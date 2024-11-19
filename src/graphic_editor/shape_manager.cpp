/**
 *  OTUS homework module
 *  #5 graphic editor
 *  (c) 2024
 */

#include "shape_manager.hpp"

#include <iostream>

namespace otus_cpp::editor {

void shape_manager::add_shape(std::shared_ptr<iShape> shape) {
	std::cout << "shape_manager::add_shape" << std::endl;
	shapes.push_back(shape);
}

void shape_manager::remove_shape(size_t index) {
	std::cout << "shape_manager::remove_shape" << std::endl;
	if (index < shapes.size()) {
		shapes.erase(shapes.begin() + index);
	}
}

void shape_manager::draw_shapes() const {
	std::cout << "shape_manager::draw_shapes" << std::endl;
	for (const auto &shape : shapes) {
		shape->draw();
	}
}

void shape_manager::load_from_file(const std::string &filename) {
	std::cout << "shape_manager::load_from_file, filename " << filename
	          << std::endl;
}

void shape_manager::save_to_file(const std::string &filename) {
	std::cout << "shape_manager::save_to_file, filename " << filename
	          << std::endl;
}

} // namespace otus_cpp::editor