/**
 *  OTUS homework module
 *  #7 terminal
 *  (c) 2024
 */
#pragma once

#include "i_command_handler.hpp"

#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>

namespace otus_cpp {
/**
 * @class command_handler
 * @brief Responsible for processing and logging command blocks.
 */
class command_handler final : public i_command_handler {
  public:
	/**
	 * @brief Constructs a CommandHandler with the specified output stream.
	 * @param output_stream The output stream to which command blocks will be
	 * written.
	 */
	command_handler(std::ostream &output_stream);

	/**
	 * @brief Processes a block of commands, logs them to console and a file.
	 * @param commands Queue of commands to process.
	 * @param time The initial time point
	 */
	void process_block(const std::queue<std::string> &commands,
	                   const std::string &time);

  private:
	std::ostream &out_; ///< Output stream for logging commands
};
} // namespace otus_cpp