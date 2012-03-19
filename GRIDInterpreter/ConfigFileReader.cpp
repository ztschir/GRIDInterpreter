//
//  ConfigFileReader.cpp
//  GRIDInterpreter
//
//  Created by Zachary Tschirhart on 2/15/12.
//  Copyright (c) 2012 Radio Navigation Lab. All rights reserved.
//

#include "ConfigFileReader.h"
using namespace std;

template <typename T> string Convert::T_to_string(T const &val) {
    ostringstream ostr;
	ostr << val;
	return ostr.str();
}
    
template <typename T> T Convert::string_to_T(string const &val) {
	istringstream istr(val);
	T returnVal;
	if (!(istr >> returnVal))
		exitWithError("Config: Not a valid " + (string)typeid(T).name() + " received!\n");
       
	return returnVal;
}
    
template <> string Convert::string_to_T(string const &val){
	return val;
}
void Convert::exitWithError(const string &error) {
	cout << error;
	cin.ignore();
	cin.get();
	
}



void ConfigFileReader::removeComment(string &line) const{
    if (line.find(';') != line.npos)
        line.erase(line.find(';'));
}

bool ConfigFileReader::onlyWhitespace(const string &line) const{
    return (line.find_first_not_of(' ') == line.npos);
}

bool ConfigFileReader::validLine(const string &line) const{
    string temp = line;
    temp.erase(0, temp.find_first_not_of("\t "));
    if (temp[0] == '=')
        return false;
    
    for (size_t i = temp.find('=') + 1; i < temp.length(); i++)
        if (temp[i] != ' ')
            return true;
    
    return false;
}

void ConfigFileReader::extractKey(string &key, size_t const &sepPos, const string &line) const{
    key = line.substr(0, sepPos);
    if (key.find('\t') != line.npos || key.find(' ') != line.npos)
        key.erase(key.find_first_of("\t "));
}

void ConfigFileReader::extractValue(string &value, size_t const &sepPos, const string &line) const{
    value = line.substr(sepPos + 1);
    value.erase(0, value.find_first_not_of("\t "));
    value.erase(value.find_last_not_of("\t ") + 1);
}

void ConfigFileReader::extractContents(const string &line) {
    string temp = line;
    temp.erase(0, temp.find_first_not_of("\t "));
    size_t sepPos = temp.find('=');
    
    string key, value;
    extractKey(key, sepPos, temp);
    extractValue(value, sepPos, temp);
    
    if (!keyExists(key))
        contents.insert(pair<string, string>(key, value));
    else
        Convert::exitWithError("CFG: Can only have unique key names!\n");
}

void ConfigFileReader::parseLine(const string &line, size_t const lineNo)
{
    if (line.find('=') == line.npos)
        Convert::exitWithError("CFG: Couldn't find separator on line: " + Convert::T_to_string(lineNo) + "\n");
    
    if (!validLine(line))
        Convert::exitWithError("CFG: Bad format for line: " + Convert::T_to_string(lineNo) + "\n");
    
    extractContents(line);
}

void ConfigFileReader::ExtractKeys()
{
    ifstream file;
    file.open(fName.c_str());
    if (!file)
        Convert::exitWithError("CFG: File " + fName + " couldn't be found!\n");
    
    string line;
    size_t lineNo = 0;
    while (getline(file, line))
    {
        lineNo++;
        string temp = line;
        
        if (temp.empty())
            continue;
        
        removeComment(temp);
        if (onlyWhitespace(temp))
            continue;
        
        parseLine(temp, lineNo);
    }
    
    file.close();
}

ConfigFileReader::ConfigFileReader(const string &fName){
    this->fName = fName;
    ExtractKeys();
}

bool ConfigFileReader::keyExists(const string &key) const{
    return contents.find(key) != contents.end();
}

string ConfigFileReader::getValueOfKey(const string &key) const{
    if (!keyExists(key))
        return "Found Nothing";
    
    return contents.find(key)->second;
}
