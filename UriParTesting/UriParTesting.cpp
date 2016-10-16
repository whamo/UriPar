// UriParTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "UriPar.h"

int main(int argc, char* const argv[])
{
	UriPar initTest("some string");
	int result = Catch::Session().run(argc, argv);

	return result;
}

