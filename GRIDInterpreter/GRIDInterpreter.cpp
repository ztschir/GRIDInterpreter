//
//  GRIDInterpreter.cpp
//  GRIDInterpreter
//
//  Created by Zachary Tschirhart on 2/19/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "TableColumns.h"
#include "ConfigFileReader.h"
#include "TableColumnValues.h"
#include "ConfigValues.h"
#include "DataFileReader.h"

using namespace std;

ConfigValues getConfigFileSettings();
void importChannelData(ConfigValues& configFile);
void importIonoData(ConfigValues& configFile);
void importNavSolData(ConfigValues& configFile);
void importSCIntData(ConfigValues& configFile);
void importTXInfoData(ConfigValues& configFile);


int main(int argc, const char **argv)
{    
    ConfigValues configFile = getConfigFileSettings();
    
    //importChannelData(configFile);
    importIonoData(configFile);
    importNavSolData(configFile);
    importSCIntData(configFile);
    importTXInfoData(configFile);
}

void importChannelData(ConfigValues& configFile){
    TableColumns channel = TableColumns("channel", configFile);
    channel.addTableColumnInt("receiverWeekNumber");
    channel.addTableColumnDouble("receiverSecondsOfWeek");
    channel.addTableColumnInt("offsetWeekNumber");
    channel.addTableColumnInt("offsetWholeSecondsOfWeek");
    channel.addTableColumnDouble("offsetFractionalSecond");
    channel.addTableColumnDouble("apparentDoppler");
    channel.addTableColumnDouble("beatCarrierPhase");
    channel.addTableColumnDouble("pseudorange");
    channel.addTableColumnDouble("carrierToNoiseRatio");
    channel.addTableColumnInt("isValidPseudorangeAndPhase");
    channel.addTableColumnInt("isAnomalyDetected");
    channel.addTableColumnInt("channelStatusID");
    channel.addTableColumnInt("signalTypeID");
    channel.addTableColumnInt("transmitterID");
    
    DataFileReader dataFile = DataFileReader("channel.log", ' ' , channel);
    dataFile.importFile();
    channel.writeValuesToDB();
}

void importIonoData(ConfigValues& configFile){
    TableColumns iono = TableColumns("ionosphere", configFile);
    iono.addTableColumnInt("offsetWeekNumber");
    iono.addTableColumnInt("offsetWholeSecondsOfWeek");
    iono.addTableColumnDouble("offsetFractionalSecond");
    iono.addTableColumnDouble("pseudorangeDerivedSTEC");
    iono.addTableColumnDouble("pseudorangeDerivedSTECDot");
    iono.addTableColumnInt("transmitterID");
    
    DataFileReader dataFile = DataFileReader("iono.log", ' ' , iono);
    dataFile.importFile();
    iono.writeValuesToDB();
}

void importNavSolData(ConfigValues& configFile){
    TableColumns navSol = TableColumns("navigationSolution", configFile);
    navSol.addTableColumnInt("offsetWeekNumber");
    navSol.addTableColumnInt("offsetWholeSecondsOfWeek");
    navSol.addTableColumnDouble("offsetFractionalSecond");
    
    navSol.addTableColumnDouble("xPosition");
    navSol.addTableColumnDouble("yPosition");
    navSol.addTableColumnDouble("zPosition");
    navSol.addTableColumnDouble("deltaReceiverClockError");
    navSol.addTableColumnDouble("xVelocity");
    navSol.addTableColumnDouble("yVelocity");
    navSol.addTableColumnDouble("zVelocity");
    navSol.addTableColumnDouble("deltaReceiverClockErrorDot");
    navSol.addTableColumnInt("navigationSolverID");
    
    DataFileReader dataFile = DataFileReader("navsol.log", ' ' , navSol);
    dataFile.importFile();
    navSol.writeValuesToDB();
}

void importSCIntData(ConfigValues& configFile){
    TableColumns scInt = TableColumns("scintillation", configFile);
    scInt.addTableColumnInt("offsetWeekNumber");
    scInt.addTableColumnInt("offsetWholeSecondsOfWeek");
    scInt.addTableColumnDouble("offsetFractionalSecond");
    
    scInt.addTableColumnDouble("measurementIntervalLength");
    scInt.addTableColumnDouble("s4WholeInterval");
    scInt.addTableColumnDouble("s4FirstHalfInterval");
    scInt.addTableColumnDouble("s4SecondHalfInterval");
    scInt.addTableColumnDouble("sigmaPhiWholeInterval");
    scInt.addTableColumnDouble("sigmaPhiFirstHalfInterval");
    scInt.addTableColumnDouble("sigmaPhiSecondHalfInterval");
    scInt.addTableColumnDouble("tau0");
    scInt.addTableColumnDouble("scintillationPowerRatio");
    scInt.addTableColumnInt("referenceChannelIndicator");
    scInt.addTableColumnInt("signalTypeID");
    scInt.addTableColumnInt("transmitterID");
    
    DataFileReader dataFile = DataFileReader("scint.log", ' ' , scInt);
    dataFile.importFile();
    scInt.writeValuesToDB();
}

void importTXInfoData(ConfigValues& configFile){
    TableColumns txInfo = TableColumns("transmitterInfo", configFile);
    txInfo.addTableColumnInt("offsetWeekNumber");
    txInfo.addTableColumnInt("offsetWholeSecondsOfWeek");
    txInfo.addTableColumnDouble("offsetFractionalSecond");
    txInfo.addTableColumnDouble("azmiuth");
    txInfo.addTableColumnDouble("elevation");
    txInfo.addTableColumnInt("healthStatus");
    txInfo.addTableColumnInt("transmitterSystemID");
    txInfo.addTableColumnInt("transmitterID");
    
    DataFileReader dataFile = DataFileReader("txinfo.log", ' ' , txInfo);
    dataFile.importFile();
    txInfo.writeValuesToDB();
}


ConfigValues getConfigFileSettings(){
    // key values in config file
    string configDBName = "db_name";
    string configDBHostname = "db_hostname";
    string configDBUsername = "db_username";
    string configDBPassword = "db_password";
    
    ConfigValues configFile;
    configFile.isValid = true;
    
    ConfigFileReader cfg = ConfigFileReader("gridinterpreter.config");
    
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


