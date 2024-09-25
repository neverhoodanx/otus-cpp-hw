/**
 *  OTUS homework module
 *  #2 ip filter
 *  (c) 2024
 */
#pragma once

#include <string>
#include <vector>

namespace otus_cpp::ip_filter {
/**
 * Cast a string of the form like "1.2.3.4" to uint32
 */
uint32_t cast_ip_to_int(const std::string &ip_str);

/**
 * Cast uint to string
 */
std::string cast_ip_to_string(std::uint32_t ip);

/**
 * Filtering by the first position in the ip address
 */
std::vector<uint32_t> filter(const std::vector<uint32_t> &pool,
                             uint32_t by_first);

/**
 * Filtering by the first and second position in the ip address
 */
std::vector<uint32_t> filter(const std::vector<uint32_t> &pool,
                             uint32_t by_first, uint32_t by_second);

/**
 * Filtering by the any bytes
 */
std::vector<uint32_t> filter_any(const std::vector<uint32_t> &pool,
                                 uint32_t by_any);

/**
 * Print in human-readable format, like "1.2.3.4"
 */
void print(const std::vector<uint32_t> &pool);

} // namespace otus_cpp::ip_filter
