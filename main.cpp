/**
 *  @file manual_test.cpp
 *  OTUS homework module
 *  manual test
 *  (c) 2025
 */


#include "hw11_join_server/join_server.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: join_server <port>\n";
		return 1;
	}

	try {
		auto port = std::atoi(argv[1]);
		boost::asio::io_context io_context;
		otus_cpp::join::server s(io_context, static_cast<short>(port));
		boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
		signals.async_wait([&](auto, auto) {
			s.stop();
			io_context.stop();
		});
		io_context.run(); // Run the server in a single thread
	} catch (std::exception &e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}