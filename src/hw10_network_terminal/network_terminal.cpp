/**
 *  @file network_terminal.cpp
 *  OTUS homework module
 *  #10 async tcp terminal
 *  (c) 2025
 */

#include "network_terminal.hpp"
#include "bulk_session.hpp"
#include "decorator_async.hpp"

namespace otus_cpp::nw_async {

server::server(boost::asio::io_context &io_context, short port,
               size_t bulk_size)
    : acceptor_(io_context, boost::asio::ip::tcp::endpoint(
                                boost::asio::ip::tcp::v4(), port)),
      socket_(io_context), bulk_size_(bulk_size) {
	start_accept();
	async_ = std::make_shared<decorator_async>(bulk_size_);
}

void server::stop() {
	acceptor_.cancel();
	async_->flush();
}

void server::start_accept() {
	acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
		if (!ec) {
			// Create a new session for the incoming connection
			std::make_shared<bulk_session>(std::move(socket_), bulk_size_,
			                               async_)
			    ->start();
		}
		start_accept();
	});
}

} // namespace otus_cpp::nw_async