// Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "UriParser.hpp"

TEST_CASE("Test scheme parsing", "[scheme]") {

	SECTION("Basic test for scheme") {
		char *basicURI = "http://www.arsenal.com";
		UriParser<char, string> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
	}
	SECTION("Basic test for no scheme") {
		char *basicURI = "//www.arsenal.com";
		UriParser<char, string> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
	}
	SECTION("Empty string input - shouldn't blow up") {
		char *basicURI = "";
		UriParser<char, string> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
	}
	SECTION("just query and fragment - shouldn't blow up") {
		char *basicURI = "?testing=true#somefragment";
		UriParser<char, string> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
	}
	SECTION("Teting scheme with special characters") {
		char *basicURI = "h+2t.0t-9p://www.arsenal.com";
		UriParser<char, string> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 10);
	}
	SECTION("Teting scheme with special characters") {
		char *basicURI = "h!2;0t*9p://www.arsenal.com";
		UriParser<char, string> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
	}
}
TEST_CASE("Test authority parsing", "[authority]") {

	SECTION("Basic test for authority") {
		char *basicURI = "http://www.arsenal.com";
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
		UriParser<char, string> basicTest(basicURI);
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
TEST_CASE("Test string constructor", "[string constructor]") {

	SECTION("Basic test for authority parsing") {
		string basicURI = "hTtP://username:password@www.ARSEnal.com:80/path1/path2?query=false#somefragment";
		char *thisPntr = &basicURI[0];
		UriParser<char, string> basicTest(basicURI);
		string actualScheme("http");
		string actualUsername("username");
		string actualPassword("password");
		string actualHost("www.arsenal.com");
		string actualPort("80");
		string actualPath("/path1/path2");
		string actualQuery("query=false");
		string actualFragment("somefragment");
		string actualAuthority("//username:password@www.ARSEnal.com:80");
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
		REQUIRE(basicTest.scheme.endPosition == thisPntr + 4);
		REQUIRE(basicTest.authority.startPosition == thisPntr + 5);
		REQUIRE(basicTest.authority.endPosition == thisPntr + 43);
		REQUIRE(basicTest.username.startPosition == thisPntr + 7);
		REQUIRE(basicTest.username.endPosition == thisPntr + 15);
		REQUIRE(basicTest.password.startPosition == thisPntr + 16);
		REQUIRE(basicTest.password.endPosition == thisPntr + 24);
		REQUIRE(basicTest.host.startPosition == thisPntr + 25);
		REQUIRE(basicTest.host.endPosition == thisPntr + 40);
		REQUIRE(basicTest.port.startPosition == thisPntr + 41);
		REQUIRE(basicTest.port.endPosition == thisPntr + 43);
		REQUIRE(basicTest.path.startPosition == thisPntr + 43);
		REQUIRE(basicTest.path.endPosition == thisPntr + 55);
		REQUIRE(basicTest.query.startPosition == thisPntr + 56);
		REQUIRE(basicTest.query.endPosition == thisPntr + 67);
		REQUIRE(basicTest.fragment.startPosition == thisPntr + 68);
		REQUIRE(basicTest.fragment.endPosition == thisPntr + 80);
	}
}
TEST_CASE("Exception testing", "[exception testing]") {

	SECTION("Basic test for authority parsing") {
		//Catch won't let me use templated constructor with require throws macros
		char *basicURI = NULL;
		UriParser<char, string> basicTest("");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		char *basicURI = "http://usern[]ame:password@www.arsenal.com:80/path1/path2?query=false#somefragment";
		UriParser<char, string> basicTest("");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		char *basicURI = "http://username:pass:word@www.arsenal.com:80/path1/path2?query=false#somefragment";
		UriParser<char, string> basicTest("");
		REQUIRE_NOTHROW(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		char *basicURI = "http://username:pas[]sword@www.arsenal.com:80/path1/path2?query=false#somefragment";
		UriParser<char, string> basicTest("");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		char *basicURI = "http://username:password@www.ars[]enal.com:80/path1/path2?query=false#somefragment";
		UriParser<char, string> basicTest("");
		REQUIRE_NOTHROW(basicTest.resetUriParser(basicURI));
	}
	SECTION("Basic test for authority parsing") {
		char *basicURI = "http://username:password@www.ars@enal.com:80/path1/path2?query=false#somefragment";
		UriParser<char, string> basicTest("");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		char *basicURI = "http://username:password@www.ars:enal.com:80/path1/path2?query=false#somefragment";
		UriParser<char, string> basicTest("");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		char *basicURI = "http://username:password@www.arsenal.com:8a0/path1/path2?query=false#somefragment";
		UriParser<char, string> basicTest("");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		char *basicURI = "http://username:password@www.arsenal.com:80/path[]1/path2?query=false#somefragment";
		UriParser<char, string> basicTest("");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		char *basicURI = "http://username:password@www.arsenal.com:80/path1/path2?query=f#alse#somefragment";
		UriParser<char, string> basicTest("");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		char *basicURI = "http://username:password@www.arsenal.com:80/path1/path2?query=f[]alse#somefragment";
		UriParser<char, string> basicTest("");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		char *basicURI = "http://username:password@www.arsenal.com:80/path1/path2?query=false#som[]efragment";
		UriParser<char, string> basicTest("");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		char *basicURI = "ldap://[2001:db8::7/c=GB?objectClass?one";
		UriParser<char, string> basicTest("");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
}
TEST_CASE("Examples from the standard", "[examples]") {

	SECTION("Example 1") {
		char *basicURI = "ftp://ftp.is.co.za/rfc/rfc1808.txt";
		UriParser<char, string> basicTest(basicURI);
		char *temp = basicURI + 35;
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 3);
		REQUIRE(basicTest.authority.startPosition == basicURI + 4);
		REQUIRE(basicTest.authority.endPosition == basicURI + 18);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == basicURI + 6);
		REQUIRE(basicTest.host.endPosition == basicURI + 18);
		REQUIRE(basicTest.port.startPosition == NULL);
		REQUIRE(basicTest.port.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI + 18);
		REQUIRE(basicTest.path.endPosition == basicURI + 34);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 2") {
		char *basicURI = "http://www.ietf.org/rfc/rfc2396.txt";
		UriParser<char, string> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 19);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == basicURI + 7);
		REQUIRE(basicTest.host.endPosition == basicURI + 19);
		REQUIRE(basicTest.port.startPosition == NULL);
		REQUIRE(basicTest.port.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI + 19);
		REQUIRE(basicTest.path.endPosition == basicURI + 35);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 3") {
		char *basicURI = "ldap://[2001:db8::7]/c=GB?objectClass?one";
		UriParser<char, string> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 20);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == basicURI + 7);
		REQUIRE(basicTest.host.endPosition == basicURI + 20);
		REQUIRE(basicTest.port.startPosition == NULL);
		REQUIRE(basicTest.port.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI + 20);
		REQUIRE(basicTest.path.endPosition == basicURI + 25);
		REQUIRE(basicTest.query.startPosition == basicURI + 26);
		REQUIRE(basicTest.query.endPosition == basicURI + 41);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 3a - made up") {
		char *basicURI = "ldap://[2001:db8::7]:1800/c=GB?objectClass?one";
		UriParser<char, string> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 25);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == basicURI + 7);
		REQUIRE(basicTest.host.endPosition == basicURI + 20);
		REQUIRE(basicTest.port.startPosition == basicURI + 21);
		REQUIRE(basicTest.port.endPosition == basicURI + 25);
		REQUIRE(basicTest.path.startPosition == basicURI + 25);
		REQUIRE(basicTest.path.endPosition == basicURI + 30);
		REQUIRE(basicTest.query.startPosition == basicURI + 31);
		REQUIRE(basicTest.query.endPosition == basicURI + 46);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 4") {
		char *basicURI = "mailto:John.Doe@example.com";
		UriParser<char, string> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 6);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == NULL);
		REQUIRE(basicTest.host.endPosition == NULL);
		REQUIRE(basicTest.port.startPosition == NULL);
		REQUIRE(basicTest.port.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI + 7);
		REQUIRE(basicTest.path.endPosition == basicURI + 27);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 5") {
		char *basicURI = "news:comp.infosystems.www.servers.unix";
		UriParser<char, string> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == NULL);
		REQUIRE(basicTest.host.endPosition == NULL);
		REQUIRE(basicTest.port.startPosition == NULL);
		REQUIRE(basicTest.port.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI + 5);
		REQUIRE(basicTest.path.endPosition == basicURI + 38);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 6") {
		char *basicURI = "tel:+1-816-555-1212";
		UriParser<char, string> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 3);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == NULL);
		REQUIRE(basicTest.host.endPosition == NULL);
		REQUIRE(basicTest.port.startPosition == NULL);
		REQUIRE(basicTest.port.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI + 4);
		REQUIRE(basicTest.path.endPosition == basicURI + 19);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 7") {
		char *basicURI = "telnet://192.0.2.16:80/";
		UriParser<char, string> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 6);
		REQUIRE(basicTest.authority.startPosition == basicURI + 7);
		REQUIRE(basicTest.authority.endPosition == basicURI + 22);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == basicURI + 9);
		REQUIRE(basicTest.host.endPosition == basicURI + 19);
		REQUIRE(basicTest.port.startPosition == basicURI + 20);
		REQUIRE(basicTest.port.endPosition == basicURI + 22);
		REQUIRE(basicTest.path.startPosition == NULL);
		REQUIRE(basicTest.path.endPosition == NULL);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 8") {
		char *basicURI = "urn:oasis:names:specification:docbook:dtd:xml:4.1.2";
		UriParser<char, string> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 3);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == NULL);
		REQUIRE(basicTest.host.endPosition == NULL);
		REQUIRE(basicTest.port.startPosition == NULL);
		REQUIRE(basicTest.port.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI + 4);
		REQUIRE(basicTest.path.endPosition == basicURI + 51);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
}
TEST_CASE("Test scheme parsing wstring", "[scheme]") {

	SECTION("Basic test for scheme wstring") {
		wchar_t *basicURI = L"http://www.arsenal.com";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
	}
	SECTION("Basic test for no scheme") {
		wchar_t *basicURI = L"//www.arsenal.com";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
	}
	SECTION("Empty string input - shouldn't blow up") {
		wchar_t *basicURI = L"";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
	}
	SECTION("just query and fragment - shouldn't blow up") {
		wchar_t *basicURI = L"?testing=true#somefragment";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
	}
	SECTION("Teting scheme with special characters") {
		wchar_t *basicURI = L"h+2t.0t-9p://www.arsenal.com";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 10);
	}
	SECTION("Teting scheme with special characters") {
		wchar_t *basicURI = L"h!2;0t*9p://www.arsenal.com";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == NULL);
		REQUIRE(basicTest.scheme.endPosition == NULL);
	}
}
TEST_CASE("Test authority parsing wstring", "[authority]") {

	SECTION("Basic test for authority") {
		wchar_t *basicURI = L"http://www.arsenal.com";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"http:";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"http:/path/here";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"http://www.arsenal.com?test=true";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"http://www.arsenal.com#somefragment";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"//www.arsenal.com#somefragment";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
TEST_CASE("Test path parsing wstring", "[path]") {

	SECTION("Basic test for path") {
		wchar_t *basicURI = L"http://www.arsenal.com/fixtures/first-team";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"/fixtures/first-team";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		wchar_t *temp = basicURI + 20;
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
		wchar_t *basicURI = L"fixtures/first-team";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"http://www.arsenal.com/fixtures/first-team?query=true";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"/fixtures/first-team?query=true";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"fixtures/first-team?query=true";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"http://www.arsenal.com/fixtures/first-team#somefragment";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"/fixtures/first-team#somefragment";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"fixtures/first-team#somefragment";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
TEST_CASE("Test query and fragment parsing wstring", "[query and fragment]") {

	SECTION("Basic test for path followed by fragment") {
		wchar_t *basicURI = L"http://www.arsenal.com/fixtures/first-team?query=false#somefragment";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"/fixtures/first-team?query=false#somefragment";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"fixtures/first-team?query=false#somefragment";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
TEST_CASE("Test simple authority parsing wstring", "[authority parsing]") {

	SECTION("Basic test for authority parsing") {
		wchar_t *basicURI = L"//username:password@www.arsenal.com:80";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"//username@www.arsenal.com:80";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		wchar_t *temp = basicURI + 29;
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
		wchar_t *basicURI = L"//www.arsenal.com:80";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
		wchar_t *basicURI = L"//www.arsenal.com";
		UriParser<wchar_t, wstring> basicTest(basicURI);
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
TEST_CASE("Test simple parsing with get functions wstring", "[simple parsing]") {

	SECTION("Basic test for authority parsing") {
		wchar_t *basicURI = L"http://username:password@www.arsenal.com:80/path1/path2?query=false#somefragment";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		wstring actualScheme(L"http");
		wstring actualUsername(L"username");
		wstring actualPassword(L"password");
		wstring actualHost(L"www.arsenal.com");
		wstring actualPort(L"80");
		wstring actualPath(L"/path1/path2");
		wstring actualQuery(L"query=false");
		wstring actualFragment(L"somefragment");
		wstring actualAuthority(L"//username:password@www.arsenal.com:80");
		wstring parseScheme = basicTest.getScheme();
		wstring parseUsername = basicTest.getUsername();
		wstring parsePassword = basicTest.getPassword();
		wstring parseHost = basicTest.getHost();
		wstring parsePort = basicTest.getPort();
		wstring parsePath = basicTest.getPath();
		wstring parseQuery = basicTest.getQuery();
		wstring parseFragment = basicTest.getFragment();
		wstring parseAuthority = basicTest.getAuthority();

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
TEST_CASE("Test string constructor wstring", "[string constructor]") {

	SECTION("Basic test for authority parsing") {
		wstring basicURI = L"hTtP://username:password@www.ARSEnal.com:80/path1/path2?query=false#somefragment";
		wchar_t *thisPntr = &basicURI[0];
		UriParser<wchar_t, wstring> basicTest(basicURI);
		wstring actualScheme(L"http");
		wstring actualUsername(L"username");
		wstring actualPassword(L"password");
		wstring actualHost(L"www.arsenal.com");
		wstring actualPort(L"80");
		wstring actualPath(L"/path1/path2");
		wstring actualQuery(L"query=false");
		wstring actualFragment(L"somefragment");
		wstring actualAuthority(L"//username:password@www.ARSEnal.com:80");
		wstring parseScheme = basicTest.getScheme();
		wstring parseUsername = basicTest.getUsername();
		wstring parsePassword = basicTest.getPassword();
		wstring parseHost = basicTest.getHost();
		wstring parsePort = basicTest.getPort();
		wstring parsePath = basicTest.getPath();
		wstring parseQuery = basicTest.getQuery();
		wstring parseFragment = basicTest.getFragment();
		wstring parseAuthority = basicTest.getAuthority();

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
		REQUIRE(basicTest.scheme.endPosition == thisPntr + 4);
		REQUIRE(basicTest.authority.startPosition == thisPntr + 5);
		REQUIRE(basicTest.authority.endPosition == thisPntr + 43);
		REQUIRE(basicTest.username.startPosition == thisPntr + 7);
		REQUIRE(basicTest.username.endPosition == thisPntr + 15);
		REQUIRE(basicTest.password.startPosition == thisPntr + 16);
		REQUIRE(basicTest.password.endPosition == thisPntr + 24);
		REQUIRE(basicTest.host.startPosition == thisPntr + 25);
		REQUIRE(basicTest.host.endPosition == thisPntr + 40);
		REQUIRE(basicTest.port.startPosition == thisPntr + 41);
		REQUIRE(basicTest.port.endPosition == thisPntr + 43);
		REQUIRE(basicTest.path.startPosition == thisPntr + 43);
		REQUIRE(basicTest.path.endPosition == thisPntr + 55);
		REQUIRE(basicTest.query.startPosition == thisPntr + 56);
		REQUIRE(basicTest.query.endPosition == thisPntr + 67);
		REQUIRE(basicTest.fragment.startPosition == thisPntr + 68);
		REQUIRE(basicTest.fragment.endPosition == thisPntr + 80);
	}
}
TEST_CASE("Exception testing wstring", "[exception testing]") {

	SECTION("Basic test for authority parsing") {
		//Catch won't let me use templated constructor with require throws macros
		wchar_t *basicURI = NULL;
		UriParser<wchar_t, wstring> basicTest(L"");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		wchar_t *basicURI = L"http://usern[]ame:password@www.arsenal.com:80/path1/path2?query=false#somefragment";
		UriParser<wchar_t, wstring> basicTest(L"");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		wchar_t *basicURI = L"http://username:pass:word@www.arsenal.com:80/path1/path2?query=false#somefragment";
		UriParser<wchar_t, wstring> basicTest(L"");
		REQUIRE_NOTHROW(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		wchar_t *basicURI = L"http://username:pas[]sword@www.arsenal.com:80/path1/path2?query=false#somefragment";
		UriParser<wchar_t, wstring> basicTest(L"");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		wchar_t *basicURI = L"http://username:password@www.ars[]enal.com:80/path1/path2?query=false#somefragment";
		UriParser<wchar_t, wstring> basicTest(L"");
		REQUIRE_NOTHROW(basicTest.resetUriParser(basicURI));
	}
	SECTION("Basic test for authority parsing") {
		wchar_t *basicURI = L"http://username:password@www.ars@enal.com:80/path1/path2?query=false#somefragment";
		UriParser<wchar_t, wstring> basicTest(L"");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		wchar_t *basicURI = L"http://username:password@www.ars:enal.com:80/path1/path2?query=false#somefragment";
		UriParser<wchar_t, wstring> basicTest(L"");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		wchar_t *basicURI = L"http://username:password@www.arsenal.com:8a0/path1/path2?query=false#somefragment";
		UriParser<wchar_t, wstring> basicTest(L"");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		wchar_t *basicURI = L"http://username:password@www.arsenal.com:80/path[]1/path2?query=false#somefragment";
		UriParser<wchar_t, wstring> basicTest(L"");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		wchar_t *basicURI = L"http://username:password@www.arsenal.com:80/path1/path2?query=f#alse#somefragment";
		UriParser<wchar_t, wstring> basicTest(L"");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		wchar_t *basicURI = L"http://username:password@www.arsenal.com:80/path1/path2?query=f[]alse#somefragment";
		UriParser<wchar_t, wstring> basicTest(L"");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		wchar_t *basicURI = L"http://username:password@www.arsenal.com:80/path1/path2?query=false#som[]efragment";
		UriParser<wchar_t, wstring> basicTest(L"");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
	SECTION("Basic test for authority parsing") {
		wchar_t *basicURI = L"ldap://[2001:db8::7/c=GB?objectClass?one";
		UriParser<wchar_t, wstring> basicTest(L"");
		REQUIRE_THROWS_AS(basicTest.resetUriParser(basicURI), invalid_argument);
	}
}
TEST_CASE("Examples from the standard wstring", "[examples]") {

	SECTION("Example 1") {
		wchar_t *basicURI = L"ftp://ftp.is.co.za/rfc/rfc1808.txt";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		wchar_t *temp = basicURI + 35;
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 3);
		REQUIRE(basicTest.authority.startPosition == basicURI + 4);
		REQUIRE(basicTest.authority.endPosition == basicURI + 18);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == basicURI + 6);
		REQUIRE(basicTest.host.endPosition == basicURI + 18);
		REQUIRE(basicTest.port.startPosition == NULL);
		REQUIRE(basicTest.port.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI + 18);
		REQUIRE(basicTest.path.endPosition == basicURI + 34);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 2") {
		wchar_t *basicURI = L"http://www.ietf.org/rfc/rfc2396.txt";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 19);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == basicURI + 7);
		REQUIRE(basicTest.host.endPosition == basicURI + 19);
		REQUIRE(basicTest.port.startPosition == NULL);
		REQUIRE(basicTest.port.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI + 19);
		REQUIRE(basicTest.path.endPosition == basicURI + 35);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 3") {
		wchar_t *basicURI = L"ldap://[2001:db8::7]/c=GB?objectClass?one";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 20);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == basicURI + 7);
		REQUIRE(basicTest.host.endPosition == basicURI + 20);
		REQUIRE(basicTest.port.startPosition == NULL);
		REQUIRE(basicTest.port.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI + 20);
		REQUIRE(basicTest.path.endPosition == basicURI + 25);
		REQUIRE(basicTest.query.startPosition == basicURI + 26);
		REQUIRE(basicTest.query.endPosition == basicURI + 41);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 3a - made up") {
		wchar_t *basicURI = L"ldap://[2001:db8::7]:1800/c=GB?objectClass?one";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == basicURI + 5);
		REQUIRE(basicTest.authority.endPosition == basicURI + 25);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == basicURI + 7);
		REQUIRE(basicTest.host.endPosition == basicURI + 20);
		REQUIRE(basicTest.port.startPosition == basicURI + 21);
		REQUIRE(basicTest.port.endPosition == basicURI + 25);
		REQUIRE(basicTest.path.startPosition == basicURI + 25);
		REQUIRE(basicTest.path.endPosition == basicURI + 30);
		REQUIRE(basicTest.query.startPosition == basicURI + 31);
		REQUIRE(basicTest.query.endPosition == basicURI + 46);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 4") {
		wchar_t *basicURI = L"mailto:John.Doe@example.com";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 6);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == NULL);
		REQUIRE(basicTest.host.endPosition == NULL);
		REQUIRE(basicTest.port.startPosition == NULL);
		REQUIRE(basicTest.port.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI + 7);
		REQUIRE(basicTest.path.endPosition == basicURI + 27);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 5") {
		wchar_t *basicURI = L"news:comp.infosystems.www.servers.unix";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 4);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == NULL);
		REQUIRE(basicTest.host.endPosition == NULL);
		REQUIRE(basicTest.port.startPosition == NULL);
		REQUIRE(basicTest.port.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI + 5);
		REQUIRE(basicTest.path.endPosition == basicURI + 38);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 6") {
		wchar_t *basicURI = L"tel:+1-816-555-1212";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 3);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == NULL);
		REQUIRE(basicTest.host.endPosition == NULL);
		REQUIRE(basicTest.port.startPosition == NULL);
		REQUIRE(basicTest.port.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI + 4);
		REQUIRE(basicTest.path.endPosition == basicURI + 19);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 7") {
		wchar_t *basicURI = L"telnet://192.0.2.16:80/";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 6);
		REQUIRE(basicTest.authority.startPosition == basicURI + 7);
		REQUIRE(basicTest.authority.endPosition == basicURI + 22);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == basicURI + 9);
		REQUIRE(basicTest.host.endPosition == basicURI + 19);
		REQUIRE(basicTest.port.startPosition == basicURI + 20);
		REQUIRE(basicTest.port.endPosition == basicURI + 22);
		REQUIRE(basicTest.path.startPosition == NULL);
		REQUIRE(basicTest.path.endPosition == NULL);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
	SECTION("Example 8") {
		wchar_t *basicURI = L"urn:oasis:names:specification:docbook:dtd:xml:4.1.2";
		UriParser<wchar_t, wstring> basicTest(basicURI);
		REQUIRE(basicTest.scheme.startPosition == basicURI);
		REQUIRE(basicTest.scheme.endPosition == basicURI + 3);
		REQUIRE(basicTest.authority.startPosition == NULL);
		REQUIRE(basicTest.authority.endPosition == NULL);
		REQUIRE(basicTest.username.startPosition == NULL);
		REQUIRE(basicTest.username.endPosition == NULL);
		REQUIRE(basicTest.password.startPosition == NULL);
		REQUIRE(basicTest.password.endPosition == NULL);
		REQUIRE(basicTest.host.startPosition == NULL);
		REQUIRE(basicTest.host.endPosition == NULL);
		REQUIRE(basicTest.port.startPosition == NULL);
		REQUIRE(basicTest.port.endPosition == NULL);
		REQUIRE(basicTest.path.startPosition == basicURI + 4);
		REQUIRE(basicTest.path.endPosition == basicURI + 51);
		REQUIRE(basicTest.query.startPosition == NULL);
		REQUIRE(basicTest.query.endPosition == NULL);
		REQUIRE(basicTest.fragment.startPosition == NULL);
		REQUIRE(basicTest.fragment.endPosition == NULL);
	}
}

int main(int argc, char* const argv[])
{
	int result = Catch::Session().run(argc, argv);
	return result;
}

