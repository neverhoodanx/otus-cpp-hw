/**
 *  OTUS homework module
 *  #6 Matrix
 *  Custom realisation of n-dimensional sparse matrix
 *  (c) 2024
 */
#pragma once

#include <functional>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

/**
 * @brief Specialization the std::hash function for our index std::tuple
 */
namespace std {
template <typename... Args> struct hash<std::tuple<Args...>> {
	std::size_t operator()(const std::tuple<Args...> &t) const {
		return std::apply(
		    [](auto &&...args) {
			    return (std::hash<std::decay_t<decltype(args)>>{}(args) ^ ...);
		    },
		    t);
	}
};
} // namespace std

namespace otus_cpp {
/**
 * @brief Specialization for creating a std::tuple with N elements of type
 * uint32_t
 */
template <std::size_t N, std::size_t... Is>
auto make_me_tuple_impl(std::index_sequence<Is...>) {
	return std::make_tuple(((void)Is, uint32_t{})...);
}
/**
 * @brief A helper function for creating a std::tuple with N elements of type
 * uint32_t
 */
template <std::size_t N> auto make_me_tuple() {
	return make_me_tuple_impl<N>(std::make_index_sequence<N>{});
}

/**
 * @brief Custom realisation of n-dimensional sparse matrix
 *
 * The matrix fillы with default values. The matrix should only store occupied
 * elements - those that have been assigned at least once. Assigning a default
 * value to a cell frees the cell
 *
 * @tparam T - The type of elements stored in the container.
 * @tparam size_t N - The dimension of the matrix
 */
template <typename T, std::size_t N> class custom_matrix {
  public:
	using tuple_index = decltype(make_me_tuple<N>());
	using tuple_index_it =
	    decltype(std::tuple_cat(tuple_index(), std::make_tuple(T())));
	/**
	 * @brief  Ctor
	 * @tparam value - default value, if not set use default Ctor of T
	 */
	custom_matrix(const T &value = T()) : default_(value) {}
	/**
	 * @brief Setting a value by key
	 * @tparam tuple_index tuple_index
	 */
	void set(tuple_index key, const T &value) {
		if (value == default_) {
			storage_.erase(key);
		} else {
			storage_[key] = value;
		}
	}
	/**
	 * @brief Getting a value by key (with modification possibility)
	 * @tparam tuple_index key - index
	 */
	T &get(tuple_index key) {
		auto it = storage_.find(key);
		if (it != storage_.end()) {
			return it->second;
		} else {
			return default_;
		}
	}
	/**
	 * @brief Getting a value by key (without modification possibility)
	 * @tparam tuple_index key - index
	 */
	T get(tuple_index key) const {
		auto it = storage_.find(key);
		if (it != storage_.end()) {
			return it->second;
		} else {
			return default_;
		}
	}
	/**
	 * @brief returns the number of actually occupied cells in
	 * the matrix
	 * @return size_t size - currnet size
	 */
	size_t size() { return storage_.size(); }
	/**
	 * @brief Assignment operator
	 */
	custom_matrix &operator=(const custom_matrix &other) {
		if (this != &other) {
			storage_ = other.storage_;
			default_ = other.default_;
		}
		return *this;
	}
	/**
	 * @brief Proxy class for implementing the method to access an element using
	 * square brackets
	 * @tparam U cumulative index
	 */
	template <typename U> class custom_crutch {
	  public:
		/**
		 * @brief Ctor
		 * @tparam custom_matrix &m - A reference to the matrix object we are
		 * accessing
		 * @tparam U v - cumulative index
		 */
		custom_crutch(custom_matrix &m, U v) : val(v), matrix(m) {}
		/**
		 * @brief Index access operator
		 * @tparam uint32_t row - index
		 */
		auto operator[](uint32_t col) {
			// if constexpr (std::tuple_size<U>::value == (n_size - 1)) {} else
			auto a = std::tuple_cat(val, std::make_tuple(col));
			return custom_crutch<decltype(a)>(matrix, a);
		}
		/**
		 * @brief Value assignment operator
		 */
		T &operator=(const T &value) {
			matrix.set(val, value);
			return matrix.get(val);
		}
		/**
		 * @brief Conversion operator to type T
		 */
		operator T() const { return matrix.get(val); }

	  private:
		U val;
		custom_matrix &matrix;
	};
	/**
	 * @brief Index access operator
	 * @tparam uint32_t row - index
	 */
	auto operator[](uint32_t row) {
		auto a = std::make_tuple(row);
		return custom_crutch<decltype(a)>(*this, a);
	}

	/**
	 * @brief Iterator class
	 */
	class iterator {
	  public:
		using iterator_category = std::input_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = tuple_index_it;
		using pointer = value_type *;
		using reference = value_type &;
		/**
		 * @brief Ctor
		 */
		iterator(typename std::unordered_map<tuple_index, T>::iterator it)
		    : it_(it) {}
		/**
		 * @brief Dereference operator
		 */
		value_type operator*() const {
			return std::tuple_cat(it_->first, std::make_tuple(it_->second));
		}
		/**
		 * @brief Prefix increment operator

		 */
		iterator &operator++() {
			++it_;
			return *this;
		}
		/**
		 * @brief Postfix increment operator
		 */
		iterator operator++(int) {
			iterator tmp = *this;
			++(*this);
			return tmp;
		}
		/**
		 * @brief Equality comparison operator
		 */
		bool operator==(const iterator &other) const {
			return it_ == other.it_;
		}
		/**
		 * @brief Inequality comparison operator
		 */
		bool operator!=(const iterator &other) const {
			return it_ != other.it_;
		}

	  private:
		typename std::unordered_map<tuple_index, T>::iterator it_;
	};
	/**
	 * @brief Returns iterator to the beginning
	 */
	iterator begin() { return iterator(storage_.begin()); }
	/**
	 * @brief Returns iterator to the end
	 */
	iterator end() { return iterator(storage_.end()); }

  private:
	T default_;
	std::unordered_map<tuple_index, T> storage_;
};
} // namespace otus_cpp