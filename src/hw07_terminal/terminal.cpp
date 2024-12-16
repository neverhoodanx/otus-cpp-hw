/**
 *  OTUS homework module
 *  #7 terminal
 *  (c) 2024
 */

#include "hw07_terminal/terminal.hpp"

#include "command_handler.hpp"
#include "command_parser.hpp"

namespace otus_cpp {
terminal::terminal(size_t block_size, std::istream &input_stream,
                   std::ostream &output_stream)
    : input_{input_stream} {
	handler_.push_back(std::make_shared<command_handler>(output_stream));
	parser_ = std::make_shared<command_parser>(
	    block_size, [this](const std::queue<std::string> &commands,
	                       const std::string &time_point) {
		    for (const auto &val : handler_) {
			    val->process_block(commands, time_point);
		    }
	    });
}

void terminal::run() {
	std::string input;
	while (std::getline(input_, input)) {
		parser_->push_chunk(input);
	}
	parser_->handle_blocks();
}

} // namespace otus_cpp