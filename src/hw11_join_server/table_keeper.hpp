/**
 *  @file table_keeper.hpp
 *  OTUS homework module
 *  #11 table keeper
 *  (c) 2025
 */
#pragma once

#include "table_data.hpp"

namespace otus_cpp::join {

class table_keeper {
  public:
	/**
	 * @brief Ctor
	 * Initializes two tables with initial data
	 */
	explicit table_keeper();
	/**
	 * @brief Process a user command
	 * @param command to execute
	 * @return Result of the command execution
	 */
	std::string process_command(const std::string &command);

  private:
	/**
	 * @brief Initialize the A table with initial data
	 */
	void init_table_a();
	/**
	 * @brief Initialize the B table with initial data
	 */
	void init_table_b();
	/**
	 * @brief Insert a new record into the table
	 * @param table Reference to the table where the record will be inserted
	 * @param id Record ID
	 * @param name Record name
	 * @return "OK\n" if insertion is successful, or an error message on
	 * dublicate
	 */
	std::string insert(table_data &table, int id, const std::string &name);
	/**
	 * @brief Clear the table of all records
	 * @param table Reference to the table to be cleared
	 */
	void truncate(table_data &table);
	/**
	 * @brief Check if a record exists in the table
	 * @param table Reference to the table to check
	 * @param id Record ID
	 * @return true if the record exists, otherwise false
	 */
	bool contains(const table_data &table, int id) const;
	/**
	 * @brief Get the name associated with a given ID from the table
	 * @param table Reference to the table to get the data from
	 * @param id Record ID
	 * @return Name associated with the given ID or empty string!
	 */
	std::string get_data(const table_data &table, int id) const;
	/**
	 * @brief Compute the intersection of two tables
	 * @return String containing the result of the intersection
	 */
	std::string intersection();
	/**
	 * @brief Compute the symmetric difference of two tables
	 * @return String containing the result of the symmetric difference
	 */
	std::string symmetric_diff();

	table_data tableA;
	table_data tableB;
};

} // namespace otus_cpp::join