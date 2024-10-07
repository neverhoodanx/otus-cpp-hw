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
 * @brief Custom Allocator
 *
 * This struct provides a custom memory allocator that preallocates a block
 * of memory for objects of type T. It manages memory allocation and
 * deallocation, allowing for efficient memory usage
 *
 * @tparam T Type of objects to allocate
 * @tparam N Size of the preallocated memory block (default is 10)
 */
template <class T, std::size_t N = 10> struct custom_allocator {
	using value_type = T;     ///< Type of the allocated objects
	using size_type = size_t; ///< Type for sizes of allocations

/**
 * I don't know how to do it right, but stl containers allocates 'end' on the
 * heap if you run on Windows
 */
#ifdef WIN32
	static constexpr int size_ = sizeof(T) * (N + 1); ///< Memory reserved
	static constexpr int block_size_ = (N + 1);       ///< Block size
#else
	static constexpr int size_ = sizeof(T) * N; ///< Memory reserved
	static constexpr int block_size_ = N;       ///< Block size
#endif
	static int pos_; ///< Current position in the pre-reserved memory
	static uint8_t data_[size_]; ///< Reserved and aligned memory block
	static T *ptr_;              ///< Pointer to the allocated memory

	/**
	 * @brief Ctor
	 */
	custom_allocator() noexcept = default;
	/**
	 * @brief Dtor
	 */
	~custom_allocator() = default;
	/**
	 * @brief Copy ctor
	 */
	custom_allocator(const custom_allocator &) {}
	/**
	 * @brief Copy conversion constructor
	 */
	template <class U>
	custom_allocator(const custom_allocator<U, N> &) noexcept {}

	/**
	 * @brief Allocates memory for a number of objects
	 *
	 * If the requested allocation exceeds the preallocated block, it falls back
	 * to standard allocation from the heap
	 *
	 * @param n Number of objects to allocate
	 * @return Pointer to the allocated memory
	 * @throws std::bad_alloc If the allocation fails
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
	 * @brief Deallocates memory for a number of objects
	 *
	 * If the pointer belongs to the preallocated memory, it simply updates
	 * the position. Otherwise, it calls the standard deallocation
	 *
	 * @param p Pointer to the memory to deallocate
	 * @param n Number of objects to deallocate
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
	 * @brief Rebinds the allocator to another type
	 *
	 * Allows for compatibility with other types, such as nodes in a list
	 *
	 * @tparam U The new type to bind to
	 */
	template <class U> struct rebind {
		typedef custom_allocator<U, N> other; ///< The new allocator type
	};
	/**
	 * @brief Checks if a pointer belongs to the preallocated memory buffer
	 *
	 * @param p Pointer to check
	 * @return True if the pointer is within the preallocated buffer, false
	 * otherwise
	 */
	static bool in_buf_memory(T *p) {
		return ((reinterpret_cast<T *>(data_) <= p) &&
		        (p <= reinterpret_cast<T *>(data_) + N));
	}
};

// Static member definitions
template <typename T, std::size_t N>
uint8_t custom_allocator<T, N>::data_[size_];

template <typename T, std::size_t N> int custom_allocator<T, N>::pos_ = 0;

template <typename T, std::size_t N> T *custom_allocator<T, N>::ptr_ = nullptr;

/**
 * @brief Inequality operator for custom allocators
 *
 * @tparam T Type of objects allocated by the first allocator
 * @tparam U Type of objects allocated by the second allocator
 * @param a1 First custom allocator to compare
 * @param a2 Second custom allocator to compare
 * @return True if both allocators are considered different, false otherwise
 */
template <class T, class U, std::size_t N>
constexpr bool operator==(const custom_allocator<T, N> &a1,
                          const custom_allocator<U, N> &a2) noexcept {
	return true;
}

/**
 * @brief Inequality operator for custom allocators
 *
 * @tparam T Type of objects allocated by the first allocator
 * @tparam U Type of objects allocated by the second allocator
 * @param a1 First custom allocator to compare
 * @param a2 Second custom allocator to compare
 * @return True if both allocators are considered different, false otherwise
 */
template <class T, class U, std::size_t N>
constexpr bool operator!=(const custom_allocator<T, N> &a1,
                          const custom_allocator<U, N> &a2) noexcept {
	return false;
}
} // namespace otus_cpp