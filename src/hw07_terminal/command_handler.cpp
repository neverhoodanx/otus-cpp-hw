/**
 *  OTUS homework module
 *  #7 terminal
 *  (c) 2024
 */

#include "command_handler.hpp"

namespace otus_cpp {
command_handler::command_handler(std::ostream &output_stream)
    : out_{output_stream} {
}

void command_handler::process_block(std::queue<std::string> commands,
                                    const std::string &time) {
	if (commands.empty())
		return;

	std::string filename = "bulk" + time + ".log";

	std::ofstream file(filename);
	if (!file) {
		std::cerr << "Error creating file " << filename << std::endl;
		return;
	}

	while (!commands.empty()) {
		auto comm = commands.front();
		commands.pop();
		if (!commands.empty()) {
			out_ << comm << ", ";
			file << comm << ", ";
		} else {
			out_ << comm;
			file << comm;
		}
	}
	out_ << std::endl;
	file << std::endl;
}
} // namespace otus_cpp