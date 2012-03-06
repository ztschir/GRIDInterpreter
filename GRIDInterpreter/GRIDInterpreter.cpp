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
#include "TableColumnValues.h"
#include "ConfigValues.h"
#include "DataFileReader.h"

using namespace std;

ConfigValues getConfigFileSettings();


int main(int argc, const char **argv)
{    

    ConfigValues configFile = getConfigFileSettings();
    // TODO: DirectoryImport
    //importChannelData(configFile);
    //importIonoData(configFile);
    //importNavSolData(configFile);
    //importSCIntData(configFile);
    //importTXInfoData(configFile);
}

ConfigValues getConfigFileSettings(){
    // key values in config file
    string configDBName = CONFIG_DB_NAME;
    string configDBHostname = CONFIG_DB_HOSTNAME;
    string configDBUsername = CONFIG_DB_USERNAME;
    string configDBPassword = CONFIG_DB_PASSWORD;
    
    ConfigValues configFile;
    configFile.isValid = true;
    
    ConfigFileReader cfg = ConfigFileReader(CONFIG_FILE_NAME);
    
	if(cfg.keyExists(configDBName)){
        configFile.dbNameValue = cfg.getValueOfKey(configDBName);
    }
    if(cfg.keyExists(configDBHostname)){
        configFile.dbHostnameValue = cfg.getValueOfKey(configDBHostname);
    }
    if(cfg.keyExists(configDBUsername)){
        configFile.dbUsernameValue = cfg.getValueOfKey(configDBUsername);
    }
    if(cfg.keyExists(configDBPassword)){
        configFile.dbPasswordValue = cfg.getValueOfKey(configDBPassword);
    }
    if(configFile.dbNameValue.empty() || 
       configFile.dbHostnameValue.empty() || 
       configFile.dbUsernameValue.empty() || 
       configFile.dbPasswordValue.empty()){
        cout << "Invalid .config file";
        configFile.isValid = false;
    }
    return configFile;
}


