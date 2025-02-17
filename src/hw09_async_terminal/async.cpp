/**
 *  @file async.cpp
 *  @brief Contains implementations for asynchronous terminal operations.
 *  OTUS homework module
 *  #9 async terminal
 *  (c) 2024
 */

#include "async.hpp"
#include "async_terminal.hpp"

#include <map>
#include <memory>
#include <mutex>
#include <sstream>
#include <stdexcept>

namespace otus_cpp::async {

/**
 * @var contexts
 * @brief Map that stores active contexts associated with their async_terminal
 * instances.
 */
std::map<Context, std::unique_ptr<async_terminal>> contexts;

/**
 * @var contextsMutex
 * @brief Mutex for ensuring thread-safe access to the contexts map.
 */
std::mutex contextsMutex;

/**
 * @var handler_
 * @brief Shared handler for managing async processing operations.
 */
std::shared_ptr<async_process> handler_;

/**
 * @brief Connects a new context and sets up async processing capabilities.
 * @param block_size The block size for the context.
 * @return A Context handle that can be used in subsequent operations.
 */
Context connect(std::size_t block_size) {
	std::lock_guard<std::mutex> lock(contextsMutex);
	static size_t uid = 0;
	if (!handler_) {
		handler_ = std::make_shared<async_process>(3);
	}
	auto executor =
	    std::make_unique<async_terminal>(block_size, uid++, handler_);
	Context ctx = reinterpret_cast<Context>(executor.get());
	{
		contexts[ctx] = std::move(executor);
	}
	return ctx;
}

/**
 * @brief Processes received data for a given context.
 * @param context The context to process the data with.
 * @param data The input data string.
 * @param size The size of the input data.
 */
void receive(Context context, const char *data, std::size_t size) {
	std::lock_guard<std::mutex> lock(contextsMutex);
	auto it = contexts.find(context);
	if (it != contexts.end()) {
		if (size == 0) {
			it->second->parser_->push_chunk(std::string());
			return;
		}
		std::string buf(data, size);
		std::istringstream stream(buf);
		std::string word;
		while (stream >> word) {
			it->second->parser_->push_chunk(word);
		}
	} else {
		std::cerr << "Invalid context" << std::endl;
	}
}

/**
 * @brief Disconnects and cleans up the specified context and its resources.
 * @param context The context to be disconnected.
 */
void disconnect(Context context) {
	std::lock_guard<std::mutex> lock(contextsMutex);
	auto it = contexts.find(context);
	if (it != contexts.end()) {
		it->second->parser_->handle_blocks();
		contexts.erase(it);
	} else {
		std::cerr << "Invalid context" << std::endl;
	}
	if (contexts.empty()) {
		handler_.reset();
	}
}

} // namespace otus_cpp::async