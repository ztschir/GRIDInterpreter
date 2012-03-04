//
//  TableColumnValues.h
//  GRIDInterpreter
//
//  The TableColumnValues class holds a single columns worth of data. 
//  There are several ways to access set and get the data for each datatype,
//  but just remember that each datatype is a linked list, so O(1) add, delete, 
//  and access to first or last value. It's O(n) for access to any other value in the set.
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
    TableColumnValues(string columnName, char valueTypeIn);
    
    TableColumnValues(list<int>* value);
    TableColumnValues(list<float>* value);
    TableColumnValues(list<double>* value);
    TableColumnValues(list<string>* value);
    
    void setValues(list<int>* value);
    void setValues(list<float>* value);
    void setValues(list<double>* value);
    void setValues(list<string>* value);
    
    void appendValues(list<int>& value);
    void appendValues(list<float>& value);
    void appendValues(list<double>& value);
    void appendValues(list<string>& value);
    
    void addValue(int& value);
    void addValue(float& value);
    void addValue(double& value);
    void addValue(string& value);
    
    bool isEmpty();
    string getColumnName();
    char getValueType();
    int getRowCount();
    
    list<int>* getIntValues();
    list<float>* getFloatValues();
    list<double>* getDoubleValues();
    list<string>* getStringValues();
    
private:
    char valueType;
    string columnName;
    
    list<int> *intValues;
    list<float> *floatValues;
    list<double> *doubleValues;
    list<string> *stringValues;
    
};

#endif
