/**
 *  OTUS homework module
 *  #8 boost, file parce
 *  (c) 2024
 */
#pragma once

#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace otus_cpp {
/**
 * @class file_parser
 * @brief A class that provides functionality for parsing files within
 * directories and identifying duplicates.
 */
class file_parser {
  public:
	/**
	 * @brief Default constructor.
	 */
	file_parser() = default;

	/**
	 * @brief Default destructor.
	 */
	~file_parser() = default;

	/**
	 * @brief Scans directories to find files and identify duplicates based on
	 * specified criteria.
	 *
	 * @param directories List of directories to scan.
	 * @param exclude_dirs List of directories to exclude from scanning.
	 * @param masks List of file name masks to filter files.
	 * @param min_size Minimum size of files to consider.
	 * @param block_size Size of the block used for reading files.
	 * @param level Depth level for directory scanning.
	 */
	void scan_directories(const std::vector<std::string> &directories,
	                      const std::vector<std::string> &exclude_dirs,
	                      const std::vector<std::string> &masks,
	                      size_t min_size, size_t block_size, int level);

	/**
	 * @brief Retrieves the map of duplicate files.
	 *
	 * @return A constant reference to a map where keys are MD5 hashes and
	 * values are sets of file paths that are duplicates.
	 */
	const std::unordered_map<std::string, std::unordered_set<std::string>> &
	get_dublicats() const;

  private:
	/**
	 * @brief Computes MD5 hash for a given buffer.
	 *
	 * @param buffer The buffer to compute the MD5 hash for.
	 * @return The computed MD5 hash as a string.
	 */
	std::string compute_md5(const std::vector<char> &buffer);

	/**
	 * @brief Processes a file to calculate hash for a given part of the file.
	 *
	 * @param path Path to the file to process.
	 * @param offset Offset from where to start processing the file.
	 * @param block_size Size of the block to read from the file.
	 * @return The calculated hash as a string.
	 */
	std::string process_file(const std::string &path, size_t offset,
	                         size_t block_size);

	/**
	 * @brief Compares hashes of two files to determine if they are identical.
	 *
	 * @param path_r Path to the first file.
	 * @param hash_r List of hashes for the first file.
	 * @param path_l Path to the second file.
	 * @param hash_l List of hashes for the second file.
	 * @param block_size Size of the block used for hashing.
	 * @return True if the files have identical hashes, false otherwise.
	 */
	bool equal_hashs(const std::string &path_r, std::list<std::string> &hash_r,
	                 const std::string &path_l, std::list<std::string> &hash_l,
	                 size_t block_size);

	/**
	 * @brief Checks if a filename matches any of the provided masks.
	 *
	 * @param filename The name of the file to check.
	 * @param masks List of masks to match the filename against.
	 * @return True if the filename matches one of the masks, false otherwise.
	 */
	bool matches_mask(const std::string &filename,
	                  const std::vector<std::string> &masks);

	// Members
	std::unordered_map<std::string, std::list<std::string>>
	    files_; ///< Map to store files and their associated hashes.
	std::unordered_map<std::string, std::unordered_set<std::string>>
	    dublicats_; ///< Map to store files that are duplicates.
};
} // namespace otus_cpp