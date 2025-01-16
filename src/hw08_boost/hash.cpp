/**
 *  OTUS homework module
 *  #8 boost - file parser
 *  (c) 2024
 */

#include "hash.hpp"

#include <boost/algorithm/hex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>

namespace {
/**
 * @brief Converts an MD5 digest to a string representation.
 *
 * This function takes an MD5 digest, which is typically represented as an array
 * of integers, and converts it into a human-readable hexadecimal string. This
 * is useful for displaying the MD5 hash in a common format.
 *
 * @param digest The MD5 digest to convert. It's a fixed-size array of integers
 * as defined by Boost's MD5 implementation.
 * @return A string containing the hexadecimal representation of the MD5 digest.
 */
std::string
md5_digest_to_string(const boost::uuids::detail::md5::digest_type &digest) {
	const auto intDigest = reinterpret_cast<const int *>(&digest);
	std::string result;
	boost::algorithm::hex(
	    intDigest,
	    intDigest +
	        (sizeof(boost::uuids::detail::md5::digest_type) / sizeof(int)),
	    std::back_inserter(result));
	return result;
}
} // namespace

namespace otus_cpp {
std::string compute_md5(const std::vector<char> &buffer) {
	boost::uuids::detail::md5 hash;
	boost::uuids::detail::md5::digest_type digest;
	hash.process_bytes(buffer.data(), buffer.size());
	hash.get_digest(digest);
	return md5_digest_to_string(digest);
}

std::string compute_crc32(const std::vector<char> &buffer) {
	boost::crc_32_type result;
	result.process_bytes(buffer.data(), buffer.size());
	return std::to_string(result.checksum());
}
} // namespace otus_cpp