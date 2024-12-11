/**
 *  OTUS homework module
 *  manual test
 *  (c) 2024
 */

#include "hw07_terminal/terminal.hpp"
// #include "lib.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
	// #7 HomeWork: terminal
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <block_size>" << std::endl;
		return 1;
	}

	size_t block_size = std::stoi(argv[1]);
	otus_cpp::terminal terminal_(block_size, std::cin, std::cout);
	terminal_.run();
	return 0;

	// #6 HomeWork: N Matrix
	// try {
	// 	otus_cpp::technical_task_matrix();
	// } catch (const std::exception &e) {
	// 	std::cerr << e.what() << std::endl;
	// 	return -1;
	// }

	// #5 HomeWork: Graphic Editor
	// try {
	// 	otus_cpp::technical_task_graphic_editor();
	// } catch (const std::exception &e) {
	// 	std::cerr << e.what() << std::endl;
	// 	return -1;
	// }

	// #4 HomeWork: SFINAE + Doxygen
	// try {
	// 	otus_cpp::technical_task_sfinae();
	// } catch (const std::exception &e) {
	// 	std::cerr << e.what() << std::endl;
	// 	return -1;
	// }

	// #3 HomeWork: Custom allocator
	// try {
	// 	otus_cpp::technical_task_allocators();
	// } catch (const std::exception &e) {
	// 	std::cerr << e.what() << std::endl;
	// 	return -1;
	// }

	// #2 HomeWork: ip filter
	// try {
	// 	otus_cpp::technical_task_ip_filter();
	// } catch (const std::exception &e) {
	// 	std::cerr << e.what() << std::endl;
	// }

	// #1 HomeWork: hello world
	// std::cout << "Version: " << otus_cpp::version() << std::endl;
	// std::cout << "Hello, world!" << std::endl;

	return 0;
}
