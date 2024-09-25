/**
 *  OTUS homework test module
 *  (c) 2024
 */

#include "custom_vector.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_custom_vector)

BOOST_AUTO_TEST_CASE(initial_is_zero) {
	otus_cpp::custom_vector<int> vec;
	BOOST_CHECK_EQUAL(vec.size(), 0);
}

BOOST_AUTO_TEST_CASE(push_back_size) {
	otus_cpp::custom_vector<int> vec;
	vec.push_back(1);
	BOOST_CHECK_EQUAL(vec.size(), 1);
	vec.push_back(2);
	BOOST_CHECK_EQUAL(vec.size(), 2);
}

BOOST_AUTO_TEST_CASE(push_back_values) {
	otus_cpp::custom_vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);

	std::ostringstream oss;
	for (size_t i = 0; i < vec.size(); ++i) {
		oss << vec[i] << " ";
	}

	BOOST_CHECK_EQUAL(oss.str(), "10 20 30 ");
}

BOOST_AUTO_TEST_CASE(copy_constructor) {
	otus_cpp::custom_vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);

	otus_cpp::custom_vector<int> vec_copy = vec;

	BOOST_CHECK_EQUAL(vec_copy.size(), 2);
	BOOST_CHECK_EQUAL(vec_copy[0], 1);
	BOOST_CHECK_EQUAL(vec_copy[1], 2);
}

BOOST_AUTO_TEST_CASE(move_constructor) {
	otus_cpp::custom_vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);

	otus_cpp::custom_vector<int> vec_move = std::move(vec);

	BOOST_CHECK_EQUAL(vec_move.size(), 2);
	BOOST_CHECK_EQUAL(vec_move[0], 1);
	BOOST_CHECK_EQUAL(vec_move[1], 2);
	BOOST_CHECK_EQUAL(vec.size(), 0);
}

BOOST_AUTO_TEST_CASE(copy_assignment_operator) {
	otus_cpp::custom_vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);

	otus_cpp::custom_vector<int> vec_copy;
	vec_copy = vec;

	BOOST_CHECK_EQUAL(vec_copy.size(), 2);
	BOOST_CHECK_EQUAL(vec_copy[0], 1);
	BOOST_CHECK_EQUAL(vec_copy[1], 2);
}

BOOST_AUTO_TEST_CASE(move_assignment_operator) {
	otus_cpp::custom_vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);

	otus_cpp::custom_vector<int> vec_move;
	vec_move = std::move(vec);

	BOOST_CHECK_EQUAL(vec_move.size(), 2);
	BOOST_CHECK_EQUAL(vec_move[0], 1);
	BOOST_CHECK_EQUAL(vec_move[1], 2);
	BOOST_CHECK_EQUAL(vec.size(), 0);
}

BOOST_AUTO_TEST_CASE(clear_check_size) {
	otus_cpp::custom_vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);

	vec.clear();

	BOOST_CHECK_EQUAL(vec.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
