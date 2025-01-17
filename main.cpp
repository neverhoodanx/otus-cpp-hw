/**
 *  @file manual_test.cpp
 *  OTUS homework module
 *  manual test
 *  (c) 2025
 */

#include "hw09_async_terminal/async.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

	// #7 HomeWork: terminal
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <block_size>" << std::endl;
		return 1;
	}

	size_t block_size = std::stoi(argv[1]);
	auto h = otus_cpp::async::connect(block_size);
	std::string input;
	while (std::getline(std::cin, input)) {
		otus_cpp::async::receive(h, input.data(), input.size());
	}
	otus_cpp::async::disconnect(h);

	return 0;
}