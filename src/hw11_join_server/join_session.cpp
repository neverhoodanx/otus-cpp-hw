/**
 *  @file join_sesion.cpp
 *  OTUS homework module
 *  #11 join sesion
 *  (c) 2025
 */

#include "join_session.hpp"

#include <iostream>

namespace otus_cpp::join {
session::session(boost::asio::ip::tcp::socket socket,
                 std::shared_ptr<table_keeper> tables)
    : socket_(std::move(socket)), tables_(tables) {
}

session::~session() {
}

void session::start() {
	read_line();
}

void session::read_line() {
	auto self(shared_from_this());
	boost::asio::async_read_until(
	    socket_, buffer_, '\n',
	    [this, self](boost::system::error_code ec,
	                 [[maybe_unused]] std::size_t length) {
		    if (!ec) {
			    std::string s((std::istreambuf_iterator<char>(&buffer_)),
			                  std::istreambuf_iterator<char>());
			    process_data(std::move(s));
		    }
	    });
}

void session::process_data(std::string str) {
	auto self(shared_from_this());
	boost::asio::post(socket_.get_executor(), [self, data = std::move(str)]() {
		auto answer = self->tables_->process_command(data);
		self->do_write(std::move(answer));
	});
}

void session::do_write(const std::string &response) {
	auto self(shared_from_this());
	boost::asio::async_write(
	    socket_, boost::asio::buffer(response.data(), response.size()),
	    [this, self](boost::system::error_code ec, std::size_t /*length*/) {
		    if (!ec) {
			    read_line(); // После записи ожидаем следующую команду
		    } else {
			    std::cerr << "Error in writing: " << ec.message() << "\n";
		    }
	    });
}

} // namespace otus_cpp::join