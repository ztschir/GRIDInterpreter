//
//  DataFileReader.cpp
//  GRIDInterpreter
//
//  Created by Zachary Tschirhart on 2/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "DataFileReader.h"  

using namespace std;

DataFileReader::DataFileReader(string fileName, char seperatorValueIn, TableColumns& tableColumnsIn) : seperatorValue(seperatorValueIn), tableColumns(tableColumnsIn)
{
    this->file = fopen(fileName.c_str(), "r");
    ConfigValues config;
    this->tableColumns = tableColumnsIn;
    this->seperatorValue = seperatorValueIn;
}

int DataFileReader::importFile(){
    int numberErrorRows = 0;
    
    if (file == NULL) perror ("Error opening file");
    else
    {
        while (!feof(file))
        {
            int size = tableColumns.getNumberOfColumns();
            
            for(int i = 0; i < size; i++){
                
                TableColumnValues column = tableColumns.getColumnValues(i);
                switch (column.getValueType()) {
                    case INT_VALUE:{
                        int intValue;
                        if(EOF == fscanf(file, " %d ", &intValue))
                        {
                            cout << "Malformed Int column" << endl;
                            numberErrorRows++;
                            int replace = 0;
                            column.addValue(replace);
                        }
                        else{
                            column.addValue(intValue);
                        }
                        
                        break;
                    }
                    case DOUBLE_VALUE:{
                        double doubleValue;
                        if(EOF == fscanf(file, " %lf ", &doubleValue))
                        {
                            cout << "Malformed Double column" << endl;
                            numberErrorRows++;
                            double replace = 0;
                            column.addValue(replace);
                        }
                        else{
                            column.addValue(doubleValue);
                        }
                        break;
                    }
                    case FLOAT_VALUE:{
                        float floatValue;
                        if(EOF == fscanf(file, " %f ", &floatValue))
                        {
                            cout << "Malformed Float column" << endl;
                            numberErrorRows++;
                            float replace = 0;
                            column.addValue(replace);
                        }
                        else{
                            column.addValue(floatValue);
                        }
                        break;
                    }
                        
                    default:{
                        string str;
                        fscanf(file, " %s ", &str);
                        column.addValue(str);
                        break;
                    }
                }
            }
        }
        fclose (file);
    }
    return numberErrorRows;
}


