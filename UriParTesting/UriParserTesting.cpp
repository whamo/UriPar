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
		REQUIRE(basicTest.path.startPosition == NULL);
		REQUIRE(basicTest.path.endPosition == NULL);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Basic test for no authority") {
		char *basicURI = "http:";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == NULL);
		REQUIRE(basicTest.path.endPosition == NULL);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Basic test for no authority") {
		char *basicURI = "http:/path/here";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI + 5);
		REQUIRE(basicTest.path.endPosition == basicURI + 15);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Basic test for authority followed by query") {
		char *basicURI = "http://www.arsenal.com?test=true";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 22);
		REQUIRE(basicTest.path.startPosition == NULL);
		REQUIRE(basicTest.path.endPosition == NULL);
		REQUIRE(basicTest.query.startPosition == basicURI + 23);
		REQUIRE(basicTest.query.endPosition == basicURI + 32);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Basic test for authority followed by fragment") {
		char *basicURI = "http://www.arsenal.com#somefragment";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 22);
		REQUIRE(basicTest.path.startPosition == NULL);
		REQUIRE(basicTest.path.endPosition == NULL);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == basicURI + 23);
		REQUIRE(basicTest.fragment.endPosition == basicURI + 35);
	}
	SECTION("Basic test for authority with no scheme") {
		char *basicURI = "//www.arsenal.com#somefragment";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
		REQUIRE(basicTest.authority.startPosition == basicURI);
		REQUIRE(basicTest.authority.endPosition == basicURI + 17);
		REQUIRE(basicTest.path.startPosition == NULL);
		REQUIRE(basicTest.path.endPosition == NULL);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == basicURI + 18);
		REQUIRE(basicTest.fragment.endPosition == basicURI + 30);

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
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
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
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
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
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
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
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
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
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
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
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
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
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == basicURI + 43);
		REQUIRE(basicTest.fragment.endPosition == basicURI + 55);
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
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == basicURI + 21);
		REQUIRE(basicTest.fragment.endPosition == basicURI + 33);
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
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == basicURI + 20);
		REQUIRE(basicTest.fragment.endPosition == basicURI + 32);
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
		REQUIRE(basicTest.fragment.startPosition == basicURI + 55);
		REQUIRE(basicTest.fragment.endPosition == basicURI + 67);
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
		REQUIRE(basicTest.fragment.startPosition == basicURI + 33);
		REQUIRE(basicTest.fragment.endPosition == basicURI + 45);
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
		REQUIRE(basicTest.fragment.startPosition == basicURI + 32);
		REQUIRE(basicTest.fragment.endPosition == basicURI + 44);
	}
}
TEST_CASE("Test simple authority parsing", "[authority parsing]") {

	SECTION("Basic test for authority parsing") {
		char *basicURI = "//username:password@www.arsenal.com:80";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
		REQUIRE(basicTest.authority.startPosition == basicURI);
		REQUIRE(basicTest.authority.endPosition == basicURI + 38);
		REQUIRE(basicTest.username.startPosition == basicURI + 2);
		REQUIRE(basicTest.username.endPosition == basicURI + 10);
		REQUIRE(basicTest.password.startPosition == basicURI + 11);
		REQUIRE(basicTest.password.endPosition == basicURI + 19);
		REQUIRE(basicTest.host.startPosition == basicURI + 20);
		REQUIRE(basicTest.host.endPosition == basicURI + 35);
		REQUIRE(basicTest.port.startPosition == basicURI + 36);
		REQUIRE(basicTest.port.endPosition == basicURI + 38);
		REQUIRE(basicTest.path.startPosition == NULL);
		REQUIRE(basicTest.path.endPosition == NULL);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Basic test for authority parsing, no password") {
		char *basicURI = "//username@www.arsenal.com:80";
		UriParser basicTest(basicURI);
		char *temp = basicURI + 29;
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
		REQUIRE(basicTest.authority.startPosition == basicURI);
		REQUIRE(basicTest.authority.endPosition == basicURI + 29);
		REQUIRE(basicTest.username.startPosition == basicURI + 2);
		REQUIRE(basicTest.username.endPosition == basicURI + 10);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == basicURI + 11);
		REQUIRE(basicTest.host.endPosition == basicURI + 26);
		REQUIRE(basicTest.port.startPosition == basicURI + 27);
		REQUIRE(basicTest.port.endPosition == basicURI + 29);
		REQUIRE(basicTest.path.startPosition == NULL);
		REQUIRE(basicTest.path.endPosition == NULL);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Basic test for authority parsing") {
		char *basicURI = "//www.arsenal.com:80";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
		REQUIRE(basicTest.authority.startPosition == basicURI);
		REQUIRE(basicTest.authority.endPosition == basicURI + 20);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == basicURI + 2);
		REQUIRE(basicTest.host.endPosition == basicURI + 17);
		REQUIRE(basicTest.port.startPosition == basicURI + 18);
		REQUIRE(basicTest.port.endPosition == basicURI + 20);
		REQUIRE(basicTest.path.startPosition == NULL);
		REQUIRE(basicTest.path.endPosition == NULL);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Basic test for authority parsing") {
		char *basicURI = "//www.arsenal.com";
		UriParser basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
		REQUIRE(basicTest.authority.startPosition == basicURI);
		REQUIRE(basicTest.authority.endPosition == basicURI + 17);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == basicURI + 2);
		REQUIRE(basicTest.host.endPosition == basicURI + 17);
		REQUIRE(basicTest.port.startPosition == NULL);
		REQUIRE(basicTest.port.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == NULL);
		REQUIRE(basicTest.path.endPosition == NULL);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
}
TEST_CASE("Test simple parsing with get functions", "[simple parsing]") {

	SECTION("Basic test for authority parsing") {
		char *basicURI = "http://username:password@www.arsenal.com:80/path1/path2?query=false#somefragment";
		UriParser basicTest(basicURI);
		string actualScheme("http");
		string actualUsername("username");
		string actualPassword("password");
		string actualHost("www.arsenal.com");
		string actualPort("80");
		string actualPath("/path1/path2");
		string actualQuery("query=false");
		string actualFragment("somefragment");
		string actualAuthority("//username:password@www.arsenal.com:80");
		string parseScheme = basicTest.getScheme();
		string parseUsername = basicTest.getUsername();
		string parsePassword = basicTest.getPassword();
		string parseHost = basicTest.getHost();
		string parsePort = basicTest.getPort();
		string parsePath = basicTest.getPath();
		string parseQuery = basicTest.getQuery();
		string parseFragment = basicTest.getFragment();
		string parseAuthority = basicTest.getAuthority();
		
		REQUIRE(actualScheme.compare(parseScheme) == 0);
		REQUIRE(actualUsername.compare(parseUsername) == 0);
		REQUIRE(actualPassword.compare(parsePassword) == 0);
		REQUIRE(actualHost.compare(parseHost) == 0);
		REQUIRE(actualPort.compare(parsePort) == 0);
		REQUIRE(actualPath.compare(parsePath) == 0);
		REQUIRE(actualQuery.compare(parseQuery) == 0);
		REQUIRE(actualFragment.compare(parseFragment) == 0);
		REQUIRE(actualAuthority.compare(parseAuthority) == 0);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 43);
		REQUIRE(basicTest.username.startPosition == basicURI + 7);
		REQUIRE(basicTest.username.endPosition == basicURI + 15);
		REQUIRE(basicTest.password.startPosition == basicURI + 16);
		REQUIRE(basicTest.password.endPosition == basicURI + 24);
		REQUIRE(basicTest.host.startPosition == basicURI + 25);
		REQUIRE(basicTest.host.endPosition == basicURI + 40);
		REQUIRE(basicTest.port.startPosition == basicURI + 41);
		REQUIRE(basicTest.port.endPosition == basicURI + 43);
		REQUIRE(basicTest.path.startPosition == basicURI + 43);
		REQUIRE(basicTest.path.endPosition == basicURI + 55);
		REQUIRE(basicTest.query.startPosition == basicURI + 56);
		REQUIRE(basicTest.query.endPosition == basicURI + 67);
		REQUIRE(basicTest.fragment.startPosition == basicURI + 68);
		REQUIRE(basicTest.fragment.endPosition == basicURI + 80);
	}
}
TEST_CASE("Exception testing", "[exception testing]") {

	SECTION("Basic test for authority parsing") {
		char *basicURI = NULL;
		REQUIRE_THROWS_AS(UriParser basicTest(basicURI), invalid_argument);
	}
}
int main(int argc, char* const argv[])
{
	int result = Catch::Session().run(argc, argv);
	return result;
}

