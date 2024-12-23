/**
 *  OTUS homework test module
 *  (c) 2024
 */

#include "hw07_terminal/terminal.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_custom_terminal)

/**
 * Test 1: Static commands with regular blocks
 */
BOOST_AUTO_TEST_CASE(test_static_blocks) {
	std::stringstream input("cmd1\ncmd2\ncmd3\ncmd4\ncmd5\n");
	std::stringstream output;
	size_t block_size = 3;

	otus_cpp::terminal terminal_(block_size, input, output);
	terminal_.run();

	std::string expected_output = "cmd1, cmd2, cmd3\ncmd4, cmd5\n";
	BOOST_CHECK_EQUAL(output.str(), expected_output);
}

/**
 * Test 2: Combination of static and dynamic blocks
 */
BOOST_AUTO_TEST_CASE(test_mixed_blocks) {
	std::stringstream input("cmd1\ncmd2\n{\ncmd3\ncmd4\n}\n{\ncmd5\ncmd6\n{"
	                        "\ncmd7\ncmd8\n}\ncmd9\n}\n{\ncmd10\ncmd11\n");
	std::stringstream output;
	size_t block_size = 2;

	otus_cpp::terminal terminal_(block_size, input, output);
	terminal_.run();

	std::string expected_output =
	    "cmd1, cmd2\ncmd3, cmd4\ncmd5, cmd6, cmd7, cmd8, cmd9\n";
	BOOST_CHECK_EQUAL(output.str(), expected_output);
}

BOOST_AUTO_TEST_SUITE_END()
