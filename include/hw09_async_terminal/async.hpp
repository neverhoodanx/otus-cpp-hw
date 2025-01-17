/**
 *  @file async.hpp
 *  @brief Contains declarations for asynchronous terminal operations.
 *  OTUS homework module
 *  #9 async terminal
 *  (c) 2024
 */

#pragma once

#include <cstddef>

namespace otus_cpp::async {

/**
 * @typedef Context
 * @brief Defines a type for managing unique contexts.
 */
using Context = void *;

/**
 * @brief Initializes a new context for handling commands with a specific block
 * size.
 * @param block_size The number of commands that can be processed in one block.
 * @return A unique context identifier for the initialized context.
 */
Context connect(std::size_t block_size);

/**
 * @brief Receives data associated with a context and forwards it for
 * processing.
 * @param context The context under which the data should be processed.
 * @param data Pointer to the data to be processed.
 * @param size Size of the data.
 */
void receive(Context context, const char *data, std::size_t size);

/**
 * @brief Ends operations and destroys the specified context.
 * @param context The context to be disconnected and destroyed.
 */
void disconnect(Context context);

} // namespace otus_cpp::async
