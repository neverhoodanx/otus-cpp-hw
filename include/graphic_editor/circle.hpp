/**
 *  OTUS homework module
 *  #5 graphic editor
 *  (c) 2024
 */
#pragma once

#include "iShape.hpp"

namespace otus_cpp::editor {
/**
 * @brief The circle implementation is inherited from the shape interface
 */
class circle final : public iShape {
  public:
	/**
	 * @brief Ctor
	 * @param r - radius
	 * @param x - coordinate horizontal X-axis
	 * @param y - coordinate vertical Y-axis
	 */
	circle(double r, int x, int y);
	/**
	 * @override iShape
	 */
	void draw() final;
	/**
	 * @override iShape
	 */
	void move(int x, int y) final;
	/**
	 *  @override iShape
	 */
	void resize(double factor) final;

  private:
	double radius;
	int centerX;
	int centerY;
};

} // namespace otus_cpp::editor