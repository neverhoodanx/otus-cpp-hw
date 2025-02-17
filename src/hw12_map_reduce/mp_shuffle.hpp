/**
 *  @file mp_shuffle.hpp
 *  OTUS homework module
 *  #12 shuffle
 *  (c) 2025
 */
#pragma once

#include <string>
#include <vector>

#include <algorithm>

namespace otus_cpp::map_reduce {
/**
 * @brief Executes the Shuffle phase of the MapReduce algorithm
 * @details This function redistributes the mapped results into buckets based on
 * a hash function. Each bucket corresponds to a reducer
 * @param r_num Number of reducers
 * @param map_results Results from the Map phase
 * @return A data containing the shuffled data for each reducer
 */
std::vector<std::vector<std::string>>
shuffle_phase(size_t r_num,
              const std::vector<std::vector<std::string>> &map_results) {

	std::vector<std::vector<std::string>> shuffle_results(r_num);

	for (const auto &mapResult : map_results) {
		for (const auto &line : mapResult) {
			size_t hash = std::hash<std::string>{}(line) % r_num;
			shuffle_results[hash].push_back(line);
		}
	}

	for (auto &shuffle_result : shuffle_results) {
		std::sort(shuffle_result.begin(), shuffle_result.end());
	}
	return shuffle_results;
}

} // namespace otus_cpp::map_reduce
