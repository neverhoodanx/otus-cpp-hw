/**
 *  @file async_terminal.hpp
 *  OTUS homework module
 *  #10 bulk sesion
 *  (c) 2025
 */
#pragma once

#include "decorator_async.hpp"

#include <boost/asio.hpp>
#include <deque>

namespace otus_cpp::nw_async {
/**
 * @class Bulk Session
 * @brief Handles a single client session, reading commands and processing them.
 */
class bulk_session : public std::enable_shared_from_this<bulk_session> {
  public:
	/**
	 * @brief Constructs a new Session object.
	 * @param socket The socket associated with the client.
	 * @param bulk_size The size of the bulk of commands to be processed.
	 */
	bulk_session(boost::asio::ip::tcp::socket socket, size_t bulk_size,
	             std::shared_ptr<decorator_async> async);

	~bulk_session();

	/**
	 * @brief Starts the session, initiating the asynchronous read operation.
	 */
	void start();

  private:
	/**
	 * @brief Asynchronously reads a line from the client.
	 */
	void read_line();

	/**
	 * @brief Processes a single command from the client.
	 * @param line The command to process.
	 */
	void process_command(const std::string &line);

	/**
	 * @brief
	 */
	void manage_block_state(char ch);

	/**
	 * @brief The socket associated with the client.
	 */
	boost::asio::ip::tcp::socket socket_;
	/**
	 * @brief Buffer for storing received data
	 */
	boost::asio::streambuf buffer_;
	/**
	 * @brief Size of the bulk commands
	 */
	size_t bulk_size_;
	/**
	 * @brief Current batch of commands
	 */
	std::deque<std::string> current_batch_;
	/**
	 * @brief Indicates if a dynamic block is active
	 */
	bool dynamic_block_active_ = false;
	/**
	 * @brief Shared pointer to the decorator_async instance.
	 */
	std::shared_ptr<decorator_async> async_;
	/**
	 * @brief Counter for the start of a block.
	 * This member keeps track of the number of times a block has started, which 
     * helps in managing multiple blocks.
	 */
	uint32_t block_start_count_;
	/**
	 * @brief Context for internal blocks.
	 */
	otus_cpp::async::Context internal_blocks_;
};
} // namespace otus_cpp::nw_async