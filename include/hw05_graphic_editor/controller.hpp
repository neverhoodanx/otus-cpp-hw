/**
 *  OTUS homework module
 *  #5 graphic editor
 *  (c) 2024
 */
#pragma once

#include "canvas.hpp"
#include "circle.hpp"
#include "shape_manager.hpp"

namespace otus_cpp::editor {
/**
 * @brief Manage the interaction between the shape_manager (model) and the
 * canvas (view)
 */
class controller {
  public:
	/**
	 * @brief Ctor
	 * @param m - Shape manager
	 * @param v - canvas
	 */
	controller(std::shared_ptr<shape_manager> m, std::shared_ptr<canvas> v);
	/**
	 * @brief Create circle on canvas
	 */
	void create_circle(double r, int x, int y);
	/**
	 * @brief Delete figure by index
	 * @param index - the index of the figure
	 */
	void delete_shape(size_t index);
	/**
	 * @brief Save image file
	 * @param filename - filename for save
	 */
	void save_document(const std::string &filename);
	/**
	 * @brief Load image file
	 * @param filename - filename for load
	 */
	void load_document(const std::string &filename);
	/**
	 * @brief Re-render canvas
	 */
	void update_view();

  private:
	std::shared_ptr<shape_manager> model;
	std::shared_ptr<canvas> view;
};

} // namespace otus_cpp::editor