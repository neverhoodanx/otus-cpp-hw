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
 * @brief Casts an IP address from string format to uint32.
 *
 * This function converts a string representation of an IP address,
 * such as "1.2.3.4", into its corresponding uint32 representation.
 *
 * @param ip_str The string representation of the IP address.
 * @return The uint32 representation of the IP address.
 */
uint32_t cast_ip_to_int(const std::string &ip_str);

/**
 * @brief Casts a uint32 IP address back to string format.
 *
 * This function converts a uint32 representation of an IP address
 * back into its string format.
 *
 * @param ip The uint32 representation of the IP address.
 * @return The string representation of the IP address.
 */
std::string cast_ip_to_string(std::uint32_t ip);

/**
 * @brief Filters IP addresses by the first octet.
 *
 * This function filters a given pool of IP addresses, returning only
 * those that match the specified first octet.
 *
 * @param pool A vector containing the pool of IP addresses in uint32 format.
 * @param by_first The first octet to filter by.
 * @return A vector of filtered IP addresses that match the first octet.
 */
std::vector<uint32_t> filter(const std::vector<uint32_t> &pool,
                             uint32_t by_first);

/**
 * @brief Filters IP addresses by the first and second octets.
 *
 * This function filters a given pool of IP addresses, returning only
 * those that match the specified first and second octets.
 *
 * @param pool A vector containing the pool of IP addresses in uint32 format.
 * @param by_first The first octet to filter by.
 * @param by_second The second octet to filter by.
 * @return A vector of filtered IP addresses that match the first and second
 * octets.
 */
std::vector<uint32_t> filter(const std::vector<uint32_t> &pool,
                             uint32_t by_first, uint32_t by_second);

/**
 * @brief Filters IP addresses by any octet.
 *
 * This function filters a given pool of IP addresses, returning only
 * those that contain the specified byte in any position.
 *
 * @param pool A vector containing the pool of IP addresses in uint32 format.
 * @param by_any The byte value to filter by.
 * @return A vector of filtered IP addresses that contain the specified byte.
 */
std::vector<uint32_t> filter_any(const std::vector<uint32_t> &pool,
                                 uint32_t by_any);

/**
 * @brief Prints a list of IP addresses in human-readable format.
 *
 * This function takes a vector of IP addresses in uint32 format and prints
 * them in a standard human-readable format, such as "1.2.3.4".
 *
 * @param pool A vector containing the pool of IP addresses in uint32 format.
 */
void print(const std::vector<uint32_t> &pool);

} // namespace otus_cpp::ip_filter
