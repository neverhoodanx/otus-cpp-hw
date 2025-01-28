/**
 *  OTUS homework test module
 *  (c) 2024
 */

#define BOOST_TEST_MODULE test_version

#include "hw01_version/lib_version.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version) {
	BOOST_CHECK(otus_cpp::version() > 0);
}
BOOST_AUTO_TEST_SUITE_END()