//
//  TableColumnValues.h
//  GRIDInterpreter
//
//  The TableColumnValues class holds a single columns worth of data. 
//  There are several ways to access set and get the data for each datatype.
//  These used to be linked list data structures but the overhead (~4x) was not
//  worth the cost of having O(1) insert and delete times. Now it's using vectors.
//
//  Created by Zachary Tschirhart on 2/13/12.
//  Copyright (c) 2012 Radio Navigation Lab. All rights reserved.
//

#ifndef GRIDInterpreter_TableColumnValue_h
#define GRIDInterpreter_TableColumnValue_h

#include "TypeIdentifiers.h"

using namespace std;

class TableColumnValues{
public:
    TableColumnValues(string columnNameIn, char valueTypeIn, bool isFileReadInValueIn);
    
    TableColumnValues(vector<int>* value, bool isFileReadInValueIn);
    TableColumnValues(vector<float>* value, bool isFileReadInValueIn);
    TableColumnValues(vector<double>* value, bool isFileReadInValueIn);
    TableColumnValues(vector<string>* value, bool isFileReadInValueIn);
    
    void setValues(vector<int>* value);
    void setValues(vector<float>* value);
    void setValues(vector<double>* value);
    void setValues(vector<string>* value);
    
    void appendValues(vector<int>& value);
    void appendValues(vector<float>& value);
    void appendValues(vector<double>& value);
    void appendValues(vector<string>& value);
    
    void addValue(int& value);
    void addValue(float& value);
    void addValue(double& value);
    void addValue(string& value);
    

    
    vector<int> *getIntValues();
    vector<float> *getFloatValues();
    vector<double> *getDoubleValues();
    vector<string> *getStringValues();
    
    int popTopIntValue();
    float popTopFloatValue();
    double popTopDoubleValue();
    string popTopStringValue();
    
    bool isEmpty();
    string getColumnName();
    char getValueType();
    int getRowCount();
    bool isReadInValue();
    
private:
    char valueType;
    string columnName;
    bool isFileReadInValue;
    
    vector<int> *intValues;
    vector<float> *floatValues;
    vector<double> *doubleValues;
    vector<string> *stringValues;
    
};

#endif
