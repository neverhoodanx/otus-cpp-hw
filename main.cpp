/**
 *  @file manual_test.cpp
 *  OTUS homework module
 *  manual test
 *  (c) 2025
 */

#include "hw13_ml_computer_vision/ml_classifier.hpp"
#include "hw13_ml_computer_vision/utility.hpp"

int main(int argc, char *argv[]) {
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " <W1> <W2> <TestData>"
		          << std::endl;
		return 1;
	}

	auto w1_path = std::string(argv[1]);
	auto w2_path = std::string(argv[2]);
	auto test_data_path = std::string(argv[3]);

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
	std::cout << "Model accuracy: " << accuracy * 100 << "%" << std::endl;
	return 0;
}