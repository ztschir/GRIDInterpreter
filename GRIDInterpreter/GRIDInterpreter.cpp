//
//  GRIDInterpreter.cpp
//  GRIDInterpreter
//
//  Main program
//
//  Created by Zachary Tschirhart on 2/19/12.
//  Copyright (c) 2012 Radio Navigation Lab. All rights reserved.
//

#include <iostream>

#include "TableColumns.h"
#include "ConfigFileReader.h"
#include "ConfigValues.h"
#include "DataFileReader.h"
#include "Importer.h"

using namespace std;

ConfigValues getConfigFileSettings();

int main(int argc, const char **argv)
{    
    ConfigValues configFile = getConfigFileSettings();
    Importer importer = Importer(configFile);
    importer.startImport();
}

ConfigValues getConfigFileSettings(){
    
    ConfigValues configFile;
    
    ConfigFileReader cfg = ConfigFileReader(CONFIG_FILE_NAME);
	if(cfg.keyExists(CONFIG_DB_NAME)){
        configFile.dbNameValue = cfg.getValueOfKey(CONFIG_DB_NAME);
    }
    if(cfg.keyExists(CONFIG_DB_HOSTNAME)){
        configFile.dbHostnameValue = cfg.getValueOfKey(CONFIG_DB_HOSTNAME);
    }
    if(cfg.keyExists(CONFIG_DB_USERNAME)){
        configFile.dbUsernameValue = cfg.getValueOfKey(CONFIG_DB_USERNAME);
    }
    if(cfg.keyExists(CONFIG_DB_PASSWORD)){
        configFile.dbPasswordValue = cfg.getValueOfKey(CONFIG_DB_PASSWORD);
    }
    if(cfg.keyExists(TOP_LEVEL_DIRECOTRY)){
        configFile.topLevelDirectory = cfg.getValueOfKey(TOP_LEVEL_DIRECOTRY);
    }
    if(cfg.keyExists(DELETE_LOG_FILES_AFTER_IMPORT)){
        string deleteValStr = cfg.getValueOfKey(DELETE_LOG_FILES_AFTER_IMPORT);
        int deleteVal;
        
        stringstream convert(deleteValStr);
        if (!(convert >> deleteVal)){
            cout << "Invalid value for delete files after import option" << endl;
            exit(1);
        }
        configFile.deleteLogFileAfterImport = deleteVal;
    }
    if(configFile.dbNameValue.empty() || 
       configFile.dbHostnameValue.empty() || 
       configFile.dbUsernameValue.empty() || 
       configFile.dbPasswordValue.empty() ||
       configFile.topLevelDirectory.empty()){
        cout << "Invalid .config file";
        exit(1);
    }
    return configFile;
}


