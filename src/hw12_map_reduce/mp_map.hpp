/**
 *  @file mp_map.hpp
 *  OTUS homework module
 *  #12 map:
 *  (c) 2025
 */
#pragma once

#include <string>
#include <vector>

#include <algorithm>
#include <fstream>
#include <thread>

namespace otus_cpp::map_reduce {
// can be used for windows
// std::string remove_carriage_returns(const std::string &input) {
//	std::string result = input;
//	result.erase(std::remove_if(result.begin(), result.end(),
//	                            [](char ch) {
//		                            return ch ==
//		                                   '\r';
//	                            }),
//	             result.end());
//
//	return result;
//}

/**
 * @struct map_function
 * @brief Represents a mapping function used in the Map phase of the MapReduce
 * algorithm
 * @details This struct defines the operator() to process input lines and return
 * a vector of mapped strings
 */
struct map_function {
	std::vector<std::string> operator()(const std::string &line) const {
#ifdef WIN32
		return {line.substr(0, line.size() - 1)};
#else
		return {line};
#endif
	}
};

/**
 * @brief Executes the Map phase of the MapReduce algorithm.
 * @details This function divides the input file into chunks and processes each
 * chunk in parallel using threads. Each thread applies the provided
 * `map_function` to its assigned chunk of data
 * @param m_num Number of mapper threads to use
 * @param file_path Path to the input file
 * @param chunks Vector of pairs representing the start and end positions of
 * file chunks
 * @return A data containing the results of the Map phase
 */
std::vector<std::vector<std::string>>
map_phase(size_t m_num, const std::string &file_path,
          std::vector<std::pair<size_t, size_t>> &chunks) {
	std::vector<std::vector<std::string>> map_results(m_num);
	std::vector<std::thread> map_threads;
	int i = 0;
	for (const auto &chunk : chunks) {
		map_threads.emplace_back(
		    [](const std::string &filename,
		       const std::pair<size_t, size_t> &chunk,
		       std::vector<std::string> &map_result, map_function map_func) {
			    std::ifstream file(filename, std::ios::binary);
			    file.seekg(chunk.first);
			    std::string line;
			    while (file.tellg() < chunk.second && getline(file, line)) {
				    auto mapped_lines = map_func(line);
				    map_result.insert(map_result.end(), mapped_lines.begin(),
				                      mapped_lines.end());
			    }
			    std::sort(map_result.begin(), map_result.end());
			    file.close();
		    },
		    std::ref(file_path), chunk, std::ref(map_results[i++]),
		    map_function());
	}
	for (auto &thread : map_threads) {
		thread.join();
	}
	return map_results;
}

} // namespace otus_cpp::map_reduce
