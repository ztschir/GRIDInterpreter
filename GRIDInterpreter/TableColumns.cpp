//
//  TableColumns.cpp
//  GRIDInterpreter
//
//  Created by Zachary Tschirhart on 2/14/12.
//  Copyright (c) 2012 Radio Navigation Lab. All rights reserved.
//

#include "TableColumns.h"
using namespace std;

TableColumns::TableColumns(){
}

TableColumns::TableColumns(string tableNameIn, ConfigValues& configValuesIn) : tableName(tableNameIn), configValues(configValuesIn){
    this->tableName = tableName;
    this->configValues = configValues;
}
void TableColumns::addTableColumnInt(string columnName, bool isFileReadInValueIn, int defaultValueIn){
    TableColumnValues column = TableColumnValues(columnName, INT_VALUE, isFileReadInValueIn);
    if(!isFileReadInValueIn)
        column.addValue(defaultValueIn);
    columnIndex.push_back(column);
}
void TableColumns::addTableColumnFloat(string columnName, bool isFileReadInValueIn, float defaultValueIn){
    TableColumnValues column = TableColumnValues(columnName, FLOAT_VALUE, isFileReadInValueIn);
    if(!isFileReadInValueIn)
        column.addValue(defaultValueIn);
    columnIndex.push_back(column);
}
void TableColumns::addTableColumnDouble(string columnName, bool isFileReadInValueIn, double defaultValueIn){
    TableColumnValues column = TableColumnValues(columnName, DOUBLE_VALUE, isFileReadInValueIn);
    if(!isFileReadInValueIn)
        column.addValue(defaultValueIn);
    columnIndex.push_back(column);
}
void TableColumns::addTableColumnString(string columnName, bool isFileReadInValueIn, string defaultValueIn){
    TableColumnValues column = TableColumnValues(columnName, STRING_VALUE, isFileReadInValueIn);
    if(!isFileReadInValueIn)
        column.addValue(defaultValueIn);
    columnIndex.push_back(column);
}

TableColumnValues TableColumns::getColumnValues(int index){
    return columnIndex[index];
}

int TableColumns::getNumberOfColumns(){
    return (int)columnIndex.size();
}

bool TableColumns::areAnyColumnsEmpty(){
    for(int i = 0; i < columnIndex.size(); i++){
        TableColumnValues column = columnIndex[i];    
        if(column.isEmpty()){
            return true;
        }
    }
    return false;
}

void TableColumns::writeValuesToDB(){
    
    sql::Driver *driver;
	stringstream sql;
    stringstream msg;
    
	try {
		// Create a connection
		driver = get_driver_instance();
		auto_ptr<sql::Connection> con(driver->connect(configValues.dbHostnameValue, configValues.dbUsernameValue, configValues.dbPasswordValue));
        
		
		auto_ptr<sql::Statement> stmt(con->createStatement());
		stmt->execute("USE " + configValues.dbNameValue);
        
        long num_columns = getNumberOfColumns();
        
        string columnNames;
        string columnValues;
        
        // Add all needed column names to query 
        for(int i = 0; i < num_columns; i++){
            columnNames.append(columnIndex[i].getColumnName());
            columnValues.append("?");
            if(num_columns > i + 1){
                columnNames.append(",");
                columnValues.append(",");
            }
        }
        
        // Create statment
        string statement = "INSERT INTO ";
        statement.append(tableName);
        statement.append("(");
        statement.append(columnNames);
        statement.append(") VALUES (");
        statement.append(columnValues);
        statement.append(")");
        
        // Create a prepared statement and add all values from the tableColumnValues object
        auto_ptr< sql::PreparedStatement > prep_stmt(con->prepareStatement(statement));
        while(!areAnyColumnsEmpty()){
            for(int j = 0; j < num_columns; j++){
                switch (columnIndex[j].getValueType()) {
                    case INT_VALUE:
                        prep_stmt->setInt(j + 1, columnIndex[j].popTopIntValue());
                        //cout << columnIndex[j].popTopIntValue() << "   ";
                        break;
                    case DOUBLE_VALUE:
                        prep_stmt->setDouble(j + 1, columnIndex[j].popTopDoubleValue());
                        //cout << columnIndex[j].popTopDoubleValue() << "   ";
                        break;
                    case FLOAT_VALUE:
                        prep_stmt->setDouble(j + 1, columnIndex[j].popTopFloatValue());
                        //cout << columnIndex[j].popTopFloatValue() << "   ";
                        break;
                    case STRING_VALUE:
                        prep_stmt->setString(j + 1, columnIndex[j].popTopStringValue());
                        //cout << columnIndex[j].popTopStringValue() << "   ";
                        break;
                    default:
                        break;
                }
            }
            prep_stmt->executeUpdate();
        }
        prep_stmt->execute();
        
        // Close the connection
        con->close();
        
    } catch (sql::SQLException &e) {
    /*
     The MySQL Connector/C++ throws three different exceptions:
     
     - sql::MethodNotImplementedException (derived from sql::SQLException)
     - sql::InvalidArgumentException (derived from sql::SQLException)
     - sql::SQLException (derived from runtime_error)
     */
        
    cout << "# ERR: DbcException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    
    if (e.getErrorCode() == 1047) {
        cout << "# ERR: Your server seems not to support PS at all because its MYSQL <4.1" << endl;
    }
    cout << "not ok 1 - examples/prepared_statement.cpp" << endl;
    
	} catch (runtime_error &e) {
        
		cout << endl;
		cout << "# ERR: runtime_error in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what() << endl;
		cout << "not ok 1 - examples/prepared_statement.cpp" << endl;
        
	}
    
}
