/**
 *  OTUS homework module
 *  #4 SFINAE, Implements the IP address printing function
 *  (c) 2024
 */
#pragma once

#include "container_trait.hpp"

#include <iostream>
#include <tuple>
#include <type_traits>

namespace otus_cpp::sfinae {

/**
 * @brief Function template to print an IP address from an integral type
 * Mask to extract each byte of the IP address
 * Loop through each byte of the number, starting from the most significant byte
 * Shift the number right by index * 8 and apply the mask to get the
 * byte
 */
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_ip(const T &number) {
	uint16_t mask = 0b11111111;
	for (auto index = sizeof(T) - 1; index > 0; --index) {
		std::cout << ((number >> index * 8) & mask) << '.';
	}
	std::cout << (number & mask) << std::endl;
}

/**
 * @brief Function template to print an IP address from a string type
 * Simply output the string
 */
template <typename T>
typename std::enable_if<std::is_same<std::string, T>::value, void>::type
print_ip(const T &str) {
	std::cout << str << std::endl;
}

/**
 * @brief Function template to print an IP address from a container type
 * Iterate through each element in the container
 */
template <typename T>
typename std::enable_if<is_container<T>::value, void>::type
print_ip(const T &container) {
	for (auto const &x : container) {
		static std::string delim = "";
		std::cout << delim << x;
		delim = '.';
	}
	std::cout << std::endl;
}

/**
 * @brief Helper function template to print elements of a tuple using index
 * sequence Fold expression to print each element in the tuple separated by dots
 */
template <class T, size_t... Ts>
void print_ip_tuple(const T &val, std::index_sequence<Ts...>) {
	(..., (std::cout << (Ts == 0 ? "" : ".") << std::get<Ts>(val)));
	std::cout << std::endl;
}

/**
 * @brief Overloaded function template to handle printing of tuples
 * Create index sequence for unpacking tuple
 */
template <class... T> void print_ip_tuple(const std::tuple<T...> &val) {
	print_ip_tuple(val, std::make_index_sequence<sizeof...(T)>());
}

/**
 * @brief Function template to print an IP address from a tuple type
 * Check on all types in the tuple are equal
 */
template <typename T>
typename std::enable_if<is_tuple<T>::value, void>::type
print_ip(const T &values) {
	static_assert(is_equale_types_v<T>);
	print_ip_tuple(values);
}

} // namespace otus_cpp::sfinae
