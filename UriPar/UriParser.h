#pragma once
#ifndef URIPARSER_H
#define URIPARSER_H

#include <string>
using namespace std;

typedef struct UriSegment
{
	char *startPosition;
	char *endPosition;
} UriSegment;

class UriParser
{
public:
	//constructor - string or pointer
	UriParser(string &in_uri);
	UriParser(char *in_uri);
	//get functions
	//get functions will pull out strings of the different segments
	string getScheme() const;
	string getAuthority() const;
	string getUsername() const;
	string getPassword() const;
	string getHost() const;
	string getPort() const;
	string getPath() const;
	string getQuery() const;
	string getFragment() const;
	//a copy of the beginning pointer
	char *uriInput;
	//and the public segment definitions
	UriSegment scheme;
	UriSegment authority;
	UriSegment username;
	UriSegment password;
	UriSegment host;
	UriSegment port;
	UriSegment path;
	UriSegment query;
	UriSegment fragment;

private:
	//make the parse function private
	void parseInputUri(char *in_uri);
	void parseScheme(char *in_current, char *in_last);
	void parseAuthority(char *in_current, char *in_last);
	void subParseAuthority(char *in_start, char *in_end);
	void parseUsernamePassword(char *in_current, char *in_end);
	void parseHost(char *in_start, char *in_end);
	void parsePath(char *in_current, char *in_last);
	void parseQuery(char *in_current, char *in_last);
	void parseFragment(char *in_current, char *in_last);
	void resetUriSegments();
	inline bool isValidSchemeCharacter(char in_test) const;
	inline bool isUnreservedCharacter(char in_test) const;
	inline bool isPercentEncoded(char in_test) const;
	inline bool isSubDelimiter(char in_test) const;
	int uriLength;
	string inputUri;
};

#endif