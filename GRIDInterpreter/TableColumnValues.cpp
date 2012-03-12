//
//  TableColumnValue.cpp
//  GRIDInterpreter
//
//  Created by Zachary Tschirhart on 2/13/12.
//  Copyright (c) 2012 Radio Navigation Lab. All rights reserved.
//

#include "TableColumnValues.h"

using namespace std;

TableColumnValues::TableColumnValues(string columnNameIn, char valueTypeIn, bool isFileReadInValueIn) : columnName(columnNameIn), valueType(valueTypeIn), isFileReadInValue(isFileReadInValueIn){
    isFileReadInValue = isFileReadInValueIn;
    columnName = columnNameIn;
    valueType = valueTypeIn;
    
    switch (valueType){
        case INT_VALUE:{
            intValues = new list<int>();
        }
        case DOUBLE_VALUE:{
            doubleValues = new list<double>();
        }
        case FLOAT_VALUE:{
            floatValues = new list<float>();
        }
        case STRING_VALUE:{
            stringValues = new list<string>();
        }
    }
}

TableColumnValues::TableColumnValues(list<int>* value, bool isFileReadInValueIn) : intValues(value){
    isFileReadInValue = isFileReadInValueIn;
    intValues = value;
    valueType = INT_VALUE;
}
TableColumnValues::TableColumnValues(list<double>* value, bool isFileReadInValueIn) : doubleValues(value){
    isFileReadInValue = isFileReadInValueIn;
    doubleValues = value;
    valueType = DOUBLE_VALUE;
}
TableColumnValues::TableColumnValues(list<float>* value, bool isFileReadInValueIn) : floatValues(value){
    isFileReadInValue = isFileReadInValueIn;
    floatValues = value;
    valueType = FLOAT_VALUE;
}
TableColumnValues::TableColumnValues(list<string>* value, bool isFileReadInValueIn) : stringValues(value){
    isFileReadInValue = isFileReadInValueIn;
    stringValues = value;
    valueType = STRING_VALUE;
}

                                     
void TableColumnValues::setValues(list<int>* value){
    intValues = value;
    valueType = INT_VALUE;
}
void TableColumnValues::setValues(list<float>* value){
    floatValues = value;
    valueType = FLOAT_VALUE;
}
void TableColumnValues::setValues(list<double>* value){
    doubleValues = value;
    valueType = DOUBLE_VALUE;
}
void TableColumnValues::setValues(list<string>* value){
    stringValues = value;
    valueType = STRING_VALUE;
}


void TableColumnValues::appendValues(list<int>& values){
    intValues->merge(values);
}
void TableColumnValues::appendValues(list<float>& values){
    floatValues->merge(values);
}
void TableColumnValues::appendValues(list<double>& values){
    doubleValues->merge(values);
}
void TableColumnValues::appendValues(list<string>& values){
    stringValues->merge(values);
}


void TableColumnValues::addValue(int& value){
    intValues->push_back(value);
}
void TableColumnValues::addValue(float& value){
    floatValues->push_back(value);
}
void TableColumnValues::addValue(double& value){
    doubleValues->push_back(value);
}
void TableColumnValues::addValue(string& value){
    stringValues->push_back(value);
}


bool TableColumnValues::isEmpty(){
    if(isFileReadInValue){
        switch (valueType){
            case INT_VALUE:{
                return intValues->empty();
            }
            case DOUBLE_VALUE:{
                return doubleValues->empty();
            }
            case FLOAT_VALUE:{
                return floatValues->empty();
            }
            case STRING_VALUE:{
                return stringValues->empty();
            }
            default:
                return false;
        }
    }
    else{
        return false;
    }
}
char TableColumnValues::getValueType(){
    return valueType;
}

string TableColumnValues::getColumnName(){
    return columnName;
}

int TableColumnValues::getRowCount(){
    switch (valueType){
        case INT_VALUE:{
            return (int)intValues->size();
        }
        case DOUBLE_VALUE:{
            return (int)doubleValues->size();
        }
        case FLOAT_VALUE:{
            return (int)floatValues->size();
        }
        case STRING_VALUE:{
            return (int)stringValues->size();
        }
        default:
            return 0;
    }
}

bool TableColumnValues::isReadInValue(){
    return isFileReadInValue;
}

list<int>* TableColumnValues::getIntValues(){
    return intValues;
}
list<float>* TableColumnValues::getFloatValues(){
    return floatValues;
}
list<double>* TableColumnValues::getDoubleValues(){
    return doubleValues;
}
list<string>* TableColumnValues::getStringValues(){
    return stringValues;
}

int TableColumnValues::popTopIntValue(){
    int value = intValues->front();
    if(isFileReadInValue)
        intValues->pop_front();
    return value;
}
float TableColumnValues::popTopFloatValue(){
    float value = floatValues->front();
    if(isFileReadInValue)
        floatValues->pop_front();
    return value;
}
double TableColumnValues::popTopDoubleValue(){
    float value = doubleValues->front();
    if(isFileReadInValue)
        doubleValues->pop_front();
    return value;
}
string TableColumnValues::popTopStringValue(){
    string value = stringValues->front();
    if(isFileReadInValue)
        stringValues->pop_front();
    return value;
}