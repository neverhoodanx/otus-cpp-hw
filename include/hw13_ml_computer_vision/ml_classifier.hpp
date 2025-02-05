/**
 *  @file ml_classifier.hpp
 *  OTUS homework module
 *  #13 classifier
 *  (c) 2025
 */
#pragma once

#include <Eigen/Dense>

namespace otus_cpp::ml {
struct ml_classifier {
	Eigen::MatrixXf w1_;
	Eigen::MatrixXf w2_;
	size_t predict(const Eigen::VectorXf &data);
};
} // namespace otus_cpp::ml