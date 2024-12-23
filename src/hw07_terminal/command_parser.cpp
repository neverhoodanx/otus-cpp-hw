/**
 *  OTUS homework module
 *  #7 terminal
 *  (c) 2024
 */

#include "command_parser.hpp"

namespace otus_cpp {
command_parser::command_parser(
    size_t block_size,
    std::function<void(std::queue<std::string>, std::string)> call_back)
    : block_size_{block_size}, call_back_{call_back} {
}

void command_parser::push_chunk(const std::string &data) {
	if (manage_block_state(data[0])) {
		return; // We're either starting a dynamic block or still inside one
	}

	if (time_.empty()) {
		time_ = std::to_string(std::time(nullptr));
	}

	buffer_.push(data);
	if (++block_count_ == block_size_ && block_start_count_ == 0) {
		handle_blocks();
	}
}

void command_parser::handle_blocks() {
	if (buffer_.empty() || block_start_count_ > 0) {
		return; // Don't process if inside a dynamic block
	}

	call_back_(buffer_, time_);
	// Clear state
	std::queue<std::string> empty;
	std::swap(buffer_, empty);
	block_count_ = 0;
	time_.clear();
}

bool command_parser::manage_block_state(char ch) {
	if (ch == '{') {
		if (block_start_count_ == 0) {
			handle_blocks(); // Finish any pending static block
		}
		++block_start_count_;
		return true;
	}
	if (ch == '}') {
		if (block_start_count_ > 0) {
			--block_start_count_;
			if (block_start_count_ == 0) {
				handle_blocks(); // Process the commands collected outside
				                 // dynamic blocks
			}
		}
		return true;
	}
	return false;
}
} // namespace otus_cpp