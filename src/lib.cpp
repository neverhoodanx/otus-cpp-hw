/**
 *  OTUS homework module
 *  (c) 2024
 */

#include "lib.hpp"
#include "ip_filter.hpp"

#include "split.hpp"
#include "version.h"

#include "custom_allocator.hpp"
#include "custom_vector.hpp"
#include "number_sequence.hpp"

#include "ip_print.hpp"

#include "graphic_editor/canvas.hpp"
#include "graphic_editor/circle.hpp"
#include "graphic_editor/controller.hpp"
#include "graphic_editor/shape_manager.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <map>

namespace otus_cpp {
void technical_task_graphic_editor() {
	editor::controller ctrl(std::make_shared<editor::shape_manager>(),
	                        std::make_shared<editor::canvas>());

	ctrl.create_circle(1, 1, 1);
	ctrl.create_circle(2, 2, 2);
	ctrl.update_view();
	ctrl.save_document("untitled.svg");
	ctrl.delete_shape(0);
	ctrl.update_view();
}

void technical_task_sfinae() {
	// 255
	otus_cpp::sfinae::print_ip(int8_t{-1});

	// 0.0
	otus_cpp::sfinae::print_ip(int16_t{0});

	// 127.0.0.1
	otus_cpp::sfinae::print_ip(int32_t{2130706433});

	// 123.45.67.89.101.112.131.41
	otus_cpp::sfinae::print_ip(int64_t{8875824491850138409});

	// Hello, World!
	otus_cpp::sfinae::print_ip(std::string{"Hello, World!"});

	// 100.200.300.400
	otus_cpp::sfinae::print_ip(std::vector<int>{100, 200, 300, 400});

	// 400.300.200.100
	otus_cpp::sfinae::print_ip(std::list<short>{400, 300, 200, 100});

	// 123.456.789.0
	otus_cpp::sfinae::print_ip(std::make_tuple(123, 456, 789, 0));

	// Compilation error
	// otus::sfinae::print_ip(std::make_tuple(123, 456, 'c', 0, 6));
}

void technical_task_allocators() {
	static constexpr std::array numbers{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	// Creating an instance of std::map<int, int>
	auto map_std_allocator = std::map<int, int>();
	// Filling it with 10 elements, where the key is a number from 0 to 9, and
	// the value is the factorial of the key
	for (const auto &x : numbers) {
		map_std_allocator.emplace(x, factorial(x));
	}

	// Creating an instance of std::map<int, int> with a new allocator limited
	// to 10 elements
	auto map_custom_allocator =
	    std::map<int, int, std::less<>,
	             custom_allocator<std::pair<const int, int>, 10>>{};
	// Filling it with 10 elements, where the key is a number from 0 to 9, and
	// the value is the factorial of the key
	for (const auto &x : numbers) {
		map_custom_allocator.emplace(x, factorial(x));
	}
	// Displaying all values (key and value separated by a space) stored in the
	// container
	for (const auto &[key, val] : map_custom_allocator) {
		std::cout << key << " " << val << std::endl;
	}

	// Creating an instance of a custom container for storing values of type int
	auto vector_std_allocator = custom_vector<int>();
	// Filling it with 10 elements from 0 to 9
	for (const auto &x : numbers) {
		vector_std_allocator.push_back(x);
	}

	// Creating an instance of a custom container for storing values of type int
	// with a new allocator limited to 10 elements
	auto vector_custom_allocator =
	    custom_vector<int, custom_allocator<int, 10>>();
	// Filling it with 10 elements from 0 to 9
	for (const auto &x : numbers) {
		vector_custom_allocator.push_back(x);
	}
	// Displaying all values stored in the container
	for (const auto &val : vector_custom_allocator) {
		std::cout << val << std::endl;
	}
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

int version() {
	return PROJECT_VERSION_PATCH;
}
} // namespace otus_cpp
