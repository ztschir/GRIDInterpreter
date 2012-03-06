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
    void importChannelData(ConfigValues& configFile);
    void importIonoData(ConfigValues& configFile);
    void importNavSolData(ConfigValues& configFile);
    void importSCIntData(ConfigValues& configFile);
    void importTXInfoData(ConfigValues& configFile);

private:
    
};

#endif
