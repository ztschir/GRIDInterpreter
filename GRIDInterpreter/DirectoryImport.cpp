//
//  DirectoryImport.cpp
//  GRIDInterpreter
//
//  Created by Zachary Tschirhart on 3/5/12.
//  Copyright (c) 2012 Radio Navigation Lab. All rights reserved.
//

#include "DirectoryImport.h"

#include <iostream>

DirectoryImport::DirectoryImport(ConfigValues& configFileIn){
    configFile = configFileIn;
    
    importChannelData();
    importIonoData();
    importNavSolData();
    importSCIntData();
    importTXInfoData();
}


void DirectoryImport::importChannelData(){
    TableColumns channel = TableColumns(CHANNEL_COLUMN_NAME, configFile);
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
    
    DataFileReader dataFile = DataFileReader(CHANNEL_FILENAME, ' ' , channel);
    dataFile.importFile();
    channel.writeValuesToDB();
}

void DirectoryImport::importIonoData(){
    TableColumns iono = TableColumns(IONOSHPHERE_COLUMN_NAME, configFile);
    iono.addTableColumnInt("offsetWeekNumber");
    iono.addTableColumnInt("offsetWholeSecondsOfWeek");
    iono.addTableColumnDouble("offsetFractionalSecond");
    iono.addTableColumnDouble("pseudorangeDerivedSTEC");
    iono.addTableColumnDouble("pseudorangeDerivedSTECDot");
    iono.addTableColumnInt("transmitterID");
    
    DataFileReader dataFile = DataFileReader(IONOSHPHERE_FILENAME, ' ' , iono);
    dataFile.importFile();
    iono.writeValuesToDB();
}

void DirectoryImport::importNavSolData(){
    TableColumns navSol = TableColumns(NAVIGATION_SOLUTION_COLUMN_NAME, configFile);
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
    
    DataFileReader dataFile = DataFileReader(NAVIGATION_SOLUTION_FILENAME, ' ' , navSol);
    dataFile.importFile();
    navSol.writeValuesToDB();
}

void DirectoryImport::importSCIntData(){
    TableColumns scInt = TableColumns(SCINTILLATION_COLUMN_NAME, configFile);
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
    
    DataFileReader dataFile = DataFileReader(SCINTILLATION_FILENAME, ' ' , scInt);
    dataFile.importFile();
    scInt.writeValuesToDB();
}

void DirectoryImport::importTXInfoData(){
    TableColumns txInfo = TableColumns(TRANSMITTER_INFO_COLUMN_NAME, configFile);
    txInfo.addTableColumnInt("offsetWeekNumber");
    txInfo.addTableColumnInt("offsetWholeSecondsOfWeek");
    txInfo.addTableColumnDouble("offsetFractionalSecond");
    txInfo.addTableColumnDouble("azmiuth");
    txInfo.addTableColumnDouble("elevation");
    txInfo.addTableColumnInt("healthStatus");
    txInfo.addTableColumnInt("transmitterSystemID");
    txInfo.addTableColumnInt("transmitterID");
    
    DataFileReader dataFile = DataFileReader(TRANSMITTER_INFO_FILENAME, ' ' , txInfo);
    dataFile.importFile();
    txInfo.writeValuesToDB();
}
