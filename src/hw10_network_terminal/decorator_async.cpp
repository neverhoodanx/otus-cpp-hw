/**
 *  @file decorator_async.cpp
 *  OTUS homework module
 *  #10 Decorator for async
 *  (c) 2025
 */

#include "decorator_async.hpp"

#include <unordered_set>

static size_t counter = 0;

static std::unordered_set<otus_cpp::async::Context> ctxs_;

namespace otus_cpp::nw_async {
decorator_async::decorator_async(size_t bulk_size) : bulk_size_(bulk_size) {
	external_blocks_ = otus_cpp::async::connect(bulk_size_);
}

decorator_async::~decorator_async() {
	otus_cpp::async::disconnect(external_blocks_);
}

void decorator_async::send_internal_data(otus_cpp::async::Context ctx,
                                         const std::string &data) {
	otus_cpp::async::receive(ctx, data.data(), data.size());
}

void decorator_async::send_external_data(const std::string &data) {
	otus_cpp::async::receive(external_blocks_, data.data(), data.size());
}

otus_cpp::async::Context decorator_async::connect() {
	counter++;
	auto ctx = otus_cpp::async::connect(bulk_size_);
	ctxs_.emplace(ctx);
	return ctx;
}

void decorator_async::disconnect(otus_cpp::async::Context ctx) {
	counter--;
	otus_cpp::async::disconnect(ctx);
	if (counter == 0) {
		otus_cpp::async::disconnect(external_blocks_);
		external_blocks_ = otus_cpp::async::connect(bulk_size_);
	}
	ctxs_.erase(ctx);
}

void decorator_async::flush() {
	for (auto ctx : ctxs_) {
		otus_cpp::async::disconnect(ctx);
	}
	otus_cpp::async::disconnect(external_blocks_);
}

} // namespace otus_cpp::nw_async