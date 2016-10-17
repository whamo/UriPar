// Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "UriParser.h"

TEST_CASE("Test scheme parsing", "[scheme]") {
	
	SECTION("Basic test for scheme") {
		char *basicURI = "http://www.arsenal.com";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
	}
	SECTION("Basic test for no scheme") {
		char *basicURI = "//www.arsenal.com";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
	}
	SECTION("Empty string input - shouldn't blow up") {
		char *basicURI = "";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
	}
	SECTION("just query and fragment - shouldn't blow up") {
		char *basicURI = "?testing=true#somefragment";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
	}
	SECTION("Teting scheme with special characters") {
		char *basicURI = "h+2t.0t-9p://www.arsenal.com";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 10);
	}
	SECTION("Teting scheme with special characters") {
		char *basicURI = "h!2;0t*9p://www.arsenal.com";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
	}
}
TEST_CASE("Test authority parsing", "[authority]") {

	SECTION("Basic test for authority") {
		char *basicURI = "http://www.arsenal.com";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 22);
	}
	SECTION("Basic test for no authority") {
		char *basicURI = "http:";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
	}
	SECTION("Basic test for no authority") {
		char *basicURI = "http:/path/here";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
	}
	SECTION("Basic test for authority followed by query") {
		char *basicURI = "http://www.arsenal.com?test=true";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 22);
	}
	SECTION("Basic test for authority followed by fragment") {
		char *basicURI = "http://www.arsenal.com#somefragment";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 22);
	}
	SECTION("Basic test for authority with no scheme") {
		char *basicURI = "//www.arsenal.com#somefragment";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.authority.startPosition == basicURI);
		REQUIRE(basicTest.authority.endPosition == basicURI + 17);
	}
}
TEST_CASE("Test path parsing", "[path]") {

	SECTION("Basic test for path") {
		char *basicURI = "http://www.arsenal.com/fixtures/first-team";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 22);
		REQUIRE(basicTest.path.startPosition == basicURI + 22);
		REQUIRE(basicTest.path.endPosition == basicURI + 42);
	}
	SECTION("Basic test for path starting with slash") {
		char *basicURI = "/fixtures/first-team";
		UriParser basicTest(basicURI);
		char *temp = basicURI + 20;
		bool will = (basicTest.path.endPosition == basicURI + 20);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI);
		REQUIRE(basicTest.path.endPosition == basicURI + 20);
	}
	SECTION("Basic test for path no initial slash") {
		char *basicURI = "fixtures/first-team";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI);
		REQUIRE(basicTest.path.endPosition == basicURI + 19);
	}
	SECTION("Basic test for path followed by query") {
		char *basicURI = "http://www.arsenal.com/fixtures/first-team?query=true";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 22);
		REQUIRE(basicTest.path.startPosition == basicURI + 22);
		REQUIRE(basicTest.path.endPosition == basicURI + 42);
		REQUIRE(basicTest.query.startPosition == basicURI + 43);
		REQUIRE(basicTest.query.endPosition == basicURI + 53);
	}
	SECTION("Basic test for path starting with slash followed by query") {
		char *basicURI = "/fixtures/first-team?query=true";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI);
		REQUIRE(basicTest.path.endPosition == basicURI + 20);
		REQUIRE(basicTest.query.startPosition == basicURI + 21);
		REQUIRE(basicTest.query.endPosition == basicURI + 31);
	}
	SECTION("Basic test for path no initial slash followed by query") {
		char *basicURI = "fixtures/first-team?query=true";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI);
		REQUIRE(basicTest.path.endPosition == basicURI + 19);
		REQUIRE(basicTest.query.startPosition == basicURI + 20);
		REQUIRE(basicTest.query.endPosition == basicURI + 30);
	}
	SECTION("Basic test for path followed by fragment") {
		char *basicURI = "http://www.arsenal.com/fixtures/first-team#somefragment";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 22);
		REQUIRE(basicTest.path.startPosition == basicURI + 22);
		REQUIRE(basicTest.path.endPosition == basicURI + 42);
	}
	SECTION("Basic test for path starting with slash followed by query") {
		char *basicURI = "/fixtures/first-team#somefragment";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI);
		REQUIRE(basicTest.path.endPosition == basicURI + 20);
	}
	SECTION("Basic test for path no initial slash followed by query") {
		char *basicURI = "fixtures/first-team#somefragment";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI);
		REQUIRE(basicTest.path.endPosition == basicURI + 19);
	}
}
TEST_CASE("Test query and fragment parsing", "[query and fragment]") {

	SECTION("Basic test for path followed by fragment") {
		char *basicURI = "http://www.arsenal.com/fixtures/first-team?query=false#somefragment";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 22);
		REQUIRE(basicTest.path.startPosition == basicURI + 22);
		REQUIRE(basicTest.path.endPosition == basicURI + 42);
		REQUIRE(basicTest.query.startPosition == basicURI + 43);
		REQUIRE(basicTest.query.endPosition == basicURI + 54);
	}
	SECTION("Basic test for path starting with slash followed by query and fragment") {
		char *basicURI = "/fixtures/first-team?query=false#somefragment";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI);
		REQUIRE(basicTest.path.endPosition == basicURI + 20);
		REQUIRE(basicTest.query.startPosition == basicURI + 21);
		REQUIRE(basicTest.query.endPosition == basicURI + 32);
	}
	SECTION("Basic test for path no initial slash followed by query and fragment") {
		char *basicURI = "fixtures/first-team?query=false#somefragment";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI);
		REQUIRE(basicTest.path.endPosition == basicURI + 19);
		REQUIRE(basicTest.query.startPosition == basicURI + 20);
		REQUIRE(basicTest.query.endPosition == basicURI + 31);
	}
}
int main(int argc, char* const argv[])
{
	int result = Catch::Session().run(argc, argv);
	return result;
}

