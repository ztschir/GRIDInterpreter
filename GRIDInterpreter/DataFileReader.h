//
//  DataFileReader.h
//  GRIDInterpreter
//
//  The DataFileReader class is to parse the data files that are given
//  and to insert all the rows in the passed in TableColumns object.
//
//
//  Created by Zachary Tschirhart on 2/28/12.
//  Copyright (c) 2012 Radio Navigation Lab. All rights reserved.
//

#ifndef GRIDInterpreter_DataFileReader_h
#define GRIDInterpreter_DataFileReader_h

#include "TypeIdentifiers.h"
#include "TableColumns.h"

using namespace std;

class DataFileReader
{
public:
    DataFileReader(int receiverID, string fileName, TableColumns& tableColumnsIn);
    int importFile();
private:
    FILE *file;
    TableColumns tableColumns;
};


#endif
