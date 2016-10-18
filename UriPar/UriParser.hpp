#pragma once
#ifndef URIPARSER_H
#define URIPARSER_H

#include <string>
using namespace std;

//URI parsing class - designed to take <char,string> and <wchar_t,wstring> templates
template <class charType>
class UriSegment
{
public:
	charType *startPosition;
	charType *endPosition;
};
template <class charType, class stringType>
class UriParser
{
public:
	//constructor - string or pointer
	UriParser(stringType &in_uri)
	{
		resetUriParser(in_uri);
	}
	UriParser(charType *in_uri)
	{
		resetUriParser(in_uri);
	}
	void resetUriParser(stringType &in_uri)
	{
		resetUriSegments();
		//parse the string
		uriInput = &in_uri[0];
		parseInputUri(&in_uri[0]);
	}
	void resetUriParser(charType *in_uri)
	{
		resetUriSegments();
		//parse the string
		uriInput = in_uri;
		parseInputUri(in_uri);
	}
	//a copy of the beginning pointer
	charType *uriInput;
	//and the public segment definitions
	UriSegment<charType> scheme;
	UriSegment<charType> authority;
	UriSegment<charType> username;
	UriSegment<charType> password;
	UriSegment<charType> host;
	UriSegment<charType> port;
	UriSegment<charType> path;
	UriSegment<charType> query;
	UriSegment<charType> fragment;
	//get functions
	//get functions will pull out strings of the different segments
	stringType getScheme() const
	{
		if ((scheme.startPosition != NULL) && (scheme.endPosition != NULL))
		{
			stringType returnString(scheme.startPosition, scheme.endPosition - scheme.startPosition);
			std::transform(returnString.begin(), returnString.end(), returnString.begin(), ::tolower);
			return returnString;
		}
		else return stringType();
	}
	stringType getAuthority() const
	{
		if ((authority.startPosition != NULL) && (authority.endPosition != NULL))
		{
			return stringType(authority.startPosition, authority.endPosition - authority.startPosition);
		}
		else return stringType();
	}
	stringType getUsername() const
	{
		if ((username.startPosition != NULL) && (username.endPosition != NULL))
		{
			return stringType(username.startPosition, username.endPosition - username.startPosition);
		}
		else return stringType();
	}
	stringType getPassword() const
	{
		if ((password.startPosition != NULL) && (password.endPosition != NULL))
		{
			return stringType(password.startPosition, password.endPosition - password.startPosition);
		}
		else return stringType();
	}
	stringType getHost() const
	{
		if ((host.startPosition != NULL) && (host.endPosition != NULL))
		{
			stringType returnString(host.startPosition, host.endPosition - host.startPosition);
			std::transform(returnString.begin(), returnString.end(), returnString.begin(), ::tolower);
			return returnString;
		}
		else return stringType();
	}
	stringType getPort() const
	{
		if ((port.startPosition != NULL) && (port.endPosition != NULL))
		{
			return stringType(port.startPosition, port.endPosition - port.startPosition);
		}
		else return stringType();
	}
	stringType getPath() const
	{
		if ((path.startPosition != NULL) && (path.endPosition != NULL))
		{
			return stringType(path.startPosition, path.endPosition - path.startPosition);
		}
		else return stringType();
	}
	stringType getQuery() const
	{
		if ((query.startPosition != NULL) && (query.endPosition != NULL))
		{
			return stringType(query.startPosition, query.endPosition - query.startPosition);
		}
		else return stringType();
	}
	stringType getFragment() const
	{
		if ((fragment.startPosition != NULL) && (fragment.endPosition != NULL))
		{
			return stringType(fragment.startPosition, fragment.endPosition - fragment.startPosition);
		}
		else return stringType();
	}

private:
	//make the parse function private
	void parseInputUri(charType *in_uri)
	{
		if (in_uri == NULL)
		{
			//input is a null string - throw an exception
			throw invalid_argument("Null input string exception");
		}
		//try to parse the scheme
		charType *current = in_uri;
		size_t totalSize = strlen(current);
		if (isalpha(*current)) parseScheme(current, current + totalSize - 1);
		else if (*current == '/')
		{
			charType *next = ++current;
			if (*next == '/') parseAuthority(--current, current + totalSize - 1);
			else parsePath(--current, current + totalSize - 1);
		}
		else if (*current == ':') parseAuthority(current, current + totalSize - 1);
		else if (*current == '?') parseQuery(current, current + totalSize - 1); /* parse as query - empty scheme authority and path */
		else if (*current == '#') parseFragment(current, current + totalSize - 1); /* parse as fragment - empty scheme authority path and query */
		else /*could be the remainder of pchar % - _ . ~ - then parse as path*/;
	}
	void parseScheme(charType *in_current, charType *in_last)
	{
		charType *current = in_current;
		scheme.startPosition = in_current;
		while ((current <= in_last) && (*current != ':') && isValidSchemeCharacter(*current)) current++;
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
	void parseAuthority(charType *in_current, charType *in_last)
	{
		charType *current = in_current;
		charType *next = ++current;
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
			subParseAuthority(authority.startPosition, authority.endPosition - 1);
		}
		else parsePath(in_current, in_last); /*parsePath(in_current here*/
	}
	void subParseAuthority(charType *in_start, charType *in_end)
	{
		charType *current = in_start;
		//always have a double slash to start authority
		current++;
		current++;
		if (current < in_end)
		{
			//user info is optional - there is a special case here when the [] charaters are used for a host
			if (*current == '[') parseHost(current, in_end);
			else parseUsernamePassword(current, in_end);
		}
	}
	void parseUsernamePassword(charType *in_current, charType *in_end)
	{
		charType *current = in_current;
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
	void parseHost(charType *in_start, charType *in_end)
	{
		charType *current = in_start;
		//when the ope square bracket is found, the colon does not indicate a port unless it is closed again
		bool parseColonSwitch = false;
		host.startPosition = current;
		while ((current <= in_end) && (*current != '/') && (*current != '?')
			&& (*current != '#'))
		{
			if (*current == '[') parseColonSwitch = true;
			if (!(isUnreservedCharacter(*current) || isPercentEncoded(*current) || isSubDelimiter(*current) || (*current == '[') || (*current == ']') || (*current == ':')))
			{
				throw invalid_argument("Malformed string at location " + to_string(current - uriInput) + " in host");
			}
			if ((port.startPosition != NULL) && !(isdigit(*current))) throw invalid_argument("Malformed string at location " + to_string(current - uriInput) + " in host");
			if ((*current == ':') && (!parseColonSwitch))
			{
				host.endPosition = current;
				current++;
				port.startPosition = current;
			}
			else if ((*current == ']') && (parseColonSwitch))
			{
				parseColonSwitch = false;
				current++;
				//must still find the end as per usual
			}
			else current++;
		}
		if (parseColonSwitch) throw invalid_argument("Malformed string IPv6/IPvFut address square bracket not closed " + to_string(current - uriInput) + " in host");
		if (port.startPosition == NULL) host.endPosition = current;
		else port.endPosition = current;
	}
	void parsePath(charType *in_current, charType *in_last)
	{
		charType *current = in_current;
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
	void parseQuery(charType *in_current, charType *in_last)
	{
		charType *current = in_current;
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
	void parseFragment(charType *in_current, charType *in_last)
	{
		charType *current = in_current;
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
	void resetUriSegments()
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
	inline bool isValidSchemeCharacter(charType in_test)
	{
		return isalnum(in_test) || (in_test == '+') || (in_test == '-') || (in_test == '.');
	}
	inline bool isUnreservedCharacter(charType in_test)
	{
		return isalnum(in_test) || (in_test == '-') || (in_test == '_') || (in_test == '.') || (in_test == '~');
	}
	inline bool isPercentEncoded(charType in_test)
	{
		return isalnum(in_test) || (in_test == '%');
	}
	inline bool isSubDelimiter(charType in_test) const
	{
		return (in_test == '!') || (in_test == '$') || (in_test == '&') || (in_test == '\'') || (in_test == '(') || (in_test == ')')
			|| (in_test == '*') || (in_test == '+') || (in_test == ',') || (in_test == ';') || (in_test == '=');
	}
};

#endif