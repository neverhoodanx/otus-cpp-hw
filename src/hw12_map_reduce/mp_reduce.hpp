/**
 *  @file mp_reduce.hpp
 *  OTUS homework module
 *  #12 reduce
 *  (c) 2025
 */
#pragma once

#include <string>
#include <vector>

#include <algorithm>
#include <fstream>
#include <set>
#include <thread>

namespace otus_cpp::map_reduce {
/**
 * @struct reduce_function
 * @brief Represents a reduction function used in the Reduce phase of the
 * MapReduce algorithm
 * @details This struct defines the operator() to process a vector of strings
 * and return a reduced set of unique prefixes
 */
struct reduce_function {
	std::vector<std::string>
	operator()(const std::vector<std::string> &lines) const {
		std::set<std::string> unique_lines(lines.begin(), lines.end());
		std::vector<std::string> result;
		for (const auto &line : unique_lines) {
			std::string prefix;
			for (size_t i = 1; i <= line.size(); ++i) {
				prefix = line.substr(0, i);
				bool isUnique = true;
				for (const auto &other_line : unique_lines) {
					if (other_line != line &&
					    other_line.substr(0, i) == prefix) {
						isUnique = false;
						break;
					}
				}
				if (isUnique) {
					result.push_back(prefix);
					break;
				}
			}
			if (result.empty()) {
				result.push_back(line);
			}
		}
		return result;
	}
};

/**
 * @brief Executes the Reduce phase of the MapReduce algorithm
 * @details This function processes the shuffled results in parallel using
 * threads. Each thread applies the provided `reduce_function` to its assigned
 * subset of data
 * @param r_num Number of reducer threads to use
 * @param shuffle_results Shuffled results from the Shuffle phase
 * @return A data containing the results of the Reduce phase
 */
std::vector<std::vector<std::string>>
reduce_phase(size_t r_num,
             const std::vector<std::vector<std::string>> &shuffle_results) {
	std::vector<std::thread> reduce_threads;
	std::vector<std::vector<std::string>> reduce_results(r_num);
	for (int i = 0; i < r_num; ++i) {
		reduce_threads.emplace_back(
		    [](const std::vector<std::string> &shuffle_result,
		       std::vector<std::string> &reduce_result,
		       reduce_function reduce_func) {
			    reduce_result = reduce_func(shuffle_result);
		    },
		    std::ref(shuffle_results[i]), std::ref(reduce_results[i]),
		    reduce_function());
	}

	for (auto &thread : reduce_threads) {
		thread.join();
	}

	return reduce_results;
}

} // namespace otus_cpp::map_reduce
