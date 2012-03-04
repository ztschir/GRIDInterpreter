//
//  TableColumns.h
//  GRIDInterpreter
//
//  Created by Zachary Tschirhart on 2/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
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
    void addTableColumnInt(string columnName);
    void addTableColumnFloat(string columnName);
    void addTableColumnDouble(string columnName);
    void addTableColumnString(string columnName);
    
    void writeValuesToDB();
    TableColumnValues getColumnValues(string columnName);
    TableColumnValues getColumnValues(int index);
    int getNumberOfColumns();
    
private:
    map<string, TableColumnValues> columns;
    vector<TableColumnValues> columnIndex;
    string tableName;
    ConfigValues configValues;
};


#endif
