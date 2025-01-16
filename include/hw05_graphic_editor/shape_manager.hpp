/**
 *  OTUS homework module
 *  #5 graphic editor
 *  (c) 2024
 */
#pragma once

#include "iShape.hpp"

#include <memory>
#include <string>
#include <vector>

namespace otus_cpp::editor {
/**
 * @brief Model, storing graphical primitives
 */
class shape_manager {
  public:
	/**
	 * @brief Add some shape
	 * @param shape -
	 */
	virtual void add_shape(std::shared_ptr<iShape> shape);
	/**
	 * @brief Remove shape by index
	 * @param index - index of the figure
	 */
	virtual void remove_shape(size_t index);
	/**
	 * @brief Draw all shapes
	 */
	virtual void draw_shapes() const;
	/**
	 * @brief Save image file
	 * @param filename - filename for save
	 */
	virtual void load_from_file(const std::string &filename);
	/**
	 * @brief Load image file
	 * @param filename - filename for load
	 */
	virtual void save_to_file(const std::string &filename);
	/**
	 * @brief Vritual Dtor
	 */
	virtual ~shape_manager() = default;

  private:
	std::vector<std::shared_ptr<iShape>> shapes;
};

} // namespace otus_cpp::editor