/**
 *  @file manual_test.cpp
 *  OTUS homework module
 *  manual test
 *  (c) 2025
 */

#include "hw09_async_terminal/async.hpp"

int main() {

	std::size_t bulk = 5;
	auto h = otus_cpp::async::connect(bulk);
	auto h2 = otus_cpp::async::connect(bulk);
	otus_cpp::async::receive(h, "1", 1);
	otus_cpp::async::receive(h2, "1\n", 2);
	otus_cpp::async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
	otus_cpp::async::receive(h, "b\nc\nd\n}\n89\n", 11);
	otus_cpp::async::disconnect(h);
	otus_cpp::async::disconnect(h2);

	return 0;
}