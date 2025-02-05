/**
 *  @file decorator_async.hpp
 *  OTUS homework module
 *  #10 Decorator for async
 *  (c) 2025
 */
#pragma once
#include "hw09_async_terminal/async.hpp"
#include <string>

namespace otus_cpp::nw_async {

/**
 * @class decorator_async
 * @brief A class that acts as a decorator for asynchronous operations.
 *
 * This class is designed to wrap around an existing asynchronous interface and
 * provide additional functionality such as sending internal and external data,
 * connecting and disconnecting contexts, and flushing data.
 */
class decorator_async {
  public:
	/**
	 * @brief Ctor
	 * @param bulk_size The size of the bulk data.
	 */
	decorator_async(size_t bulk_size);

	/**
	 * @brief Destructor for decorator_async.
	 * Cleans up any resources held by the decorator.
	 */
	~decorator_async();

	/**
	 * @brief Sends internal data through the context.
	 * This method sends internal data using the provided context.
	 * @param ctx The context through which the data should be sent.
	 * @param data The string data to be sent.
	 */
	void send_internal_data(otus_cpp::async::Context ctx,
	                        const std::string &data);

	/**
	 * @brief Sends external data.
	 * This method sends external data directly without using a specific
	 * context.
	 * @param data The string data to be sent.
	 */
	void send_external_data(const std::string &data);

	/**
	 * @brief Connects to the asynchronous system.
	 * Establishes a connection and returns a context that can be used for
	 * further operations.
	 * @return The context representing the connection.
	 */
	otus_cpp::async::Context connect();

	/**
	 * @brief Disconnects from the asynchronous system.
	 * Ends the connection represented by the given context.
	 * @param ctx The context to be disconnected.
	 */
	void disconnect(otus_cpp::async::Context ctx);

	/**
	 * @brief Flushes any pending data.
	 * Forces the immediate transmission of any buffered data.
	 */
	void flush();

  private:
	/**
	 * @brief The context for external blocks.
	 * This member holds the context for handling external data blocks.
	 */
	otus_cpp::async::Context external_blocks_;

	/**
	 * @brief The size of the bulk data.
	 * This member specifies the size of the bulk data for processing.
	 */
	size_t bulk_size_;
};

} // namespace otus_cpp::nw_async