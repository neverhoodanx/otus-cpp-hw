/**
 *  @file utility.hpp
 *  OTUS homework module
 *  #12 utility:
 *  (c) 2025
 */
#pragma once

#include <string>
#include <utility>
#include <vector>

namespace otus_cpp::map_reduce {
/**
 * @brief Splits a file into chunks for parallel processing
 * @details This function divides the input file into approximately equal-sized
 * chunks, ensuring that each chunk ends at a newline boundary
 * @param num_chunks Number of chunks to split the file into
 * @param file_path Path to the input file
 * @return A vector of pairs representing the start and end positions of each
 * chunk
 * @throws std::runtime_error If the file cannot be opened
 */
std::vector<std::pair<size_t, size_t>> split_file(size_t num_chunks,
                                                  const std::string &file_path);
} // namespace otus_cpp::map_reduce