/**
 *  @file manual_test.cpp
 *  OTUS homework module
 *  manual test
 *  (c) 2025
 */

#include "hw12_map_reduce/map_reduce.hpp"

#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " <src> <mnum> <rnum>"
		          << std::endl;
		return 1;
	}

	auto file_path = std::string(argv[1]);
	size_t m_num = std::atoi(argv[2]);
	size_t r_num = std::atoi(argv[3]);

	otus_cpp::map_reduce::run(m_num, r_num, file_path);

	std::cout << "MapReduce completed successfully" << std::endl;

	otus_cpp::map_reduce::run(m_num, r_num, file_path);

	std::cout << "MapReduce completed successfully" << std::endl;
	return 0;
}