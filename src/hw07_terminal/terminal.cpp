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
    : input_{input_stream},
      handler_{std::make_shared<command_handler>(output_stream)},
      parser_{std::make_shared<command_parser>(block_size, handler_)} {
}

void terminal::run() {
	std::string input;
	while (std::getline(input_, input)) {
		parser_->push_chunk(input);
	}
	parser_->handle_blocks();
}

} // namespace otus_cpp