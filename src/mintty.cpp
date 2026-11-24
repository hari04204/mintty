#include "mintty.hpp"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <limits.h>
#include <ostream>
#include <string>
#include <unistd.h>
#include <vector>

Shell::Shell() {};

void Shell::run() {
  constexpr size_t size = PATH_MAX;
  char buffer[size];
  std::string line;

  while (true) {
    if (getcwd(buffer, size) != NULL) {
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

		for(std::string token: tokens){
			std::cout << token << std::endl;
		}
  }
}

bool Shell::readLine(std::string &line) {
  return static_cast<bool>(std::getline(std::cin, line));
}

std::vector<std::string> Shell::tokenize(std::string &line){
	std::vector<std::string> tokens;
	std::string current;
	for(char c: line){
		if(c!=' '){
			current+=c;
		}
		else{
			tokens.push_back(current);
			current.clear();
		}
	}
	if(!current.empty()) tokens.push_back(current);
	return tokens;
}