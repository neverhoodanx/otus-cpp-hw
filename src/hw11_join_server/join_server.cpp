/**
 *  @file join_server.cpp
 *  OTUS homework module
 *  #11 async tcp join server
 *  (c) 2025
 */

#include "join_server.hpp"
#include "iostream"
#include "join_session.hpp"
#include "table_keeper.hpp"

namespace otus_cpp::join {

server::server(boost::asio::io_context &io_context, short port)
    : acceptor_(io_context, boost::asio::ip::tcp::endpoint(
                                boost::asio::ip::tcp::v4(), port)),
      socket_(io_context), table_keeper_(std::make_shared<table_keeper>()) {
	start_accept();
}

void server::stop() {
	acceptor_.cancel();
}

void server::start_accept() {
	acceptor_.async_accept([this](boost::system::error_code ec,
	                              boost::asio::ip::tcp::socket socket) {
		if (!ec) {
			std::make_shared<session>(std::move(socket), table_keeper_)
			    ->start();
		} else {
			std::cerr << "Error in accepting connection: " << ec.message()
			          << std::endl;
		}
		start_accept();
	});
}

} // namespace otus_cpp::join