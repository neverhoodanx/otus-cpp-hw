/**
 *  OTUS homework test module
 *  (c) 2024
 */

#include "custom_allocator.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_custom_vector)

BOOST_AUTO_TEST_CASE(test_allocate_deallocate) {
	otus_cpp::custom_allocator<int, 1> allocator;

	int *p = allocator.allocate(1);
	BOOST_REQUIRE(p != nullptr);

	*p = 42;
	BOOST_CHECK(*p == 42);

	allocator.deallocate(p, 1);
}

BOOST_AUTO_TEST_CASE(test_reserve) {
	otus_cpp::custom_allocator<int, 10> allocator;

	int *p1 = allocator.allocate(1);
	BOOST_REQUIRE(p1 != nullptr);

	*p1 = 100;
	BOOST_CHECK(*p1 == 100);

	allocator.deallocate(p1, 1);

	int *p2 = allocator.allocate(1);
	BOOST_REQUIRE(p2 != nullptr);
	BOOST_CHECK(p1 == p2);

	allocator.deallocate(p2, 1);
}

BOOST_AUTO_TEST_CASE(test_allocate_large) {
	otus_cpp::custom_allocator<int> allocator;

	BOOST_CHECK_THROW(
	    allocator.allocate(std::numeric_limits<std::size_t>::max()),
	    std::bad_alloc);
}

BOOST_AUTO_TEST_SUITE_END()
