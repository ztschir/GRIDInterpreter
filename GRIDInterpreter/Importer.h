//
//  Importer.h
//  GRIDInterpreter
//
//  The purpose of this class is to manipulate the directories 
//  and kick off the imports in each directory containing data.
//
//  Created by Zachary Tschirhart on 3/5/12.
//  Copyright (c) 2012 Radio Navigation Lab. All rights reserved.
//

#ifndef GRIDInterpreter_Importer_h
#define GRIDInterpreter_Importer_h

#include "TypeIdentifiers.h"
#include "ConfigValues.h"
#include "TableColumns.h"
#include "DataFileReader.h"

class Importer{
    
public:
    Importer(ConfigValues& configFileIn);
    void startImport();
    
private:
    int getdir (string dir, vector<string> &files);
    void importChannelData(int receiverID, string directoryPath);
    void importIonoData(int receiverID, string directoryPath);
    void importNavSolData(int receiverID, string directoryPath);
    void importSCIntData(int receiverID, string directoryPath);
    void importTXInfoData(int receiverID, string directoryPath);
    ConfigValues configFile;
};

#endif
