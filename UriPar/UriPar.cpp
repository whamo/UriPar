#include "UriPar.h"

UriPar::UriPar(char *in_uri)
{
	//simple constructor here
	int len = strlen(in_uri);
	//parse the string
	parseInputUri(in_uri);
}
void UriPar::parseInputUri(char *in_uri)
{
	if (in_uri == NULL)
	{
		//input a null string - throw an exception
		throw("Null input string exception");
	}
	//try to parse the scheme
	char *current = in_uri;
	parseScheme(current, current + strlen(current) - 1);
}

void UriPar::parseScheme(char *in_current, char *in_last)
{
	char *current = in_current;
	while (current <= in_last)
	{
		current++;
	}

	
}