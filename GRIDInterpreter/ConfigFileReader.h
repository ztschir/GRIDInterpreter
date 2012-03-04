//
//  ConfigFileReader.h
//  GRIDInterpreter
//
//  Created by Zachary Tschirhart on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef GRIDInterpreter_ConfigFileReader_h
#define GRIDInterpreter_ConfigFileReader_h

//#include <iostream>
//#include <string>
//#include <sstream>
//#include <map>
//#include <fstream>

#include "TypeIdentifiers.h"

using namespace std;

class Convert{
public:
	template <typename T> static string T_to_string(T const &val);
	template <typename T> T static string_to_T(string const &val);
	template <typename T> static string string_to_T(string const &val);
    void static exitWithError(const string &error);
};

class ConfigFileReader{
private:
	map<string, string> contents;
	string fName;
	void removeComment(string &line) const;
	bool onlyWhitespace(const string &line) const;
	bool validLine(const string &line) const;
	void extractKey(string &key, size_t const &sepPos, const string &line) const;
	void extractValue(string &value, size_t const &sepPos, const string &line) const;
	void extractContents(const string &line) ;
	void parseLine(const string &line, size_t const lineNo);
	void ExtractKeys();
public:
	ConfigFileReader(const string &fName);
	bool keyExists(const string &key) const;
    string getValueOfKey(const string &key) const;
};

#endif
