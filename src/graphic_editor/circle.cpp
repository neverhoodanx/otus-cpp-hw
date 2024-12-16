/**
 *  OTUS homework module
 *  #5 graphic editor
 *  (c) 2024
 */
#include "circle.hpp"

#include <iostream>

namespace otus_cpp::editor {

circle::circle(double r, int x, int y) : radius(r), centerX(x), centerY(y) {
	std::cout << "circle::circle" << std::endl;
};

void circle::draw() {
	std::cout << "circle::draw" << std::endl;
};

void circle::move(int x, int y) {
	centerX = x;
	centerY = y;
	std::cout << "circle::move, x,y=" << x << "," << y << std::endl;
};

void circle::resize(double factor) {
	radius = radius*factor;
	std::cout << "circle::resize, factor" << factor << std::endl;
};

} // namespace otus_cpp::editor