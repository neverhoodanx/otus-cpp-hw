/**
 *  OTUS homework module
 *  #2 ip filter
 *  Split
 *  (c) 2024
 */
#pragma once

#include <algorithm>

namespace otus_cpp {
/**
 * Splitting a string by a delimiter
 */
template <typename InIt, typename OutIt, typename T, typename F>
InIt split(InIt it, InIt end_it, OutIt out_it, T split_val, F bind_func) {
	while (it != end_it) {
		auto slice_end(std::find(it, end_it, split_val));
		*out_it++ = bind_func(it, slice_end);
		if (slice_end == end_it) {
			return end_it;
		}
		it = std::next(slice_end);
	}
	return it;
}
} // namespace otus_cpp
