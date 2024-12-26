/**
 *  OTUS homework module
 *  #8 boost - file parser
 *  (c) 2024
 */

#include "file_parser.hpp"

#include <boost/algorithm/hex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include <boost/uuid/detail/md5.hpp>

#include <fstream>
#include <iostream>
#include <regex>

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

/**
 * @brief Concatenates all strings in a list into a single vector of characters.
 *
 * This function takes a list of strings and combines all of them into a
 * contiguous sequence of characters stored in a vector. It's useful for cases
 * where you need a single char buffer with all the string contents.
 *
 * @param stringList The list of strings to concatenate.
 * @return A vector of characters containing the concatenated strings.
 */
std::vector<char>
concatenateStringsToVector(const std::list<std::string> &stringList) {
	std::vector<char> result;
	size_t totalSize = 0;
	for (const auto &str : stringList) {
		totalSize += str.size();
	}
	result.reserve(totalSize);
	for (const auto &str : stringList) {
		result.insert(result.end(), str.begin(), str.end());
	}
	return result;
}

} // namespace

namespace otus_cpp {

namespace fs = boost::filesystem;

std::string file_parser::compute_md5(const std::vector<char> &buffer) {

	boost::uuids::detail::md5 hash;
	boost::uuids::detail::md5::digest_type digest;
	hash.process_bytes(buffer.data(), buffer.size());
	hash.get_digest(digest);

	return md5_digest_to_string(digest);
}

std::string file_parser::process_file(const std::string &path, size_t offset,
                                      size_t block_size) {
	std::ifstream file(path, std::ios::binary);
	if (!file.is_open()) {
		return {};
	}

	file.seekg(offset * block_size, std::ios::beg);
	if (file.fail()) {
		return {};
	}

	std::vector<char> buffer(block_size);
	file.read(buffer.data(), block_size);
	if (file.gcount() == 0) {
		return {};
	}
	if (file.gcount() < (long long)block_size) {
		std::fill(buffer.begin() + file.gcount(), buffer.end(), 0);
	}

	return compute_md5(buffer);
}

bool file_parser::equal_hashs(const std::string &path_r,
                              std::list<std::string> &hash_r,
                              const std::string &path_l,
                              std::list<std::string> &hash_l,
                              size_t block_size) {
	if (hash_r.empty()) {
		hash_r.push_back(process_file(path_r, hash_r.size(), block_size));
	}
	if (hash_l.empty()) {
		hash_l.push_back(process_file(path_l, hash_l.size(), block_size));
	}
	if (hash_r.size() == hash_l.size() &&
	    std::equal(hash_r.begin(), hash_r.end(), hash_l.begin()) &&
	    hash_l.back().empty() && hash_r.back().empty()) {
		return true;
	}
	auto r = hash_r.begin();
	auto l = hash_l.begin();
	while (r != hash_r.end() && l != hash_l.end()) {
		if ((*r) == (*l)) {
			r++;
			l++;
		} else {
			return false;
		}
	}
	while (r != hash_r.end()) {
		hash_l.push_back(process_file(path_l, hash_l.size(), block_size));
		if ((*r) != hash_l.back()) {
			return false;
		}
		r++;
	}
	while (l != hash_l.end()) {
		hash_r.push_back(process_file(path_r, hash_r.size(), block_size));
		if ((*l) != hash_r.back()) {
			return false;
		}
		l++;
	}
	while (true) {
		if (hash_r.back().empty() && hash_l.back().empty()) {
			return true;
		}
		if (hash_r.back() != hash_l.back()) {
			return false;
		}
		hash_r.push_back(process_file(path_r, hash_r.size(), block_size));
		hash_l.push_back(process_file(path_l, hash_l.size(), block_size));
	}
	return true;
}

bool file_parser::matches_mask(const std::string &filename,
                               const std::vector<std::string> &masks) {
	if (masks.empty()) {
		return true;
	}
	for (const auto &mask : masks) {
		std::regex mask_regex(
		    "^" + std::regex_replace(mask, std::regex("\\*"), ".*") + "$",
		    std::regex_constants::icase);
		if (std::regex_match(filename, mask_regex)) {
			return true;
		}
	}
	return false;
}

void file_parser::scan_directories(const std::vector<std::string> &directories,
                                   const std::vector<std::string> &exclude_dirs,
                                   const std::vector<std::string> &masks,
                                   size_t min_size, size_t block_size,
                                   int level) {
	std::unordered_map<std::string, std::vector<fs::path>> file_signatures;

	for (const auto &dir : directories) {
		if (!fs::exists(dir) || !fs::is_directory(dir))
			continue;

		fs::recursive_directory_iterator end_itr;
		for (fs::recursive_directory_iterator itr(dir); itr != end_itr; ++itr) {
			if (std::find_if(exclude_dirs.begin(), exclude_dirs.end(),
			                 [=](const std::string &val) {
				                 fs::recursive_directory_iterator test_itr(val);
				                 if (test_itr.depth() < itr.depth()) {
					                 return itr->path().string().find(val) !=
					                        std::string::npos;
				                 } else {
					                 return false;
				                 }
			                 }) != exclude_dirs.end()) {
				continue;
			}

			if (itr.depth() > (level - 1)) {
				continue;
			}

			if (fs::is_regular_file(*itr) && fs::file_size(*itr) > min_size &&
			    matches_mask(itr->path().filename().string(), masks)) {
				if (files_.empty()) {
					files_.emplace(std::make_pair(itr->path().string(),
					                              std::list<std::string>()));
					continue;
				}

				auto nf = std::make_pair(itr->path().string(),
				                         std::list<std::string>());
				nf.second.push_back(
				    process_file(itr->path().string(), 0, block_size));
				for (auto &pair : files_) {
					if (equal_hashs(pair.first, pair.second, nf.first,
					                nf.second, block_size)) {
						auto buf_hash = concatenateStringsToVector(pair.second);
						auto hash = compute_md5(buf_hash);
						dublicats_[hash].insert(pair.first);
						dublicats_[hash].insert(nf.first);
					}
				}
				files_.emplace(nf);
			}
		}
	}
}

const std::unordered_map<std::string, std::unordered_set<std::string>> &
file_parser::get_dublicats() const {
	return dublicats_;
}
} // namespace otus_cpp
