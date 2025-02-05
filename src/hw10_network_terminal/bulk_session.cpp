/**
 *  @file bulk_session.cpp
 *  OTUS homework module
 *  #10 bulk sesion
 *  (c) 2025
 */

#include "bulk_session.hpp"

#include <iostream>

namespace otus_cpp::nw_async {
bulk_session::bulk_session(boost::asio::ip::tcp::socket socket,
                           size_t bulk_size,
                           std::shared_ptr<decorator_async> async)
    : socket_(std::move(socket)), bulk_size_(bulk_size), async_(async),
      block_start_count_(0) {
	internal_blocks_ = async_->connect();
}

bulk_session::~bulk_session() {
	async_->disconnect(internal_blocks_);
}

void bulk_session::start() {
	read_line();
}

void bulk_session::read_line() {
	auto self(shared_from_this());
	boost::asio::async_read_until(
	    socket_, buffer_, '\n',
	    [this, self](boost::system::error_code ec,
	                 [[maybe_unused]] std::size_t length) {
		    if (!ec) {
			    std::istream is(&buffer_);
			    std::string line;
			    while (is >> line) {
				    if (!line.empty()) {
					    process_command(line);
				    }
			    }
			    read_line(); // Read the next line
		    }
	    });
}

void bulk_session::process_command(const std::string &line) {
	manage_block_state(line[0]);

	if (block_start_count_ == 0) {
		async_->send_external_data(line);
	} else {
		async_->send_internal_data(internal_blocks_, line);
	}
}

void bulk_session::manage_block_state(char ch) {
	if (ch == '{') {
		++block_start_count_;
	}
	if (ch == '}') {
		if (block_start_count_ > 0) {
			--block_start_count_;
		}
	}
}

} // namespace otus_cpp::nw_async