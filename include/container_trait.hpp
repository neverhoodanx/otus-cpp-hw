/**
 *  OTUS homework module
 *  #4 SFINAE, trair for list, vector, tuple
 *  (c) 2024
 */
#pragma once

#include <list>
#include <set>
#include <vector>

namespace otus_cpp::sfinae {

/**
 * @brief Primary template to check if a type is a container.
 *
 * This primary template defaults to false, indicating that the type T
 * is not recognized as a container.
 *
 * @tparam T The type to be checked.
 */
template <typename T> struct is_container : std::false_type {};

/**
 * @brief Specialization for std::vector to recognize it as a container.
 *
 * This specialization allows std::vector to be identified as a container
 * type by inheriting from std::true_type.
 *
 * @tparam Ts The types of elements in the std::vector.
 */
template <typename... Ts>
struct is_container<std::vector<Ts...>> : std::true_type {};

/**
 * @brief Specialization for std::list to recognize it as a container.
 *
 * This specialization allows std::list to be identified as a container
 * type by inheriting from std::true_type.
 *
 * @tparam Ts The types of elements in the std::list.
 */
template <typename... Ts>
struct is_container<std::list<Ts...>> : std::true_type {};

/**
 * @brief Primary template to check if a type is a tuple.
 *
 * This primary template defaults to false, indicating that the type T
 * is not recognized as a tuple.
 *
 * @tparam T The type to be checked.
 */
template <typename T> struct is_tuple : std::false_type {};

/**
 * @brief Specialization for std::tuple to recognize it as a tuple.
 *
 * This specialization allows std::tuple to be identified as a tuple
 * type by inheriting from std::true_type.
 *
 * @tparam Args The types of elements in the std::tuple.
 */
template <typename... Args>
struct is_tuple<std::tuple<Args...>> : std::true_type {};

/**
 * @brief Template to check if all types are equal.
 *
 * This template checks if the type T is the same as all the types in
 * the parameter pack Ts... using std::is_same.
 *
 * @tparam T The first type to compare.
 * @tparam Ts The types to compare against T.
 */
template <typename T, typename... Ts> struct is_equale_types {
	/// @brief Static constant that evaluates to true if all types are equal,
	/// false otherwise.
	constexpr static bool value =
	    std::is_same_v<std::tuple<T, Ts...>, std::tuple<Ts..., T>>;
};

/**
 * @brief Specialization for tuples to check equality of types within the tuple.
 *
 * This specialization allows checking equality of types within a tuple
 * by recursively applying is_equale_types on the types in the tuple.
 *
 * @tparam T The types contained in the tuple.
 */
template <typename... T>
struct is_equale_types<std::tuple<T...>> : is_equale_types<T...> {};

/**
 * @brief Helper variable template to simplify usage of is_equale_types.
 *
 * This variable template provides a convenient way to access the value
 * of is_equale_types without needing to specify the template parameters
 * explicitly.
 *
 * @tparam T The types to check for equality.
 */
template <typename... T>
constexpr bool is_equale_types_v = is_equale_types<T...>::value;

} // namespace otus_cpp::sfinae
