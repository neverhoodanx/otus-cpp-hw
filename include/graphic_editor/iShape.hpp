/**
 *  OTUS homework module
 *  #5 graphic editor
 *  (c) 2024
 */
#pragma once

namespace otus_cpp::editor {
/**
 * @brief Interface for the shape class
 */
struct iShape {
	/**
	 * @brief Draw shape
	 */
	virtual void draw() = 0;
	/**
	 * @brief Change posoztion on canvs
	 * @param x - coordinate horizontal X-axis
	 * @param y - coordinate vertical Y-axis
	 */
	virtual void move(int x, int y) = 0;
	/**
	 * @brief Change size
	 * @param factor - scale factor
	 */
	virtual void resize(double factor) = 0;
	/**
	 * @brief Vritual Dtor
	 */
	virtual ~iShape() = default;
};

} // namespace otus_cpp::editor