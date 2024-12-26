/**
 *  OTUS homework module
 *  manual test
 *  (c) 2024
 */

#include "hw08_boost/file_parser.hpp"

#include <boost/program_options.hpp>

#include <iostream>

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
	// #8 HomeWork: boost
	try {
		std::vector<std::string> directories;
		std::vector<std::string> exclude_dirs;
		std::vector<std::string> masks;
		size_t min_size;
		size_t block_size;
		int level;
		std::string hash_type;

		po::options_description desc("Allowed options");
		desc.add_options()
		("help", "produce help message")
		("directories,d", po::value<std::vector<std::string>>(&directories)->multitoken(), "directories to scan")
		("exclude,e", po::value<std::vector<std::string>>(&exclude_dirs)->multitoken(), "directories to exclude")
		("mask,m", po::value<std::vector<std::string>>(&masks)->multitoken(), "file name masks")
		("min-size,s", po::value<size_t>(&min_size)->default_value(1), "minimum file size")
		("block-size,b", po::value<size_t>(&block_size)->default_value(4096), "block size for reading")
		("level,l", po::value<int>(&level)->default_value(1), "scanning level (0 Current directory only or 1 Recursive scanning)")
		("hash,H", po::value<std::string>(&hash_type)->default_value("md5"), "hash type (md5 or crc32)");

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("help") || directories.empty()) {
			std::cout << desc << "\n";
			return 1;
		}
		if (level != 0 && level != 1) {
			std::cerr << "Invalid level. Use '0' for current directory only or "
			             "'1' for recursive scanning.\n";
			return 1;
		}
		if (hash_type != "md5" && hash_type != "crc32") {
			std::cerr << "Invalid hash type. Use 'md5' or 'crc32'.\n";
			return 1;
		}

		auto fp_ = std::make_unique<otus_cpp::file_parser>();

		fp_->scan_directories(directories, exclude_dirs, masks, min_size,
		                      block_size, level, hash_type);

		for (const auto &pair : fp_->get_dublicats()) {
			std::cout << "hash: " << pair.first
			          << ", dublicates: " << std::endl;
			for (const auto &value : pair.second) {
				std::cout << " - " << value << " " << std::endl;
			}
			std::cout << std::endl;
		}
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	} catch (...) {
		std::cerr << "Unknown error!\n";
		return 1;
	}
	return 0;
}
