/**
 *  OTUS homework test module
 *  (c) 2025
 */

#include <boost/test/unit_test.hpp>

#include "hw13_ml_computer_vision/ml_classifier.hpp"
#include "hw13_ml_computer_vision/utility.hpp"

BOOST_AUTO_TEST_SUITE(MlpClassifier)

// Тест predict
BOOST_AUTO_TEST_CASE(MlpClassifier_predict) {
	auto w1_path = std::string("w1.txt");
	auto w2_path = std::string("w2.txt");
	auto test_data_path = std::string("test.csv");

	const int input_size = 784;  // Размерность входных данных
	const int hidden_size = 128; // Размерность скрытого слоя
	const int output_size = 10;  // Размерность выходного слоя

	// Загрузка весов
	auto w1 =
	    otus_cpp::ml::load_matrix_from_file(w1_path, input_size, hidden_size);
	auto w2 =
	    otus_cpp::ml::load_matrix_from_file(w2_path, hidden_size, output_size);

	// Загрузка тестовых данных
	std::vector<Eigen::VectorXf> x_test;
	std::vector<int> y_test;
	otus_cpp::ml::load_csv_data(test_data_path, x_test, y_test, input_size);

	otus_cpp::ml::ml_classifier ml = {w1, w2};
	int correct_predictions = 0;
	int label_index = 0;
	for (const auto &x : x_test) {
		auto res = ml.predict(x);
		if (res == y_test[label_index++]) {
			correct_predictions++;
		}
	}

	double accuracy = static_cast<double>(correct_predictions) / x_test.size();
	BOOST_CHECK_CLOSE(0.885, accuracy, 1);
}

BOOST_AUTO_TEST_SUITE_END()