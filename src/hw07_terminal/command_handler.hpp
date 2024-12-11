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
 * @class CommandHandler
 * @brief Responsible for processing and logging command blocks.
 */
class command_handler {
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
	 */
	void process_block(std::queue<std::string> commands, const std::string &time);

  private:
	std::ostream &out_; ///< Output stream for logging commands
};
} // namespace otus_cpp