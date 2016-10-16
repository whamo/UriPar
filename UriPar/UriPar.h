#pragma once
#ifndef URIPAR_H
#define URIPAR_H

#include <string>
using namespace std;

struct UriSegment
{
	char *startPosition;
	char *endPosition;
};

class UriPar
{
public:
	//constructor - string or pointer
	UriPar(string in_uri);
	UriPar(char *in_uri);
	//get functions
	//get functions will pull out strings of the different segments
	string getScheme() const;
	string getAuthority() const;
	string getPath() const;
	string getQuery() const;
	string getFragment() const;
	//and the public segment definitions
	UriSegment *scheme;
	UriSegment *authority;
	UriSegment *path;
	UriSegment *query;
	UriSegment *fragment;

private:
	//make the parse function private
	void parseInputUri(char *in_uri);
	void parseScheme(char *in_current, char *in_last);
	int uriLength;
	string inputUri;
};

#endif