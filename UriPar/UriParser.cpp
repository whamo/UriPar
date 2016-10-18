#include "UriParser.h"
using namespace std;

UriParser::UriParser(char *in_uri)
{
	resetUriSegments();
	//parse the string
	uriInput = in_uri;
	parseInputUri(in_uri);
}

UriParser::UriParser(string &in_uri)
{
	resetUriSegments();
	//parse the string
	uriInput = &in_uri[0];
	parseInputUri(&in_uri[0]);
}

void UriParser::parseInputUri(char *in_uri)
{
	if (in_uri == NULL)
	{
		//input is a null string - throw an exception
		throw invalid_argument("Null input string exception");
	}
	//try to parse the scheme
	char *current = in_uri;
	size_t totalSize = strlen(current);
	if (isalpha(*current)) parseScheme(current, current + totalSize - 1);
	else if (*current == '/')
	{
		char *next = ++current;
		if (*next == '/') parseAuthority(--current, current + totalSize - 1);
		else parsePath(--current, current + totalSize - 1);
	}
	else if (*current == ':') parseAuthority(current, current + totalSize - 1);
	else if (*current == '?') parseQuery(current, current + totalSize - 1); /* parse as query - empty scheme authority and path */
	else if (*current == '#') parseFragment(current, current + totalSize - 1); /* parse as fragment - empty scheme authority path and query */
	else /*could be the remainder of pchar % - _ . ~ - then parse as path*/;
}

void UriParser::parseScheme(char *in_current, char *in_last)
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
	else if ((isUnreservedCharacter(*current) || isPercentEncoded(*current) || isSubDelimiter(*current) || (*current == ':') || (*current == '@') || (*current == '/')))
	{
		//no scheme found reset the start
		scheme.startPosition = NULL;
		parsePath(in_current, in_last); /*attempt to parse the path (note - cannot be authority) query and fragment here*/
	}
	else
	{
		scheme.startPosition = NULL;
		throw invalid_argument("Malformed string at location " + to_string(current - uriInput) + " in scheme");
	}
}

void UriParser::parseAuthority(char *in_current, char *in_last)
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
		if (*current == '/') parsePath(current, in_last); /*parse the path here*/
		else if (*current == '?') parseQuery(current, in_last); /*parse the query here*/
		else if (*current == '#') parseFragment(current, in_last); /*parse the fragment here*/
		//sub parse the authority section here
		subParseAuthority(authority.startPosition, authority.endPosition-1);
	}
	else parsePath(in_current, in_last); /*parsePath(in_current here*/
}
void UriParser::subParseAuthority(char *in_start, char *in_end)
{
	char *current = in_start;
	//always have a double slash to start authority
	current++;
	current++;
	parseUsernamePassword(current, in_end);
}
void UriParser::parseUsernamePassword(char *in_current, char *in_end)
{
	char *current = in_current;
	//authority may be empty
	if (current < in_end)
	{
		username.startPosition = current;
		while ((current <= in_end) && (*current != '/') && (*current != '?')
			&& (*current != '#') && (*current != '@'))
		{
			if (!(isUnreservedCharacter(*current) || isPercentEncoded(*current) || isSubDelimiter(*current) || (*current == ':')))
			{
				throw invalid_argument("Malformed string at location " + to_string(current - uriInput) + " in username");
			}
			if (*current == ':')
			{
				username.endPosition = current;
				current++;
				password.startPosition = current;
			}
			else current++;
		}
		if (*current == '@')
		{
			if (password.startPosition == NULL) username.endPosition = current;
			else password.endPosition = current;
			parseHost(++current, in_end);
		}
		else
		{
			username.startPosition = NULL;
			username.endPosition = NULL;
			password.startPosition = NULL;
			password.endPosition = NULL;
			parseHost(in_current, in_end);
		}
	}
}
void UriParser::parseHost(char *in_current, char *in_end)
{
	char *current = in_current;
	host.startPosition = current;
	while ((current <= in_end) && (*current != '/') && (*current != '?')
		&& (*current != '#'))
	{
		if (!(isUnreservedCharacter(*current) || isPercentEncoded(*current) || isSubDelimiter(*current) || (*current == '[') || (*current == ']') || (*current == ':')))
		{
			throw invalid_argument("Malformed string at location " + to_string(current - uriInput) + " in host");
		}
		if ((port.startPosition != NULL) && !(isdigit(*current))) throw invalid_argument("Malformed string at location " + to_string(current - uriInput) + " in port");
		if (*current == ':')
		{
			host.endPosition = current;
			current++;
			port.startPosition = current;
		}
		else current++;
	}
	if (port.startPosition == NULL) host.endPosition = current;
	else port.endPosition = current;
}
void UriParser::parsePath(char *in_current, char *in_last)
{
	char *current = in_current;
	//note that the path may be empty - i.e. this could already be the end of the string
	if (current < in_last)
	{
		path.startPosition = current;
		current++;
		while ((current <= in_last) && (*current != '?') && (*current != '#'))
		{
			//ignoring the extra conditions on : and @ for now
			if (!(isUnreservedCharacter(*current) || isPercentEncoded(*current) || isSubDelimiter(*current) || (*current == ':') || (*current == '@') || (*current == '/')))
			{
				throw invalid_argument("Malformed string at location " + to_string(current - uriInput) + " in path");
			}
			current++;
		}
		path.endPosition = current;
		if (*current == '?') parseQuery(current, in_last); /*parse the query here*/
		else if (*current == '#') parseFragment(current, in_last); /*parse the fragment here*/
	}
}
void UriParser::parseQuery(char *in_current, char *in_last)
{
	char *current = in_current;
	current++; //found the ? character move to the next
	query.startPosition = current;
	while ((current <= in_last) && (*current != '#'))
	{
		if (!(isUnreservedCharacter(*current) || isPercentEncoded(*current) || isSubDelimiter(*current) || (*current == ':') || (*current == '@') || (*current == '/') || (*current == '?')))
		{
			throw invalid_argument("Malformed string at location " + to_string(current - uriInput) + " in query");
		}
		current++;
	}
	query.endPosition = current;
	if (*current == '#') parseFragment(current, in_last);/*parse the fragment here*/
}
void UriParser::parseFragment(char *in_current, char *in_last)
{
	char *current = in_current;
	current++; //found the # character move to the next
	fragment.startPosition = current;
	while (current <= in_last)
	{
		if (!(isUnreservedCharacter(*current) || isPercentEncoded(*current) || isSubDelimiter(*current) || (*current == ':') || (*current == '@') || (*current == '/') || (*current == '?')))
		{
			throw invalid_argument("Malformed string at location " + to_string(current - uriInput) + " in fragment");
		}
		current++;
	}
	fragment.endPosition = current;
}
inline bool UriParser::isValidSchemeCharacter(char in_test) const
{
	return isalnum(in_test) || (in_test == '+') || (in_test == '-') || (in_test == '.');
}

inline bool UriParser::isUnreservedCharacter(char in_test) const
{
	return isalnum(in_test) || (in_test == '-') || (in_test == '_') || (in_test == '.') || (in_test == '~');
}

inline bool UriParser::isPercentEncoded(char in_test) const
{
	return isalnum(in_test) || (in_test == '%');
}

inline bool UriParser::isSubDelimiter(char in_test) const
{
	return (in_test == '!') || (in_test == '$') || (in_test == '&') || (in_test == '\'') || (in_test == '(') || (in_test == ')')
		|| (in_test == '*') || (in_test == '+') || (in_test == ',') || (in_test == ';') || (in_test == '=');
}

std::string UriParser::getScheme() const
{
	if ((scheme.startPosition != NULL) && (scheme.endPosition != NULL))
	{
		return std::string(scheme.startPosition, scheme.endPosition - scheme.startPosition);
	}
	else return std::string();
}

std::string UriParser::getAuthority() const
{
	if ((authority.startPosition != NULL) && (authority.endPosition != NULL))
	{
		return std::string(authority.startPosition, authority.endPosition - authority.startPosition);
	}
	else return std::string();
}

std::string UriParser::getUsername() const
{
	if ((username.startPosition != NULL) && (username.endPosition != NULL))
	{
		return std::string(username.startPosition, username.endPosition - username.startPosition);
	}
	else return std::string();
}

std::string UriParser::getPassword() const
{
	if ((password.startPosition != NULL) && (password.endPosition != NULL))
	{
		return std::string(password.startPosition, password.endPosition - password.startPosition);
	}
	else return std::string();
}

std::string UriParser::getHost() const
{
	if ((host.startPosition != NULL) && (host.endPosition != NULL))
	{
		return std::string(host.startPosition, host.endPosition - host.startPosition);
	}
	else return std::string();
}

std::string UriParser::getPort() const
{
	if ((port.startPosition != NULL) && (port.endPosition != NULL))
	{
		return std::string(port.startPosition, port.endPosition - port.startPosition);
	}
	else return std::string();
}

std::string UriParser::getPath() const
{
	if ((path.startPosition != NULL) && (path.endPosition != NULL))
	{
		return std::string(path.startPosition, path.endPosition - path.startPosition);
	}
	else return std::string();
}

std::string UriParser::getQuery() const
{
	if ((query.startPosition != NULL) && (query.endPosition != NULL))
	{
		return std::string(query.startPosition, query.endPosition - query.startPosition);
	}
	else return std::string();
}

std::string UriParser::getFragment() const
{
	if ((fragment.startPosition != NULL) && (fragment.endPosition != NULL))
	{
		return std::string(fragment.startPosition, fragment.endPosition - fragment.startPosition);
	}
	else return std::string();
}

void UriParser::resetUriSegments()
{
	scheme.startPosition = NULL;
	scheme.endPosition = NULL;
	authority.startPosition = NULL;
	authority.endPosition = NULL;
	username.startPosition = NULL;
	username.endPosition = NULL;
	password.startPosition = NULL;
	password.endPosition = NULL;
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