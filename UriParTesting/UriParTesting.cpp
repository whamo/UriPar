// UriParTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "UriPar.h"

TEST_CASE("Test scheme parsing", "[scheme]") {
	
	SECTION("Basic test fo scheme") {
		char *basicURI = "http://www.arsenal.com";
		UriPar basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI + 4);
	}
}

int main(int argc, char* const argv[])
{
	UriPar initTest("some string");

	int result = Catch::Session().run(argc, argv);

	return result;
}

