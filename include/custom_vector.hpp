/**
 *  OTUS homework module
 *  #3 Custom OtusAllocator
 *  Custom vector
 *  (c) 2024
 */
#pragma once

#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>

namespace otus_cpp {
/**
 * Custom container aka vector
 */
template <typename T, typename Alloc = std::allocator<T>> class custom_vector {
  public:
	using allocator_type = Alloc;
	using value_type = T;
	using pointer = typename std::allocator_traits<Alloc>::pointer;
	using size_type = typename std::allocator_traits<Alloc>::size_type;

	using iterator = T *;
	using const_iterator = const T *;

	/**
	 * Ctor
	 * initial_capacity - initial size of the container
	 */
	custom_vector(size_type initial_capacity = 10)
	    : size_(0), capacity_(initial_capacity), allocator_(Alloc()) {
		data_ = std::allocator_traits<Alloc>::allocate(allocator_, capacity_);
	}
	/**
	 * Copy Ctor
	 */
	custom_vector(const custom_vector &other)
	    : size_(other.size_), capacity_(other.capacity_),
	      allocator_(other.allocator_) {
		data_ = std::allocator_traits<Alloc>::allocate(allocator_, capacity_);
		for (size_type i = 0; i < size_; ++i) {
			std::allocator_traits<Alloc>::construct(allocator_, data_ + i,
			                                        other.data_[i]);
		}
	}
	/**
	 * Move Ctor
	 */
	custom_vector(custom_vector &&other) noexcept
	    : data_(other.data_), size_(other.size_), capacity_(other.capacity_),
	      allocator_(std::move(other.allocator_)) {
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}
	/**
	 * Copy assignment operator
	 */
	custom_vector &operator=(const custom_vector &other) {
		if (this != &other) {
			clear();
			if (capacity_ < other.size_) {
				std::allocator_traits<Alloc>::deallocate(allocator_, data_,
				                                         capacity_);
				capacity_ = other.capacity_;
				data_ = std::allocator_traits<Alloc>::allocate(allocator_,
				                                               capacity_);
			}
			size_ = other.size_;
			for (size_type i = 0; i < size_; ++i) {
				std::allocator_traits<Alloc>::construct(allocator_, data_ + i,
				                                        other.data_[i]);
			}
		}
		return *this;
	}
	/**
	 * Move assignment operator
	 */
	custom_vector &operator=(custom_vector &&other) noexcept {
		if (this != &other) {
			clear();
			std::allocator_traits<Alloc>::deallocate(allocator_, data_,
			                                         capacity_);
			data_ = other.data_;
			size_ = other.size_;
			capacity_ = other.capacity_;
			allocator_ = std::move(other.allocator_);

			other.data_ = nullptr;
			other.size_ = 0;
			other.capacity_ = 0;
		}
		return *this;
	}
	/**
	 * Dtor
	 */
	~custom_vector() {
		clear();
		std::allocator_traits<Alloc>::deallocate(allocator_, data_, capacity_);
	}
	/**
	 * Add element at the end
	 * @param value to be copied to the new element.
	 */
	void push_back(const T &value) {
		if (size_ >= capacity_) {
			resize();
		}
		std::allocator_traits<Alloc>::construct(allocator_, data_ + size_,
		                                        value);
		++size_;
	}
	/**
	 * Delete last element
	 */
	void pop_back() {
		if (size_ > 0) {
			--size_;
			std::allocator_traits<Alloc>::destroy(allocator_, data_ + size_);
		}
	}
	/**
	 * Access element
	 * @return reference to the element at position n in the vector container
	 */
	T &operator[](size_type index) {
		if (index >= size_)
			throw std::out_of_range("Index out of range");
		return data_[index];
	}
	/**
	 * Access element
	 * @return const reference to the element at position n in the vector
	 * container
	 */
	const T &operator[](size_type index) const {
		if (index >= size_)
			throw std::out_of_range("Index out of range");
		return data_[index];
	}
	/**
	 * Removes all elements from the vector, container size is 0
	 */
	void clear() {
		for (size_type i = 0; i < size_; ++i) {
			std::allocator_traits<Alloc>::destroy(allocator_, data_ + i);
		}
		size_ = 0;
	}
	/**
	 * Current size
	 * @return size size_type
	 */
	size_type size() const { return size_; }
	/**
	 * Resered conatainer size
	 * @return capacity size_type
	 */
	size_type capacity() const { return capacity_; }
	/**
	 * Resizes the container so that it contains capacity_ * 2 elements
	 */
	void resize() {
		size_type new_capacity = capacity_ * 2;
		pointer new_data =
		    std::allocator_traits<Alloc>::allocate(allocator_, new_capacity);

		for (size_type i = 0; i < size_; ++i) {
			std::allocator_traits<Alloc>::construct(allocator_, new_data + i,
			                                        std::move(data_[i]));
			std::allocator_traits<Alloc>::destroy(allocator_, data_ + i);
		}

		std::allocator_traits<Alloc>::deallocate(allocator_, data_, capacity_);
		data_ = new_data;
		capacity_ = new_capacity;
	}
	/**
	 * Return iterator to beginning
	 */
	iterator begin() { return data_; }
	/**
	 * Return iterator to end
	 */
	iterator end() { return data_ + size_; }
	/**
	 * Return const_iterator to beginning
	 */
	const_iterator cbegin() const { return data_; }
	/**
	 * Return const_iterator to end
	 */
	const_iterator cend() const { return data_ + size_; }

  private:
	pointer data_;
	size_type size_;
	size_type capacity_;
	allocator_type allocator_;
};
} // namespace otus_cpp
