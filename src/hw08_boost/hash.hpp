/**
 *  OTUS homework module
 *  #8 boost, file parce
 *  (c) 2024
 */
#pragma once

#include <string>
#include <vector>

namespace otus_cpp {
/**
 * @brief Computes MD5 hash for a given buffer.
 *
 * @param buffer The buffer to compute the MD5 hash for.
 * @return The computed MD5 hash as a string.
 */
std::string compute_md5(const std::vector<char> &buffer);

/**
 * @brief Computes CRC32 hash for a given buffer.
 *
 * @param buffer The buffer to compute the CRC32 hash for.
 * @return The computed CRC32 hash as a string.
 */
std::string compute_crc32(const std::vector<char> &buffer);
} // namespace otus_cpp