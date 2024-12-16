/**
 *  OTUS homework module
 *  #6 Matrix
 *  Take solution from
 *  https://stackoverflow.com/questions/6245735/pretty-print-stdtuple (c) 2024
 */
#pragma once

#include <iostream>
#include <tuple>
namespace otus_cpp {
template <class TupType, size_t... I>
void print(const TupType &_tup, std::index_sequence<I...>) {
	std::cout << "(";
	(..., (std::cout << (I == 0 ? "" : ", ") << std::get<I>(_tup)));
	std::cout << ")\n";
}

template <class... T> void print(const std::tuple<T...> &_tup) {
	print(_tup, std::make_index_sequence<sizeof...(T)>());
}
} // namespace otus_cpp
