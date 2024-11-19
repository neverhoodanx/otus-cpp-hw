/**
 *  OTUS homework test module
 *  (c) 2024
 */

#include "graphic_editor/controller.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_graphic_editor)

class MockShapeManager : public otus_cpp::editor::shape_manager {
  public:
	void save_to_file(const std::string &filename) final {
		otus_cpp::editor::shape_manager::save_to_file(filename);
		check = true;
	};
	void load_from_file(const std::string &filename) final {
		otus_cpp::editor::shape_manager::load_from_file(filename);
		check = true;
	};

	void add_shape(std::shared_ptr<otus_cpp::editor::iShape> shape) final {
		otus_cpp::editor::shape_manager::add_shape(shape);
		check = true;
	}
	void remove_shape(size_t index) final {
		check = true;
		otus_cpp::editor::shape_manager::remove_shape(index);
	}
	bool check = false;
};

class MockCanvas : public otus_cpp::editor::canvas {
  public:
	void render(const otus_cpp::editor::shape_manager &shapes) final {
		otus_cpp::editor::canvas::render(shapes);
		check = true;
	}
	bool check = false;
};

BOOST_AUTO_TEST_CASE(test_create_circle) {
	auto mock_manager = std::make_shared<MockShapeManager>();
	auto mock_canvas = std::make_shared<MockCanvas>();
	otus_cpp::editor::controller ctrl(mock_manager, mock_canvas);

	ctrl.create_circle(10.0, 100, 100);

	BOOST_CHECK_EQUAL(mock_manager->check, true);
}

BOOST_AUTO_TEST_CASE(test_delete_shape) {
	auto mock_manager = std::make_shared<MockShapeManager>();
	auto mock_canvas = std::make_shared<MockCanvas>();
	otus_cpp::editor::controller ctrl(mock_manager, mock_canvas);
	ctrl.delete_shape(0);

	BOOST_CHECK_EQUAL(mock_manager->check, true);
}

BOOST_AUTO_TEST_CASE(test_save_document) {
	auto mock_manager = std::make_shared<MockShapeManager>();
	auto mock_canvas = std::make_shared<MockCanvas>();
	otus_cpp::editor::controller ctrl(mock_manager, mock_canvas);

	ctrl.save_document("test_file.txt");

	BOOST_CHECK_EQUAL(mock_manager->check, true);
}

BOOST_AUTO_TEST_CASE(test_load_document) {
	auto mock_manager = std::make_shared<MockShapeManager>();
	auto mock_canvas = std::make_shared<MockCanvas>();
	otus_cpp::editor::controller ctrl(mock_manager, mock_canvas);

	ctrl.load_document("test_file.txt");

	BOOST_CHECK_EQUAL(mock_manager->check, true);
}

BOOST_AUTO_TEST_CASE(test_update_view) {
	auto mock_manager = std::make_shared<MockShapeManager>();
	auto mock_canvas = std::make_shared<MockCanvas>();
	otus_cpp::editor::controller ctrl(mock_manager, mock_canvas);

	ctrl.update_view();

	BOOST_CHECK_EQUAL(mock_canvas->check, true);
}
BOOST_AUTO_TEST_SUITE_END()
