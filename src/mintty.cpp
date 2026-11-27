#include "mintty.hpp"
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <limits.h>
#include <ostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

Shell::Shell() {}

void Shell::run() {
  constexpr size_t size = PATH_MAX;
  char buffer[size];
  std::string line;

  while (true) {
    if (getcwd(buffer, size) != nullptr) {
      // finds the last occurrance of the char
      const char *slash = strrchr(buffer, '/');
      // point to the next char if exists
      const char *name = slash ? slash + 1 : buffer;
      std::cout << name << "➜" << " " << std::flush;
    } else {
      perror("getcwd");
    }

    if (!readLine(line)) {
      std::cout << "exiting shell" << std::endl;
      break;
    }

    std::vector<std::string> tokens = tokenize(line);
    if (tokens.empty())
      continue;

    lastStatus = execute(tokens);
  }
}

bool Shell::readLine(std::string &line) {
  return static_cast<bool>(std::getline(std::cin, line));
}

std::vector<std::string> Shell::tokenize(const std::string &line) {
  std::vector<std::string> tokens;
  std::string current;
  for (char c : line) {
    if (c != ' ' && c != '\t') {
      current += c;
    } else {
      if (!current.empty())
        tokens.push_back(current);
      current.clear();
    }
  }
  if (!current.empty())
    tokens.push_back(current);
  return tokens;
}

int Shell::execute(const std::vector<std::string> &tokens) {
  std::vector<char *> argv;
  for (const std::string &s : tokens) {
    argv.push_back(const_cast<char *>(s.c_str()));
  }
  argv.push_back(nullptr);

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return 1;
  } else if (pid == 0) {
    execvp(argv[0], argv.data());
    perror("execvp");
    _exit(127);
  }
  int status;
  if (waitpid(pid, &status, 0) == -1) {
    perror("waitpid");
    return 1;
  }
  if (WIFEXITED(status)) {
    return WEXITSTATUS(status);
  }
  if (WIFSIGNALED(status)) {
    return 128 + WTERMSIG(status);
  }
  return 1;
}