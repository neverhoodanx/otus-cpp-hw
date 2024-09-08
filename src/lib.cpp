/**
 *  OTUS homework module
 *  (c) 2024
 */

#include "lib.hpp"
#include "ip_filter.hpp"

#include "split.hpp"
#include "version.h"

#include <algorithm>
#include <iostream>
#include <iterator>

namespace otus_cpp {

int version() {
	return PROJECT_VERSION_PATCH;
}

void technical_task_ip_filter() {
	// read and parse ip
	std::vector<uint32_t> ip_pool;
	for (std::string line; std::getline(std::cin, line);) {
		std::vector<std::string> out;
		split(std::begin(line), std::end(line), std::back_inserter(out), '\t',
		      [](auto it_a, auto it_b) { return std::string(it_a, it_b); });
		ip_pool.push_back(ip_filter::cast_ip_to_int(out[0]));
	}

	// sort in reverse lexicographic order
	std::sort(ip_pool.begin(), ip_pool.end(), std::greater<uint32_t>());
	ip_filter::print(ip_pool);

	// filtering the IPs by the first position of the ip address
	// first == 1
	auto pool_filtred_by_firts = ip_filter::filter(ip_pool, 1);
	ip_filter::print(pool_filtred_by_firts);

	// filtering the IPs by the first and second position of the ip address
	// first == 46 && second == 70
	auto pool_filtred_by_firts_second = ip_filter::filter(ip_pool, 46, 70);
	ip_filter::print(pool_filtred_by_firts_second);

	// filtering the IPs by any position of the ip address
	// any == 46 && second == 70
	auto pool_filtred_by_any = ip_filter::filter_any(ip_pool, 46);
	ip_filter::print(pool_filtred_by_any);
}
} // namespace otus_cpp
