/**
 *  @file async_terminal.cpp
 *  OTUS homework module
 *  #9 async terminal
 *  (c) 2024
 */

#include "async_terminal.hpp"
#include "async_process.hpp"

namespace otus_cpp::async {

/**
 * @class async_terminal
 * @brief Represents an asynchronous terminal for processing commands.
 */
async_terminal::async_terminal(size_t block_size, size_t uid,
                               std::shared_ptr<async_process> handler) {
	std::string ctx_name = std::to_string(uid);
	parser_ = std::make_shared<otus_cpp::command_parser>(
	    block_size, [handler, ctx_name](const std::queue<std::string> &commands,
	                                    const std::string &time_point) {
		    handler->process_block(commands, ctx_name, time_point);
	    });
}

} // namespace otus_cpp::async