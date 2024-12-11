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

void command_handler::process_block(const std::queue<std::string> &commands,
                                    const std::string &time) {
	if (commands.empty())
		return;

	std::string filename = "bulk" + time + ".log";

	std::ofstream file(filename);
	if (!file) {
		std::cerr << "Error creating file " << filename << std::endl;
		return;
	}
	std::queue<std::string> temp = commands;
	while (!temp.empty()) {
		auto comm = temp.front();
		temp.pop();
		if (!temp.empty()) {
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