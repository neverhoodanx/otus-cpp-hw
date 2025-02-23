/**
 *  @file map_reduce.hpp
 *  OTUS homework module
 *  #12 map_reduce
 *  (c) 2025
 */

#include "map_reduce.hpp"
#include "mp_map.hpp"
#include "mp_reduce.hpp"
#include "mp_shuffle.hpp"
#include "utility.hpp"

#include <iostream>

namespace otus_cpp::map_reduce {

std::string get_elem(const std::vector<std::string> &data) {
	auto iter =
	    std::max_element(data.begin(), data.end(),
	                     [](const std::string &a, const std::string &b) {
		                     return a.size() < b.size();
	                     });
	if (iter != data.end()) {
		return *iter;
	}
	return std::string();
}

void run(size_t m_num, size_t r_num, const std::string &file_path) {
	auto chunks = split_file(m_num, file_path);
	auto map_data = map_phase(m_num, file_path, chunks);
	auto shuffle_data = shuffle_phase(r_num, map_data);
	auto reduce_data = reduce_phase(r_num, shuffle_data);
	for (size_t i = 0; i < r_num; ++i) {
		std::string out_filename = "out_" + std::to_string(i) + ".txt";
		std::cout << "Filename: " << out_filename << std::endl;
		std::ofstream out_file(out_filename);
		auto str = get_elem(reduce_data[i]);
		if (!str.empty()) {
			std::cout << " - " << str << std::endl;
		}
		for (const auto &line : reduce_data[i]) {
			out_file << line << "\n";
		}
		out_file.close();
	}
}

} // namespace otus_cpp::map_reduce