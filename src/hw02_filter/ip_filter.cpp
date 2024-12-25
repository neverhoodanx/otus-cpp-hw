/**
 *  OTUS homework module
 *  #2 ip filter
 *  (c) 2024
 */

#include "ip_filter.hpp"
#include "split.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

static size_t ip_size = 4;

namespace otus_cpp::ip_filter {

uint32_t cast_ip_to_int(const std::string &ip_str) {
	std::vector<std::string> out;
	out.reserve(ip_size);
	split(std::begin(ip_str), std::end(ip_str), std::back_inserter(out), '.',
	      [](auto it_a, auto it_b) { return std::string(it_a, it_b); });
	uint32_t ip_int = 0;
	ip_int |= (std::stoul(out[0]) << 24) & 0xff000000;
	ip_int |= (std::stoul(out[1]) << 16) & 0x00ff0000;
	ip_int |= (std::stoul(out[2]) << 8) & 0x0000ff00;
	ip_int |= std::stoul(out[3]) & 0x000000ff;
	return ip_int;
}

std::string cast_ip_to_string(std::uint32_t ip) {
	std::stringstream ss;
	ss << (ip >> 24) << "." << ((ip >> 16) & 0x00ff) << "."
	   << ((ip >> 8) & 0x0000ff) << "." << (ip & 0x000000ff);
	return ss.str();
}

std::vector<uint32_t> filter(const std::vector<uint32_t> &pool,
                             uint32_t by_first) {
	std::vector<uint32_t> ret;
	std::copy_if(pool.begin(), pool.end(), std::back_inserter(ret),
	             [by_first](uint32_t x) {
		             uint32_t firtst = x >> 24;
		             return ((firtst) == by_first);
	             });
	return ret;
}

std::vector<uint32_t> filter(const std::vector<uint32_t> &pool,
                             uint32_t by_first, uint32_t by_second) {
	std::vector<uint32_t> ret;
	std::copy_if(pool.begin(), pool.end(), std::back_inserter(ret),
	             [by_first, by_second](uint32_t x) {
		             uint32_t firtst = x >> 24;
		             uint32_t second = (x >> 16) & 0x00ff;
		             return ((firtst == by_first) && (second == by_second));
	             });
	return ret;
}

std::vector<uint32_t> filter_any(const std::vector<uint32_t> &pool,
                                 uint32_t by_any) {
	std::vector<uint32_t> ret;
	std::copy_if(pool.begin(), pool.end(), std::back_inserter(ret),
	             [by_any](uint32_t x) {
		             uint32_t firtst = x >> 24;
		             uint32_t second = (x >> 16) & 0x00ff;
		             uint32_t third = (x >> 8) & 0x0000ff;
		             uint32_t fourth = x & 0x000000ff;
		             return ((firtst == by_any) || (second == by_any) ||
		                     (third == by_any) || (fourth == by_any));
	             });
	return ret;
}

void print(const std::vector<uint32_t> &pool) {
	for (const auto &ip : pool) {
		std::cout << cast_ip_to_string(ip) << "\n"; // std::endl
	}
}

} // namespace otus_cpp::ip_filter
