/**
 *  OTUS homework test module
 *  (c) 2025
 */

#include "hw09_async_terminal/async.hpp"
#include <boost/test/unit_test.hpp>

#include <queue>
#include <sstream>
#include <string>

BOOST_AUTO_TEST_SUITE(AsyncTerminalSuite)

BOOST_AUTO_TEST_CASE(TestConnectDisconnect) {
	std::size_t block_size = 5;
	auto context = otus_cpp::async::connect(block_size);
	BOOST_CHECK(context != nullptr);

	otus_cpp::async::disconnect(context);
}

BOOST_AUTO_TEST_CASE(TestReceiveCommand) {
	std::size_t block_size = 3;
	auto context = otus_cpp::async::connect(block_size);

	otus_cpp::async::receive(context, "command1\ncommand2\n", 17);
	otus_cpp::async::receive(context, "command3\n", 9);

	otus_cpp::async::disconnect(context);
}

BOOST_AUTO_TEST_CASE(TestLargeBlock) {
	std::size_t block_size = 10;
	auto context = otus_cpp::async::connect(block_size);

	std::string commands;
	for (size_t i = 0; i < block_size; ++i) {
		commands += "cmd_" + std::to_string(i) + "\n";
	}

	otus_cpp::async::receive(context, commands.c_str(), commands.size());
	otus_cpp::async::disconnect(context);
}

BOOST_AUTO_TEST_CASE(TestMultipleContexts) {
	std::size_t block_size1 = 5;
	std::size_t block_size2 = 3;
	auto context1 = otus_cpp::async::connect(block_size1);
	auto context2 = otus_cpp::async::connect(block_size2);

	otus_cpp::async::receive(context1, "cmd1\n", 5);
	otus_cpp::async::receive(context2, "cmd2\ncmd3\ncmd4\n", 17);

	otus_cpp::async::disconnect(context1);
	otus_cpp::async::disconnect(context2);
}

BOOST_AUTO_TEST_SUITE_END()