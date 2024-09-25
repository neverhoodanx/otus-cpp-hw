/**
 *  OTUS homework module
 *  #3 Custom OtusAllocator
 *  (c) 2024
 */
#pragma once

#include <iostream>
#include <limits>
#include <memory>

namespace otus_cpp {
/**
 * Custom Allocator
 * T - type
 * N - size_ of the preallocated memory
 */
template <class T, std::size_t N = 10> struct custom_allocator {
	using value_type = T;
	using size_type = size_t;

	// using pointer = T *;
	// using const_pointer = const T *;
	// using reference = T &;
	// using const_reference = const T &;

/**
 * I don't know how to do it right, but stl containers allocates 'end' on the
 * heap if you run on Windows
 */
#ifdef WIN32
	static constexpr int size_ = sizeof(T) * (N + 1);
	static constexpr int block_size_ = (N + 1);
#else
	static constexpr int size_ = sizeof(T) * N;
	static constexpr int block_size_ = N;
#endif
	static int pos_;             // current pos_ in pre reserved memory
	static uint8_t data_[size_]; // reserve and align
	static T *ptr_;

	/**
	 * Ctor
	 */
	custom_allocator() noexcept = default;
	/**
	 * Dtor
	 */
	~custom_allocator() = default;
	/**
	 * Copy ctor
	 */
	custom_allocator(const custom_allocator &) {}
	/**
	 * Copy conversion constructor
	 */
	template <class U>
	custom_allocator(const custom_allocator<U, N> &) noexcept {}

	// custom_allocator(custom_allocator &&other) noexcept {}
	// custom_allocator &operator=(const custom_allocator &other) {} // can be
	// return *this custom_allocator &operator=(custom_allocator &&other)
	// noexcept {} // propagation

	/**
	 * Allocate
	 * @param n - number of objects
	 */
	T *allocate(std::size_t n) {
		// std::cout << "allocate n:" << n << " pos_: " << pos_ << std::endl;
		if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
			throw std::bad_alloc();
		}
		if (pos_ + n > block_size_) {
			// std::cout << "new alloc on n: " << n << std::endl;
			return reinterpret_cast<T *>(::operator new(sizeof(T) * n));
		}
		int cur = pos_;
		pos_ += static_cast<int>(n);
		return reinterpret_cast<T *>(data_) + cur;
	}

	/**
	 * deallocate
	 * @param p - poinert to memeory
	 * @param n - number of objects
	 */
	void deallocate(T *p, std::size_t n) {
		// std::cout << "deallocate n:" << n << std::endl;
		if (!in_buf_memory(p)) {
			// std::cout << "delete free n:" << n << std::endl;
			::operator delete(p);
		}
		if (p == (reinterpret_cast<T *>(data_) + (pos_ - n))) {
			// std::cout << "free n:" << n << std::endl;
			pos_ -= static_cast<int>(n);
		}
	}

	/**
	 * Rebined for compatibility with other type, like node in list
	 */
	template <class U> struct rebind {
		typedef custom_allocator<U, N> other;
	};
	/**
	 * check the pointer from our memory or from the heap
	 */
	static bool in_buf_memory(T *p) {
		return ((reinterpret_cast<T *>(data_) <= p) &&
		        (p <= reinterpret_cast<T *>(data_) + N));
	}
};

template <typename T, std::size_t N>
uint8_t custom_allocator<T, N>::data_[size_];

template <typename T, std::size_t N> int custom_allocator<T, N>::pos_ = 0;

template <typename T, std::size_t N> T *custom_allocator<T, N>::ptr_ = nullptr;

template <class T, class U, std::size_t N>
constexpr bool operator==(const custom_allocator<T, N> &a1,
                          const custom_allocator<U, N> &a2) noexcept {
	return true;
}

template <class T, class U, std::size_t N>
constexpr bool operator!=(const custom_allocator<T, N> &a1,
                          const custom_allocator<U, N> &a2) noexcept {
	return false;
}
} // namespace otus_cpp