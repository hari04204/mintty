#include "mintty.hpp"
#include <cstdio>
#include <iostream>
#include <limits.h>
#include <ostream>
#include <string>
#include <unistd.h>

Shell::Shell() {};

void Shell::run() {
  constexpr size_t size = PATH_MAX;
  char buffer[size];
	std::string line;

  while (true) {
    if (getcwd(buffer, size) != NULL) {
      std::cout << buffer << " " << std::flush;
    } else {
      perror("getcwd");
		}

		if(!readLine(line)){
			std::cout << "exiting shell" << std::endl;
			break;
		}
		std::cout << line << std::endl;
  }
}

bool Shell::readLine(std::string& line){
	return static_cast<bool>(std::getline(std::cin, line));
}