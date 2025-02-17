/**
 *  @file async_terminal.hpp
 *  OTUS homework module
 *  #9 async terminal
 *  (c) 2024
 */
#pragma once

#include "async_process.hpp"
#include "hw07_terminal/command_parser.hpp"
#include "hw07_terminal/i_command_handler.hpp"

namespace otus_cpp::async {

/**
 * @class async_terminal
 * @brief Represents an asynchronous terminal for processing command blocks.
 */
class async_terminal {
  public:
	/**
	 * @brief Constructs an async_terminal object.
	 * @param block_size Maximum number of commands in a block.
	 * @param uid Unique identifier for the terminal session.
	 * @param handler Shared pointer to an async_process handler.
	 */
	async_terminal(size_t block_size, size_t uid,
	               std::shared_ptr<async_process> handler);

	std::shared_ptr<otus_cpp::command_parser>
	    parser_; ///< Parser for processing commands.
};

} // namespace otus_cpp::async