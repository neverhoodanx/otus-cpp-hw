/**
 *  OTUS homework module
 *  #7 terminal
 *  (c) 2024
 */
#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace otus_cpp {

struct i_command_handler;
class command_parser;

/**
 * @class terminal
 * @brief Manages the input stream and processes commands using a Parser.
 */
class terminal {
  public:
	/**
	 * @brief Constructs a Terminal with the specified block size, input, and
	 * output streams.
	 * @param block_size Number of commands per static block.
	 * @param input_stream Stream from which commands are read.
	 * @param output_stream Stream to which results are written.
	 */
	terminal(size_t block_size, std::istream &input_stream,
	         std::ostream &output_stream);

	/**
	 * @brief Reads commands from the input stream and processes them.
	 */
	void run();

  private:
	std::istream &input_;
	std::vector<std::shared_ptr<i_command_handler>> handler_;
	std::shared_ptr<command_parser> parser_;
};
} // namespace otus_cpp