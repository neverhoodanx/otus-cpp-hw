/**
 *  OTUS homework module
 *  (c) 2024
 */
#pragma once

#include <algorithm>
#include <iterator>
#include <vector>

namespace otus_cpp {
/**
 * Return library version
 * @return version number
 */
int version();

struct ip_filter {
	// template <typename... Args> std::vector<int> filter(Args... args) {
	// 	std::cout <<...args << std::endl;
	// 	return std::vector<int>();
	// }
	std::vector<int> filter(const std::vector<uint32_t> &pool, int value) {
		std::vector<int> temp;
		std::copy_if(pool.begin(), pool.end(), std::back_inserter(temp),
		             [value](uint32_t x) {
			             uint32_t firtst = x >> 24;
			             return firtst == value;
		             });
		return temp;
	}
	std::vector<int> filter(int, int) { return std::vector<int>(); }
	std::vector<int> filter(int, int, int) { return std::vector<int>(); }
	std::vector<int> filter(int, int, int, int) { return std::vector<int>(); }
	std::vector<int> filter_any() { return std::vector<int>(); }
};

} // namespace otus_cpp
