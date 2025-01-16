/**
 *  OTUS homework test module
 *  (c) 2024
 */

#include "hw08_boost/file_parser.hpp"
#include <boost/test/unit_test.hpp>

#include <boost/filesystem.hpp>
// #include <boost/process.hpp>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

BOOST_AUTO_TEST_SUITE(test_boost_file_parser)

using namespace boost::filesystem;
// namespace bp = boost::process;

void create_file_with_content(const path &file_path,
                              const std::string &content) {
	std::ofstream file(file_path.string());
	file << content;
	file.close();
}

BOOST_AUTO_TEST_CASE(find_duplicates_test) {
	path temp_dir = current_path() / unique_path();
	create_directories(temp_dir);

	path file1 = temp_dir / "file1.txt";
	path file2 = temp_dir / "file2.txt";
	path file3 = temp_dir / "file3.txt";
	path file4 = temp_dir / "file4.txt";
	std::unordered_set<std::string> output_check;
	output_check.emplace(file1.string());
	output_check.emplace(file2.string());

	create_file_with_content(file1, "Hello, World!\n");
	create_file_with_content(file2, "Hello, World!\n");

	create_file_with_content(file3, "Hello, Boost!\n");
	create_file_with_content(file4, "Hello, Test!\n");

	otus_cpp::file_parser parser;
	parser.scan_directories({temp_dir.string()}, {}, {"*.*"}, 2, 64, 1, "md5");
	auto output = parser.get_dublicats();

	BOOST_CHECK_EQUAL(output.size(), 1);
	auto it = output.begin();
	for (auto val : it->second) {
		BOOST_CHECK_EQUAL(output_check.find(val) != output_check.end(), true);
	}

	remove_all(temp_dir);
}

BOOST_AUTO_TEST_SUITE_END()
