UriParser class implemented by W. Hamilton 19-Oct-2016
Built in Visual Studio 2015

------------------------------------------------------------------------------------------------------------------------------------------------------
Installation:
Copy the .hpp file to your project

------------------------------------------------------------------------------------------------------------------------------------------------------
Usage:
#include UriParser.hpp

------------------------------------------------------------------------------------------------------------------------------------------------------
About:
This is a simple implementation of a URI parsing class. It can handle both char/string and wchar_t/wstring combinations.

It has been tested with the unit tests you see in the associated testing project. All development and testing was completed using Visual Studio 2015.

------------------------------------------------------------------------------------------------------------------------------------------------------
Example Code;
		string basicURI = "hTtP://username:password@www.ARSENAL.com:80/path1/path2?query=false#somefragment";
		UriParser<char, string> basicTest(basicURI);
		cout << basicTest.getScheme() << endl;
		cout << basicTest.getUsername() << endl;
		cout <<  basicTest.getPassword() << endl;
		cout <<  basicTest.getHost() << endl;
		cout <<  basicTest.getPort() << endl;
		cout <<  basicTest.getPath() << endl;
		cout <<  basicTest.getQuery() << endl;
		cout <<  basicTest.getFragment() << endl;
		cout <<  basicTest.getAuthority() << endl;

		<--output-->
		http
		username
		password
		www.arsenal.com
		80
		/path1/path2
		query=false
		somefragment
		//username:password@www.ARSEnal.com:80

Identical output will be produced by the code;

		wstring wbasicURI = L"hTtP://username:password@www.ARSEnal.com:80/path1/path2?query=false#somefragment";
		UriParser<wchar_t, wstring> wbasicTest(wbasicURI);
		wcout << wbasicTest.getScheme() << endl;
		wcout << wbasicTest.getUsername() << endl;
		wcout << wbasicTest.getPassword() << endl;
		wcout << wbasicTest.getHost() << endl;
		wcout << wbasicTest.getPort() << endl;
		wcout << wbasicTest.getPath() << endl;
		wcout << wbasicTest.getQuery() << endl;
		wcout << wbasicTest.getFragment() << endl;
		wcout << wbasicTest.getAuthority() << endl;

------------------------------------------------------------------------------------------------------------------------------------------------------
Warranty/License:
This software comes with no warranty or license.

------------------------------------------------------------------------------------------------------------------------------------------------------
References:
https://tools.ietf.org/html/rfc3986