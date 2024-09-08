/**
 *  OTUS homework test module
 *  (c) 2024
 */

#define BOOST_TEST_MODULE test_version

#include "ip_filter.hpp"
#include "lib.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version) {
	BOOST_CHECK(otus_cpp::version() > 0);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_ip_filter)

BOOST_AUTO_TEST_CASE(ip_filter_cast_int_to_str) {
	auto ip_str = std::string("192.168.1.1");
	uint32_t ip_uint32 = 0xC0A80101;

	auto ret = otus_cpp::ip_filter::cast_ip_to_string(ip_uint32);

	BOOST_CHECK_EQUAL(ret, ip_str);
}

BOOST_AUTO_TEST_CASE(ip_filter_cast_str_to_int) {
	auto ip_str = std::string("192.168.1.3");
	uint32_t ip_uint32 = 0xC0A80103;

	auto ret = otus_cpp::ip_filter::cast_ip_to_int(ip_str);

	BOOST_CHECK_EQUAL(ret, ip_uint32);
}

BOOST_AUTO_TEST_CASE(ip_filter_lexical_reverse_order) {
	std::vector<std::string> ip_pool_in = {
	    "12.235.47.4",    "120.84.122.30", "164.226.91.161", "223.52.68.175",
	    "255.93.172.253", "120.84.122.29", "42.60.248.48",   "48.168.210.63",
	    "5.63.38.253",    "223.52.192.1"};
	std::vector<std::string> ip_pool_out = {
	    "255.93.172.253", "223.52.192.1",  "223.52.68.175", "164.226.91.161",
	    "120.84.122.30",  "120.84.122.29", "48.168.210.63", "42.60.248.48",
	    "12.235.47.4",    "5.63.38.253"};

	std::vector<uint32_t> ip_pool;
	for (const auto &line : ip_pool_in) {
		ip_pool.push_back(otus_cpp::ip_filter::cast_ip_to_int(line));
	}

	std::sort(ip_pool.begin(), ip_pool.end(), std::greater<uint32_t>());

	std::vector<std::string> ip_pool_res;
	for (auto ip : ip_pool) {
		ip_pool_res.push_back(otus_cpp::ip_filter::cast_ip_to_string(ip));
	}

	BOOST_TEST(ip_pool_out == ip_pool_res, boost::test_tools::per_element());
}

BOOST_AUTO_TEST_CASE(ip_filter_filter_by_first) {
	std::vector<std::string> ip_pool_in = {
	    "255.93.172.253", "223.52.192.1",  "223.52.68.175", "164.226.91.161",
	    "120.84.122.30",  "120.84.122.29", "48.168.210.63", "42.60.248.48",
	    "12.235.47.4",    "5.63.38.253"};

	std::vector<std::string> ip_pool_out = {"120.84.122.30", "120.84.122.29"};

	std::vector<uint32_t> ip_pool;
	for (const auto &line : ip_pool_in) {
		ip_pool.push_back(otus_cpp::ip_filter::cast_ip_to_int(line));
	}

	auto ip_pool_filtered = otus_cpp::ip_filter::filter(ip_pool, 120);

	std::vector<std::string> ip_pool_res;
	for (auto ip : ip_pool_filtered) {
		ip_pool_res.push_back(otus_cpp::ip_filter::cast_ip_to_string(ip));
	}

	BOOST_TEST(ip_pool_out == ip_pool_res, boost::test_tools::per_element());
}

BOOST_AUTO_TEST_CASE(ip_filter_filter_by_first_second) {
	std::vector<std::string> ip_pool_in = {
	    "255.93.172.253", "223.52.192.1",  "223.52.68.175", "164.226.91.161",
	    "120.84.122.30",  "120.84.122.29", "48.168.210.63", "42.60.248.48",
	    "12.235.47.4",    "5.63.38.253"};

	std::vector<std::string> ip_pool_out = {"223.52.192.1", "223.52.68.175"};

	std::vector<uint32_t> ip_pool;
	for (const auto &line : ip_pool_in) {
		ip_pool.push_back(otus_cpp::ip_filter::cast_ip_to_int(line));
	}

	auto ip_pool_filtered = otus_cpp::ip_filter::filter(ip_pool, 223, 52);

	std::vector<std::string> ip_pool_res;
	for (auto ip : ip_pool_filtered) {
		ip_pool_res.push_back(otus_cpp::ip_filter::cast_ip_to_string(ip));
	}

	BOOST_TEST(ip_pool_out == ip_pool_res, boost::test_tools::per_element());
}

BOOST_AUTO_TEST_CASE(ip_filter_filter_by_any) {
	std::vector<std::string> ip_pool_in = {
	    "255.93.172.253", "223.52.192.1",  "223.52.68.175", "164.226.91.161",
	    "120.84.122.30",  "120.84.122.29", "48.168.210.63", "42.60.248.48",
	    "12.235.47.4",    "5.63.38.253"};

	std::vector<std::string> ip_pool_out = {"48.168.210.63", "5.63.38.253"};

	std::vector<uint32_t> ip_pool;
	for (const auto &line : ip_pool_in) {
		ip_pool.push_back(otus_cpp::ip_filter::cast_ip_to_int(line));
	}

	auto ip_pool_filtered = otus_cpp::ip_filter::filter_any(ip_pool, 63);

	std::vector<std::string> ip_pool_res;
	for (auto ip : ip_pool_filtered) {
		ip_pool_res.push_back(otus_cpp::ip_filter::cast_ip_to_string(ip));
	}

	BOOST_TEST(ip_pool_out == ip_pool_res, boost::test_tools::per_element());
}

BOOST_AUTO_TEST_SUITE_END()
