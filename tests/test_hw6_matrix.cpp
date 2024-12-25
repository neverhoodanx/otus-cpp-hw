/**
 *  OTUS homework test module
 *  (c) 2024
 */

#include "hw06_matrix/custom_matrix.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_custom_n_matrix)

BOOST_AUTO_TEST_CASE(test_set_get_values) {
	otus_cpp::custom_matrix<int, 2> matrix;
	matrix[0][0] = 1;
	matrix[1][1] = 2;
	matrix[2][2] = 3;

	BOOST_CHECK_EQUAL(matrix.get({0, 0}), 1);
	BOOST_CHECK_EQUAL(matrix.get({1, 1}), 2);
	BOOST_CHECK_EQUAL(matrix.get({2, 2}), 3);
	BOOST_CHECK_EQUAL(matrix.get({0, 1}), 0); // Default value
}

BOOST_AUTO_TEST_CASE(test_iter_over_matrix) {
	otus_cpp::custom_matrix<int, 2> matrix;
	matrix[0][0] = 1;
	matrix[1][1] = 2;
	matrix[2][2] = 3;

	std::vector<std::tuple<uint32_t, uint32_t, int>> expected = {
	    {2, 2, 3}, {0, 0, 1}, {1, 1, 2}};

	auto it = matrix.begin();
	for (const auto &expected_value : expected) {
		(void)expected_value;
		BOOST_CHECK(it != matrix.end());
		++it;
	}
	BOOST_CHECK(it == matrix.end());
}

BOOST_AUTO_TEST_CASE(test_remove_values) {
	otus_cpp::custom_matrix<int, 2> matrix;
	matrix[0][0] = 1;
	matrix[1][1] = 2;
	matrix[2][2] = 3;

	matrix.set({1, 1}, 0);

	BOOST_CHECK_EQUAL(matrix.get({0, 0}), 1);
	BOOST_CHECK_EQUAL(matrix.get({1, 1}), 0);
	BOOST_CHECK_EQUAL(matrix.get({2, 2}), 3);
}

BOOST_AUTO_TEST_CASE(AssignmentOperator) {
	otus_cpp::custom_matrix<int, 2> matrix1;
	matrix1[0][0] = 1;
	matrix1[1][1] = 2;

	otus_cpp::custom_matrix<int, 2> matrix2;
	matrix2 = matrix1;

	BOOST_CHECK_EQUAL(matrix2.get({0, 0}), 1);
	BOOST_CHECK_EQUAL(matrix2.get({1, 1}), 2);
}

BOOST_AUTO_TEST_SUITE_END()
