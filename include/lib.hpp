/**
 *  OTUS homework module
 *  (c) 2024
 */
#pragma once

#include <string>
#include <vector>

namespace otus_cpp {
/**
 * @brief HW4 - SFINAE
 * following outputs are exepted:
 * - print_ip( int8_t{-1} ); // 255
 * - print_ip( int16_t{0} ); // 0.0
 * - print_ip( int32_t{2130706433} ); // 127.0.0.1
 * - print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
 * - print_ip( std::string{“Hello, World!”} ); // Hello, World!
 * - print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
 * - print_ip( std::list<shot>{400, 300, 200, 100} ); // 400.300.200.100
 * - print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
 */
void technical_task_sfinae();

/**
 * @brief HW3 - Custom allocators
 * following outputs are exepted:
 * - all values (key and value separated by a space) stored in the map<int,int>
 * - all values stored in the custom container "int"
 */
void technical_task_allocators();

/**
 * @brief HW2 print to seconds ip list with task,
 * following outputs are exepted:
 * - reverse sorting
 * - filter by firts position
 * - filter by firts and second position
 * - filter by any position
 */
void technical_task_ip_filter();

/**
 * @brief HW 1 Return library version
 * @return version number
 */
int version();

} // namespace otus_cpp
