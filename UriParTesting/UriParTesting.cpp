// UriParTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "UriPar.h"

TEST_CASE("Test scheme parsing", "[scheme]") {
	
	SECTION("Basic test for scheme") {
		char *basicURI = "http://www.arsenal.com";
		UriPar basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
	}
	SECTION("Basic test for no scheme") {
		char *basicURI = "//www.arsenal.com";
		UriPar basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
	}
	SECTION("Empty string input - shouldn't blow up") {
		char *basicURI = "";
		UriPar basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
	}
	SECTION("just query and fragment - shouldn't blow up") {
		char *basicURI = "?testing=true#somefragment";
		UriPar basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
	}
	SECTION("Teting scheme with special characters") {
		char *basicURI = "h+2t.0t-9p://www.arsenal.com";
		UriPar basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 10);
	}
}

int main(int argc, char* const argv[])
{
	UriPar initTest("some string");

	int result = Catch::Session().run(argc, argv);

	return result;
}

