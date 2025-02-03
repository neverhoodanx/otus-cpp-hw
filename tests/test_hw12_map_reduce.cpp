/**
 *  OTUS homework test module
 *  (c) 2025
 */

#include <boost/test/unit_test.hpp>

#include "hw12_map_reduce/mp_map.hpp"
#include "hw12_map_reduce/mp_reduce.hpp"
#include "hw12_map_reduce/mp_shuffle.hpp"
#include "hw12_map_reduce/utility.hpp"

using namespace otus_cpp::map_reduce;

std::string create_temp_file(const std::vector<std::string> &lines) {
	std::string file_path = "temp_test_file.txt";
	std::ofstream file(file_path);
	for (const auto &line : lines) {
		file << line << "\n";
	}
	file.close();
	return file_path;
}

void remove_temp_file(const std::string &file_path) {
	std::remove(file_path.c_str());
}

BOOST_AUTO_TEST_SUITE(MapReduceTests)

BOOST_AUTO_TEST_CASE(TestMapPhaseWithEmails) {
	std::vector<std::string> emails = {"alice@example.com", "bobob@example.com",
	                                   "carol@example.com", "dave@example.com"};
	std::string file_path = create_temp_file(emails);

	size_t m_num = 2;
	std::vector<std::pair<size_t, size_t>> chunks =
	    split_file(m_num, file_path);

	std::vector<std::vector<std::string>> map_results =
	    map_phase(m_num, file_path, chunks);

	BOOST_CHECK_EQUAL(map_results.size(), m_num);
	std::vector<std::string> expected_result1 = {"alice@example.com",
	                                             "bobob@example.com"};
	std::vector<std::string> expected_result2 = {"carol@example.com",
	                                             "dave@example.com"};
	BOOST_CHECK_EQUAL_COLLECTIONS(map_results[0].begin(), map_results[0].end(),
	                              expected_result1.begin(),
	                              expected_result1.end());
	BOOST_CHECK_EQUAL_COLLECTIONS(map_results[1].begin(), map_results[1].end(),
	                              expected_result2.begin(),
	                              expected_result2.end());

	remove_temp_file(file_path);
}

BOOST_AUTO_TEST_CASE(TestShufflePhaseWithEmails) {
	std::vector<std::vector<std::string>> map_results = {
	    {"alice@example.com", "bobob@example.com"},
	    {"carol@example.com", "dave@example.com"}};

	size_t r_num = 2;
	std::vector<std::vector<std::string>> shuffle_results =
	    shuffle_phase(r_num, map_results);

	BOOST_CHECK_EQUAL(shuffle_results.size(), r_num);

	BOOST_CHECK(!shuffle_results[0].empty() || !shuffle_results[1].empty());
}

BOOST_AUTO_TEST_CASE(TestReducePhaseWithEmails) {
	std::vector<std::vector<std::string>> shuffle_results = {
	    {"alice@example.com", "alicia@example.com"},
	    {"bob@example.com", "bobby@example.com"}};

	size_t r_num = 2;
	std::vector<std::vector<std::string>> reduce_results =
	    reduce_phase(r_num, shuffle_results);

	BOOST_CHECK_EQUAL(reduce_results.size(), r_num);
	std::vector<std::string> expected_result1 = {"alice", "alici"};
	std::vector<std::string> expected_result2 = {"bob@", "bobb"};
	BOOST_CHECK_EQUAL_COLLECTIONS(
	    reduce_results[0].begin(), reduce_results[0].end(),
	    expected_result1.begin(), expected_result1.end());
	BOOST_CHECK_EQUAL_COLLECTIONS(
	    reduce_results[1].begin(), reduce_results[1].end(),
	    expected_result2.begin(), expected_result2.end());
}

BOOST_AUTO_TEST_SUITE_END()