/**
 *  @file table_keeper.cpp
 *  OTUS homework module
 *  #11 table keeper
 *  (c) 2025
 */

#include "table_keeper.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace otus_cpp::join {
table_keeper::table_keeper() {
	init_table_a();
	init_table_b();
}

std::string table_keeper::process_command(const std::string &command) {
	std::istringstream iss(command);
	std::string cmd;
	iss >> cmd;

	if (cmd == "INSERT") {
		std::string table;
		int id;
		std::string name;
		iss >> table >> id >> name;
		if (table == "A") {
			return insert(tableA, id, name);
		} else if (table == "B") {
			return insert(tableB, id, name);
		} else {
			return "ERR invalid table\n";
		}
	} else if (cmd == "TRUNCATE") {
		std::string table;
		iss >> table;
		if (table == "A") {
			truncate(tableA);
		} else if (table == "B") {
			truncate(tableB);
		} else {
			return "ERR invalid table\n";
		}
		return "OK\n";
	} else if (cmd == "INTERSECTION") {
		return intersection();
	} else if (cmd == "SYMMETRIC_DIFFERENCE") {
		return symmetric_diff();
	} else {
		return "ERR unknown command\n";
	}
}
std::string table_keeper::insert(table_data &table, int id,
                                 const std::string &name) {
	if (table.ids.find(id) != table.ids.end()) {
		return std::string("ERR duplicate " + std::to_string(id) + "\n");
	}
	table.ids.insert(id);
	table.data[id] = name;
	return "OK\n";
}

void table_keeper::truncate(table_data &table) {
	table.ids.clear();
	table.data.clear();
}

bool table_keeper::contains(const table_data &table, int id) const {
	return table.ids.find(id) != table.ids.end();
}

std::string table_keeper::get_data(const table_data &table, int id) const {
	auto it = table.data.find(id);
	if (it != table.data.end()) {
		return it->second;
	}
	return std::string();
}

std::string table_keeper::intersection() {
	std::ostringstream oss;
	std::vector<int> intersectionIds;

	std::set_intersection(tableA.ids.begin(), tableA.ids.end(),
	                      tableB.ids.begin(), tableB.ids.end(),
	                      std::back_inserter(intersectionIds));

	for (const int id : intersectionIds) {
		oss << id << "," << tableA.data.at(id) << "," << tableB.data.at(id)
		    << std::endl;
	}

	oss << "OK\n";
	return oss.str();
}

std::string table_keeper::symmetric_diff() {
	std::ostringstream oss;

	for (const int id : tableA.ids) {
		if (!contains(tableB, id)) {
			oss << id << "," << tableA.data.at(id) << "," << std::endl;
		}
	}

	for (const int id : tableB.ids) {
		if (!contains(tableA, id)) {
			oss << id << ",," << tableB.data.at(id) << std::endl;
		}
	}

	oss << "OK" << std::endl;
	return oss.str();
}

void table_keeper::init_table_a() {
	std::vector<std::pair<int, std::string>> initialData = {
	    {0, "lean"},      {1, "sweater"}, {2, "frank"},
	    {3, "violation"}, {4, "quality"}, {5, "precision"}};
	for (const auto &[id, name] : initialData) {
		insert(tableA, id, name);
	}
}

void table_keeper::init_table_b() {
	std::vector<std::pair<int, std::string>> initialData = {
	    {3, "proposal"}, {4, "example"}, {5, "lake"},
	    {6, "flour"},    {7, "wonder"},  {8, "selection"}};
	for (const auto &[id, name] : initialData) {
		insert(tableB, id, name);
	}
}
} // namespace otus_cpp::join