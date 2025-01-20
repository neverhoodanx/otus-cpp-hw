/**
 *  @file async_process.cpp
 *  OTUS homework module
 *  #9 async terminal
 *  (c) 2024
 */

#include "async_process.hpp"

namespace otus_cpp::async {

async_process::async_process(size_t threadCount) : done(false) {
	// Initialize the console output thread
	consoleThread = std::thread(&async_process::processConsoleQueue, this);

	// Create worker threads
	for (size_t i = 0; i < threadCount; ++i) {
		workerThreads.emplace_back([this] {
			static size_t count = 0;
			while (true) {
				{
					std::unique_lock<std::mutex> lock(fileMutex);
					consoleCv.wait(
					    lock, [this] { return !consoleQueue.empty() || done; });

					if (done && consoleQueue.empty())
						return;
				}
				auto cmd = processFileQueue();
				// Create a file name
				std::string fileName = cmd.timestamp + "_" + cmd.contextName +
				                       std::to_string(count++) + ".txt";

				// Write command to file
				std::ofstream outputFile(fileName, std::ios::app);
				std::queue<std::string> temp = cmd.commandText;
				outputFile << "[" << cmd.contextName << "]: ";
				while (!temp.empty()) {
					auto comm = temp.front();
					temp.pop();
					if (!temp.empty()) {
						outputFile << comm << ", ";
					} else {
						outputFile << comm;
					}
				}
				outputFile << std::endl;
				outputFile.close();
			}
		});
	}
}

async_process::~async_process() {
	{
		std::lock_guard<std::mutex> lock(consoleMutex);
		done = true;
		consoleCv.notify_all();
	}

	{
		std::lock_guard<std::mutex> lock(fileMutex);
		fileCv.notify_all();
	}

	if (consoleThread.joinable()) {
		consoleThread.join();
	}

	for (auto &worker : workerThreads) {
		if (worker.joinable()) {
			worker.join();
		}
	}
}

void async_process::process_block(const std::queue<std::string> &commands,
                                  const std::string &context_name,
                                  const std::string &time) {
	Command cmd{context_name, time, commands};

	{
		std::lock_guard<std::mutex> lock(consoleMutex);
		consoleQueue.push(cmd);
		consoleCv.notify_one();
	}

	{
		std::lock_guard<std::mutex> lock(fileMutex);
		fileQueue.push(cmd);
		fileCv.notify_one();
	}
}

void async_process::processConsoleQueue() {
	while (true) {
		Command cmd;
		{
			std::unique_lock<std::mutex> lock(consoleMutex);
			consoleCv.wait(lock,
			               [this] { return !consoleQueue.empty() || done; });

			if (done && consoleQueue.empty())
				return;

			cmd = consoleQueue.front();
			consoleQueue.pop();
		}

		std::queue<std::string> temp = cmd.commandText;
		std::cout << "[" << cmd.contextName << "]: ";
		while (!temp.empty()) {
			auto comm = temp.front();
			temp.pop();
			if (!temp.empty()) {
				std::cout << comm << ", ";
			} else {
				std::cout << comm;
			}
		}
		std::cout << std::endl;
	}
}

Command async_process::processFileQueue() {
	std::unique_lock<std::mutex> lock(fileMutex);
	if (fileQueue.empty()) {
		return {};
	}
	Command cmd = fileQueue.front();
	fileQueue.pop();
	return cmd;
}

} // namespace otus_cpp::async