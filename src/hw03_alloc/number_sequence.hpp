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
 * @brief Calculate the factorial of a non-negative integer.
 *
 * This function computes the factorial of a given non-negative integer
 * using a recursive approach. The factorial of n (denoted as n!) is
 * the product of all positive integers less than or equal to n.
 *
 * @param n A non-negative integer whose factorial is to be calculated.
 * @return The factorial of the input integer n. Returns 1 if n is 0 or 1.
 */
constexpr uint32_t factorial(uint32_t n) {
	return n <= 1 ? 1 : (n * factorial(n - 1));
}

/**
 * @brief Calculate the nth Fibonacci number.
 *
 * This function computes the nth Fibonacci number using a recursive approach.
 * The Fibonacci sequence is defined as follows:
 * F(0) = 0, F(1) = 1, and F(n) = F(n-1) + F(n-2) for n > 1.
 *
 * @param n A non-negative integer representing the position in the Fibonacci
 * sequence.
 * @return The nth Fibonacci number.
 */
constexpr uint32_t fibonacci(uint32_t n) {
	return n <= 1 ? n : fibonacci(n - 1) + fibonacci(n - 2);
}
} // namespace otus_cpp
