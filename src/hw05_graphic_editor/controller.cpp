/**
 *  OTUS homework module
 *  #5 graphic editor
 *  (c) 2024
 */
#include "controller.hpp"

#include <iostream>

namespace otus_cpp::editor {

controller::controller(std::shared_ptr<shape_manager> m,
                       std::shared_ptr<canvas> v)
    : model(m), view(v) {
	std::cout << "controller created" << std::endl;
}

void controller::create_circle(double r, int x, int y) {
	std::cout << "controller::create_circle, r,x,y=" << r << "," << x << ","
	          << y << std::endl;
	model->add_shape(std::make_shared<circle>(r, x, y));
}

void controller::delete_shape(size_t index) {
	std::cout << "controller::delete_shape, index " << index << std::endl;
	model->remove_shape(index);
}

void controller::save_document(const std::string &filename) {
	std::cout << "controller::save_document, filename " << filename
	          << std::endl;
	model->save_to_file(filename);
}

void controller::load_document(const std::string &filename) {
	std::cout << "controller::load_document, filename " << filename
	          << std::endl;
	model->load_from_file(filename);
}

void controller::update_view() {
	std::cout << "controller::update_view" << std::endl;
	view->render(*model.get());
}

} // namespace otus_cpp::editor