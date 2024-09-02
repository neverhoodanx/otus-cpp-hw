/**
 *  OTUS homework Gtest module
 *  (c) 2024
 */

#include "lib.h"

#include <gtest/gtest.h>

TEST(TestVersion, not_null_version) {
	EXPECT_GT(otus_cpp::version(), 0);
}
