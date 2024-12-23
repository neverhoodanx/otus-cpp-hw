/**
 *  OTUS homework module
 *  #7 terminal
 *  (c) 2024
 */
#pragma once

#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>

namespace otus_cpp {
/**
 * @class Interface for command_handler
 * @brief Responsible for processing command blocks.
 */
struct i_command_handler {
	/**
	 * @brief Processes a block of commands, logs them to console and a file.
	 * @param commands Queue of commands to process.
	 * @param time The initial time point
	 */
	virtual void process_block(const std::queue<std::string> &commands,
	                           const std::string &time) = 0;
	/**
	 * @brief Vritual Dtor
	 */
	virtual ~i_command_handler() = default;
};
} // namespace otus_cpp