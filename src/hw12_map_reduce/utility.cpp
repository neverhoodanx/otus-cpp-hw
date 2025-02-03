/**
 *  @file utility.cpp
 *  OTUS homework module
 *  #12 utility:
 *  (c) 2025
 */

#include "utility.hpp"

#include <fstream>
#include <iostream>

namespace otus_cpp::map_reduce {
std::vector<std::pair<size_t, size_t>>
split_file(size_t num_chunks, const std::string &file_path) {
	std::ifstream file(file_path, std::ios::binary);
	std::vector<std::pair<size_t, size_t>> sections;

	if (!file.is_open()) {
		throw std::runtime_error{"Cannot open file"};
	}

	file.seekg(0, std::ios::end);
	size_t file_size = file.tellg();
	size_t chunk_size = file_size / num_chunks;
	size_t current = chunk_size;
	size_t start = 0;
	size_t stop = chunk_size;
	for (auto i = 0; i < num_chunks; ++i) {
		file.seekg(stop);
		current = stop;
		while (current < (stop + chunk_size) && current < file_size) {
			char c;
			file.get(c);
			if (c == '\n') {
				break;
			}
			++current;
		}
		sections.emplace_back(start, current);
		stop = current + chunk_size;
		start = current + 1;
	}
	sections.back().second = file_size;
	file.close();
	return sections;
}
} // namespace otus_cpp::map_reduce