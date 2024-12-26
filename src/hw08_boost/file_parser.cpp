/**
 *  OTUS homework module
 *  #8 boost - file parser
 *  (c) 2024
 */

#include "file_parser.hpp"
#include "hash.hpp"

#include <boost/filesystem.hpp>

#include <fstream>
#include <iostream>
#include <regex>

namespace {

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

	return hash_calc_(buffer);
}

bool file_parser::equal_hashs(const std::string &path_r,
                              std::list<std::string> &hash_r,
                              const std::string &path_l,
                              std::list<std::string> &hash_l,
                              size_t block_size) {
	auto process_next_block = [&](const std::string &path,
	                              std::list<std::string> &hash_list) {
		hash_list.push_back(process_file(path, hash_list.size(), block_size));
	};

	while (true) {
		// Ensure both hash lists have at least one element
		if (hash_r.size() <= hash_l.size() && hash_r.size() == hash_l.size()) {
			process_next_block(path_r, hash_r);
			process_next_block(path_l, hash_l);
		} else if (hash_r.size() < hash_l.size()) {
			process_next_block(path_r, hash_r);
		} else {
			process_next_block(path_l, hash_l);
		}

		// Compare the current block of hashes
		auto it_r = hash_r.begin();
		auto it_l = hash_l.begin();
		for (; it_r != hash_r.end() && it_l != hash_l.end(); ++it_r, ++it_l) {
			if (*it_r != *it_l) {
				return false;
			}
		}

		// Check if any hashes are empty, indicating end of file
		if (hash_r.back().empty() && hash_l.back().empty()) {
			return true;
		}
	}
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

void file_parser::setup_hash_foo(const std::string &hash_type) {
	if (hash_type == "md5") {
		hash_calc_ = [](const std::vector<char> &buffer) -> std::string {
			return compute_md5(buffer);
		};
		return;
	}
	if (hash_type == "crc32") {
		hash_calc_ = [](const std::vector<char> &buffer) -> std::string {
			return compute_crc32(buffer);
		};
		return;
	}
	hash_calc_ =
	    []([[maybe_unused]] const std::vector<char> &buffer) -> std::string {
		return {};
	};
}

void file_parser::scan_directories(const std::vector<std::string> &directories,
                                   const std::vector<std::string> &exclude_dirs,
                                   const std::vector<std::string> &masks,
                                   size_t min_size, size_t block_size,
                                   int level, const std::string &hash) {
	setup_hash_foo(hash);
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

			if (level != 1 && itr.depth() > level) {
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
						auto hash = hash_calc_(buf_hash);
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
