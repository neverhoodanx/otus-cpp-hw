/**
 *  OTUS homework module
 *  #5 graphic editor
 *  (c) 2024
 */
#pragma once

#include "shape_manager.hpp"

namespace otus_cpp::editor {
/**
 * View for displaying data
 */
class canvas {
  public:
	/**
	 * Updates the rendering of all primitives on the canvas
	 */
	virtual void render(const shape_manager &shapes);
};

} // namespace otus_cpp::editor