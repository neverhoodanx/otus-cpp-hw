/**
 *  @file map_reduce.hpp
 *  OTUS homework module
 *  #12 map reduce
 *  (c) 2025
 */
#pragma once

#include <string>
#include <utility>
#include <vector>

namespace otus_cpp::map_reduce {
/**
 * @brief Launches a MapReduce task to determine the minimal possible prefix
 * that uniquely identifies a string
 * @param m_num Number of mapper threads to use for map phase
 * @param r_num Number of reducer threads to use for reduce phase
 * @param file_path Path to the input file
 */
void run(size_t m_num, size_t r_num, const std::string &file_path);

} // namespace otus_cpp::map_reduce
