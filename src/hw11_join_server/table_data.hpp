/**
 *  @file table_data.hpp
 *  OTUS homework module
 *  #11 record for table
 *  (c) 2025
 */
#pragma once

#include <map>
#include <set>
#include <string>

namespace otus_cpp::join {
/**
 * @struct table_data
 * @brief Structure to store a record with an ID and a name
 */
struct table_data {
	std::set<int> ids;
	std::map<int, std::string> data;
};

} // namespace otus_cpp::join