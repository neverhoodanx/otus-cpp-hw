/**
 *  OTUS homework module
 *  manual test
 *  (c) 2024
 */

#include "lib.hpp"

#include <iostream>

int main(int, char **) {
	// #2 HomeWork: ip filter
	try {
		otus_cpp::technical_task_ip_filter();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	// #1 HomeWork: hello world
	/*
	std::cout << "Version: " << otus_cpp::version() << std::endl;
	std::cout << "Hello, world!" << std::endl;
	*/

	return 0;
}
