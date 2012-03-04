//
//  DataFileReader.h
//  GRIDInterpreter
//
//  Created by Zachary Tschirhart on 2/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef GRIDInterpreter_DataFileReader_h
#define GRIDInterpreter_DataFileReader_h

#include "TypeIdentifiers.h"
#include "TableColumns.h"

using namespace std;

class DataFileReader
{
public:
    DataFileReader(string fileName, char seperatorValueIn, TableColumns& tableColumnsIn);
    int importFile();
private:
    FILE *file;
    TableColumns tableColumns;
    char seperatorValue;
};


#endif
