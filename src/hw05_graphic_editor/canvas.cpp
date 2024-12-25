/**
 *  OTUS homework module
 *  #5 graphic editor
 *  (c) 2024
 */
#include "canvas.hpp"

#include <iostream>

namespace otus_cpp::editor {

void canvas::render(const shape_manager &shapes) {
	std::cout << "canvas::render" << std::endl;
	shapes.draw_shapes();
}

} // namespace otus_cpp::editor