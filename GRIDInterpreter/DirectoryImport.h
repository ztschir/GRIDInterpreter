//
//  DirectoryImport.h
//  GRIDInterpreter
//
//  Created by Zachary Tschirhart on 3/5/12.
//  Copyright (c) 2012 Radio Navigation Lab. All rights reserved.
//

#ifndef GRIDInterpreter_DirectoryImport_h
#define GRIDInterpreter_DirectoryImport_h

#include "TypeIdentifiers.h"
#include "ConfigValues.h"
#include "TableColumns.h"
#include "DataFileReader.h"

class DirectoryImport{
    
public:
    DirectoryImport(ConfigValues& configFileIn);

private:
    void importChannelData();
    void importIonoData();
    void importNavSolData();
    void importSCIntData();
    void importTXInfoData();
    
    ConfigValues configFile;
};

#endif
