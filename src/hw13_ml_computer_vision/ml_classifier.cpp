/**
 *  @file ml_classifier.cpp
 *  OTUS homework module
 *  #13 classifier
 *  (c) 2025
 */

#include "ml_classifier.hpp"

namespace otus_cpp::ml {

template <typename T> auto sigma(T x) {
	return 1 / (1 + std::exp(-x));
}

Eigen::VectorXf sigmoid(const Eigen::VectorXf &z) {
	Eigen::VectorXf exp_z{z.rows()};
	for (Eigen::Index i = 0; i < z.rows(); ++i) {
		exp_z(i) = sigma(z(i));
	}
	return exp_z;
}

Eigen::VectorXf softmax(const Eigen::VectorXf &z) {
	Eigen::VectorXf exp_z{z.rows()};
	float denominator = 0.0f;
	for (Eigen::Index i = 0; i < z.rows(); ++i) {
		denominator += std::exp(z(i));
	}
	for (Eigen::Index i = 0; i < z.rows(); ++i) {
		exp_z(i) = std::exp(z(i)) / denominator;
	}
	return exp_z;
}

size_t ml_classifier::predict(const Eigen::VectorXf &data) {
	auto o1 = sigmoid(w1_ * data);
	auto o2 = softmax(w2_ * o1);

	std::vector<float> res;
	for (Eigen::Index i = 0; i < o2.rows(); ++i) {
		res.push_back(o2(i));
	}
	auto argmax = std::max_element(res.begin(), res.end());
	int predictedClass = std::distance(res.begin(), argmax);
	return static_cast<size_t>(predictedClass);
}
} // namespace otus_cpp::ml