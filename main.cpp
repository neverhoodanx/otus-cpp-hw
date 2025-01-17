/**
 *  @file manual_test.cpp
 *  OTUS homework module
 *  manual test
 *  (c) 2025
 */


#include "hw10_network_terminal/network_terminal.hpp"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: bulk_server <port> <bulk_size>\n";
		return 1;
	}

	try {
		auto port = std::atoi(argv[1]);
		size_t bulk_size = std::atoi(argv[2]);

		boost::asio::io_context io_context;
		otus_cpp::nw_async::server s(io_context, static_cast<short>(port),
		                             bulk_size);
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