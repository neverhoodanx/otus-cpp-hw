/**
 *  OTUS homework module
 *  #3 Custom OtusAllocator
 *  Number sequence
 *  (c) 2024
 */
#pragma once

#include <cstdint>

namespace otus_cpp {
/**
 * Calc factorial
 */
constexpr uint32_t factorial(uint32_t n) {
	return n <= 1 ? 1 : (n * factorial(n - 1));
}

/**
 * Calc fibonacci
 */
constexpr uint32_t fibonacci(uint32_t n) {
	return n <= 1 ? n : fibonacci(n - 1) + fibonacci(n - 2);
}
} // namespace otus_cpp
