/**
 *  @file join_sesion.hpp
 *  OTUS homework module
 *  #11 join sesion
 *  (c) 2025
 */
#pragma once

#include "table_keeper.hpp"

#include <boost/asio.hpp>

namespace otus_cpp::join {
/**
 * @class Bulk Session
 * @brief Handles a single client session, reading commands and processing them
 */
class session : public std::enable_shared_from_this<session> {
  public:
	/**
	 * @brief Constructs a new Session object
	 * @param socket The socket associated with the client
	 * @param bulk_size The size of the bulk of commands to be processed
	 */
	session(boost::asio::ip::tcp::socket socket,
	        std::shared_ptr<table_keeper> tables);

	~session();

	/**
	 * @brief Starts the session, initiating the asynchronous read operation
	 */
	void start();

  private:
	/**
	 * @brief Asynchronously reads a line from the client
	 */
	void read_line();
	/**
	 * @brief Asynchronously write a data to the client
	 */
	void do_write(const std::string &response);

	/**
	 * @brief Processes a single command from the client
	 * @param line The command to process
	 */
	void process_data(std::string str);

	/**
	 * @brief The socket associated with the client
	 */
	boost::asio::ip::tcp::socket socket_;
	/**
	 * @brief Buffer for storing received data
	 */
	boost::asio::streambuf buffer_;
	/**
	 * @brief Buffer for storing received data
	 */
	std::shared_ptr<table_keeper> tables_;
};
} // namespace otus_cpp::join