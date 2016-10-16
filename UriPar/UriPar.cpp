#include "UriPar.h"

UriPar::UriPar(char *in_uri)
{
	resetUriSegments();
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

void UriPar::resetUriSegments()
{
	scheme.startPosition = NULL;
	scheme.endPosition = NULL;
	authority.startPosition = NULL;
	authority.endPosition = NULL;
	host.startPosition = NULL;
	host.endPosition = NULL;
	port.startPosition = NULL;
	port.endPosition = NULL;
	path.startPosition = NULL;
	path.endPosition = NULL;
	query.startPosition = NULL;
	query.endPosition = NULL;
	fragment.startPosition = NULL;
	fragment.endPosition = NULL;
}