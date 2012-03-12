//
//  TableColumns.h
//  GRIDInterpreter
//
//  The TableColumns class holds all of the TableColumnValues for a single table
//  that you wish to access.
//
//  Created by Zachary Tschirhart on 2/14/12.
//  Copyright (c) 2012 Radio Navigation Lab. All rights reserved.
//

#ifndef GRIDInterpreter_TableColumns_h
#define GRIDInterpreter_TableColumns_h

#include "TableColumnValues.h"
#include "ConfigValues.h"
#include "TypeIdentifiers.h"


using namespace std;

class TableColumns{
    
public:
    TableColumns();
    TableColumns(string tableNameIn, ConfigValues& configValuesIn);
    void addTableColumnInt(string columnName, bool isFileReadInValueIn = true, int defaultValueIn = 0);
    void addTableColumnFloat(string columnName, bool isFileReadInValueIn = true, float defaultValueIn = 0);
    void addTableColumnDouble(string columnName, bool isFileReadInValueIn = true, double defaultValueIn = 0);
    void addTableColumnString(string columnName, bool isFileReadInValueIn = true, string defaultValueIn = "");
    
    void writeValuesToDB();
    TableColumnValues getColumnValues(string columnName);
    TableColumnValues getColumnValues(int index);
    bool areAnyColumnsEmpty();
    int getNumberOfColumns();
    
private:
    vector<TableColumnValues> columnIndex;
    string tableName;
    ConfigValues configValues;
};


#endif
