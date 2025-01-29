/**
 *  OTUS homework test module
 *  (c) 2024
 */

#include "hw11_join_server/table_keeper.hpp"

#include <boost/test/unit_test.hpp>

#include <sstream>

BOOST_AUTO_TEST_SUITE(ServerLogicTestSuite)

BOOST_AUTO_TEST_CASE(test_insert_and_truncate) {
	otus_cpp::join::table_keeper keeper;
	// cleanup the A
	auto response = keeper.process_command("TRUNCATE A");
	BOOST_CHECK_EQUAL(response, "OK\n");

	// insert data to the A
	response = keeper.process_command("INSERT A 0 lean");
	BOOST_CHECK_EQUAL(response, "OK\n");

	response = keeper.process_command("INSERT A 1 sweater");
	BOOST_CHECK_EQUAL(response, "OK\n");

	// duplicate insertion check
	response = keeper.process_command("INSERT A 0 understand");
	BOOST_CHECK(response.find("ERR duplicate") != std::string::npos);

	// cleanup the A
	response = keeper.process_command("TRUNCATE A");
	BOOST_CHECK_EQUAL(response, "OK\n");

	// get collection
	response = keeper.process_command("INTERSECTION");
	BOOST_CHECK_EQUAL(response, "OK\n");
}

BOOST_AUTO_TEST_CASE(test_intersection) {
	otus_cpp::join::table_keeper keeper;

	// Insert initial data into A and B
	keeper.process_command("INSERT A 0 lean");
	keeper.process_command("INSERT A 3 violation");
	keeper.process_command("INSERT A 4 quality");
	keeper.process_command("INSERT A 5 precision");

	keeper.process_command("INSERT B 3 proposal");
	keeper.process_command("INSERT B 4 example");
	keeper.process_command("INSERT B 5 lake");

	// Testing intersection
	std::string expected = "3,violation,proposal\n"
	                       "4,quality,example\n"
	                       "5,precision,lake\n"
	                       "OK\n";

	std::string response = keeper.process_command("INTERSECTION");
	BOOST_CHECK_EQUAL(response, expected);
}

BOOST_AUTO_TEST_CASE(test_symmetric_difference) {
	otus_cpp::join::table_keeper keeper;

	// Insert initial data into A and B
	keeper.process_command("INSERT A 0 lean");
	keeper.process_command("INSERT A 1 sweater");
	keeper.process_command("INSERT A 2 frank");
	keeper.process_command("INSERT A 3 violation");
	keeper.process_command("INSERT A 4 quality");
	keeper.process_command("INSERT A 5 precision");

	keeper.process_command("INSERT B 3 proposal");
	keeper.process_command("INSERT B 4 example");
	keeper.process_command("INSERT B 5 lake");
	keeper.process_command("INSERT B 6 flour");
	keeper.process_command("INSERT B 7 wonder");
	keeper.process_command("INSERT B 8 selection");

	// Testing symmetric difference
	std::string expected = "0,lean,\n"
	                       "1,sweater,\n"
	                       "2,frank,\n"
	                       "6,,flour\n"
	                       "7,,wonder\n"
	                       "8,,selection\n"
	                       "OK\n";

	std::string response = keeper.process_command("SYMMETRIC_DIFFERENCE");
	BOOST_CHECK_EQUAL(response, expected);
}

BOOST_AUTO_TEST_SUITE_END()