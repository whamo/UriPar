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
	size_t totalSize = strlen(current);
	if (isalpha(*current)) parseScheme(current, current + totalSize - 1);
	else if (*current == '/')
	{
		char *next = ++current;
		if (*next == '/') parseAuthority(current, current + totalSize - 1);
		else /*parse the path section here*/;
	}
	else if (*current == ':')/*empty and parse authority section here*/;
	else /*parse the path as relative and then query and fragment part here*/;
}

void UriPar::parseScheme(char *in_current, char *in_last)
{
	char *current = in_current;
	scheme.startPosition = in_current;
	while ((current <= in_last)&&(*current != ':')&&isValidSchemeCharacter(*current)) current++;
	//either hit the end, found an invalid character or found the end of the scheme
	if (*current == ':')
	{
		scheme.endPosition = current;
		current++;
		parseAuthority(current, in_last);
	}
	else /*attempt to parse the path query and fragment here*/;
}

void UriPar::parseAuthority(char *in_current, char *in_last)
{
	char *current = in_current;
	char *next = ++current;
	if (*next == '/')
	{
		authority.startPosition = in_current;
		current++;
		while ((current <= in_last) && (*current != '/') && (*current != '?') 
			&& (*current != '#')) current++;
		//authority is quite robust, accept all the inner text here
		authority.endPosition = current;
		if (*current == '/') /*parse the path here*/;
		else if (*current == '?') /*parse the query here*/;
		else if (*current == '#') /*parse the query here*/;
		//sub parse the authority section here into user port blah blah blah
	}
	else /*parsePath(in_current here*/;
}
bool UriPar::isValidSchemeCharacter(char in_test)
{
	return isalnum(in_test) || (in_test == '+') || (in_test == '-') || (in_test == '.');
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