/**
 *  OTUS homework module
 *  #7 terminal
 *  (c) 2024
 */
#pragma once

#include "command_handler.hpp"
#include <functional>
#include <memory>

namespace otus_cpp {
/**
 * @class command_parser
 * @brief Parses input commands and manages blocks of commands.
 */
class command_parser {
  public:
	/**
	 * @brief Constructs a Parser with the given block size and CommandHandler.
	 * @param block_size Number of commands per static block.
	 * @param handler The CommandHandler responsible for processing completed
	 * blocks.
	 */
	command_parser(
	    size_t block_size,
	    std::function<void(std::queue<std::string>, std::string)> call_back);

	/**
	 * @brief Attempts to add a command to the current block.
	 * @param data Command to process.
	 */
	void push_chunk(const std::string &data);

	/**
	 * @brief Processes a completed block of commands.
	 */
	void handle_blocks();

  private:
	/**
	 * @brief Manages the state of dynamic blocks based on the provided
	 * character.
	 * @param ch Character to be checked ('{' or '}').
	 * @return True if a block state change occurs, false otherwise.
	 */
	bool manage_block_state(char ch);

	std::queue<std::string> buffer_;
	size_t block_count_ = 0;
	size_t block_size_;
	size_t block_start_count_ = 0;
	std::string time_;
	std::function<void(std::queue<std::string>, std::string)> call_back_;
};
} // namespace otus_cpp