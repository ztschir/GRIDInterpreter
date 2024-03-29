//
//  DataFileReader.cpp
//  GRIDInterpreter
//
//  Created by Zachary Tschirhart on 2/28/12.
//  Copyright (c) 2012 Radio Navigation Lab. All rights reserved.
//

#include "DataFileReader.h"  



using namespace std;

DataFileReader::DataFileReader(int receiverID, string fileName, TableColumns& tableColumnsIn) 
    : tableColumns(tableColumnsIn)
{
    this->file = fopen(fileName.c_str(), "r");
    ConfigValues config;
    this->tableColumns = tableColumnsIn;
    cout << "Reading in: " << fileName << endl;
}

int DataFileReader::importFile(){
    int numberErrorRows = 0;
    
    if (file == NULL) perror ("Error opening file");
    else
    {
        int size = tableColumns.getNumberOfColumns();
        int row = 1;
        while (!feof(file))
        {
            for(int i = 0; i < size; i++){
                TableColumnValues column = tableColumns.getColumnValues(i);
                if(column.isReadInValue()){
                    switch (column.getValueType()) {
                        case INT_VALUE:{
                            int intValue;
                            if(EOF == fscanf(file, " %d ", &intValue))
                            {
                                cout << "Malformed Int column: " << i << " row: " << row << " , replacing with zero" << endl;
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
                                cout << "Malformed Double column: " << i << " row: " << row << " , replacing with zero" << endl;
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
                                cout << "Malformed Float column: " << i << " row: " << row << " , replacing with zero" << endl;
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
                            char str;
                            fscanf(file, " %s ", &str);
                            string strval = string(&str);
                            column.addValue(strval);
                            break;
                        }
                    }
                }
            }
            row++;
        }
        fclose(file);
    }
    return numberErrorRows;
}


