/**
 *  @file utility.hpp
 *  OTUS homework module
 *  #13 utility:
 *  (c) 2025
 */
#pragma once

#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <vector>

namespace otus_cpp::ml {

Eigen::MatrixXf load_matrix_from_file(const std::string &filename, int rows,
                                      int cols) {
	Eigen::MatrixXf matrix(rows, cols);
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error{"Cannot open file"};
	}
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			file >> matrix(i, j);
		}
	}
	file.close();
	return matrix.transpose();
}

void load_csv_data(const std::string &filename, std::vector<Eigen::VectorXf> &X,
                   std::vector<int> &y, int total) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error{"Cannot open file"};
	}

	std::string line;
	while (std::getline(file, line)) {
		Eigen::VectorXf x(total);
		int label;
		std::stringstream ss(line);
		std::string value;

		std::getline(ss, value, ',');
		label = std::stoi(value);

		// Считываем пиксели
		int index = 0;
		while (std::getline(ss, value, ',')) {
			if (index >= total)
				break;
			x(index++) = std::stof(value) / 255.0f;
		}

		X.push_back(x);
		y.push_back(label);
	}

	file.close();
}

} // namespace otus_cpp::ml