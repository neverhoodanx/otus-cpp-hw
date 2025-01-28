/**
 *  @file async_terminal.hpp
 *  OTUS homework module
 *  #10 async tcp terminal
 *  (c) 2025
 */
#pragma once

#include <boost/asio.hpp>

namespace otus_cpp::nw_async {

class decorator_async;

/**
 * @class Server
 * @brief Listens for incoming client connections and manages sessions.
 */
class server {
  public:
	/**
	 * @brief Constructs a new Server object.
	 * @param io_context The io_context used for asynchronous operations.
	 * @param port The port on which the server listens for connections.
	 * @param bulk_size The size of the bulk of commands.
	 */
	server(boost::asio::io_context &io_context, short port, size_t bulk_size);
	/**
	 * @brief Stops the server from accepting new connections.
	 *
	 * This method stops the server's acceptor from listening for new
	 * connections, effectively shutting down the server.
	 */
	void stop();

  private:
	/**
	 * @brief Starts an asynchronous accept operation for incoming connections.
	 */
	void start_accept();
	/**
	 * @brief Acceptor used to listen for incoming connections.
	 */
	boost::asio::ip::tcp::acceptor acceptor_;
	/**
	 * @brief Client's socket
	 */
	boost::asio::ip::tcp::socket socket_;
	/**
	 * @brief Size of the bulk commands
	 */
	size_t bulk_size_;
	/**
	 * @brief Shared pointer to the decorator_async instance.
	 */
	std::shared_ptr<decorator_async> async_;
};
} // namespace otus_cpp::nw_async