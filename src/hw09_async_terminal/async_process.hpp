/**
 *  @file async_process.hpp
 *  OTUS homework module
 *  #9 async terminal
 *  (c) 2024
 */

#pragma once

#include "hw07_terminal/i_command_handler.hpp"
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace otus_cpp::async {

/**
 * @struct Command
 * @brief Represents a command structure containing the context name, timestamp,
 * and command text.
 */
struct Command {
	std::string contextName; ///< Name of the context related to the command.
	std::string timestamp;   ///< Time at which the command was created.
	std::queue<std::string> commandText; ///< The actual text of the command.
};

/**
 * @class async_process
 * @brief Handles asynchronous processing of command blocks.
 */
class async_process {
  public:
	/**
	 * @brief Constructs an async_process object and initializes worker threads.
	 * @param threadCount The number of threads to initialize.
	 */
	async_process(size_t threadCount);

	/**
	 * @brief Destructor for async_process. Joins all threads.
	 */
	~async_process();

	/**
	 * @brief Processes a block of commands.
	 * @param commands The queue of commands to be processed.
	 * @param context_name The name of the context.
	 * @param time The timestamp for the commands.
	 */
	void process_block(const std::queue<std::string> &commands,
	                   const std::string &context_name,
	                   const std::string &time);

  private:
	/**
	 * @brief Processes the console output queue.
	 */
	void processConsoleQueue();

	/**
	 * @brief Processes the file output queue.
	 * @return The Command object to be processed.
	 */
	Command processFileQueue();

	std::queue<Command> consoleQueue; ///< Queue of commands for console output.
	std::queue<Command> fileQueue;    ///< Queue of commands for file output.
	std::mutex consoleMutex;          ///< Mutex for console queue operations.
	std::mutex fileMutex;             ///< Mutex for file queue operations.
	std::condition_variable
	    consoleCv;                  ///< Condition variable for console queue.
	std::condition_variable fileCv; ///< Condition variable for file queue.
	std::vector<std::thread>
	    workerThreads;         ///< Worker threads for file processing.
	std::thread consoleThread; ///< Thread for console output processing.
	std::atomic<bool> done; ///< Atomic flag for checking if processing is done.
};

} // namespace otus_cpp::async