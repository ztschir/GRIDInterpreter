//
//  Importer.cpp
//  GRIDInterpreter
//
//  Created by Zachary Tschirhart on 3/5/12.
//  Copyright (c) 2012 Radio Navigation Lab. All rights reserved.
//

#include "Importer.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

Importer::Importer(ConfigValues& configFileIn){
    configFile = configFileIn;
    
}

void Importer::startImport(){
    
    vector<string> directoriesInTopDirectory;
    getdir(configFile.topLevelDirectory, directoriesInTopDirectory);
    
    for(string directoryName: directoriesInTopDirectory){
        // Extract the Receiver ID
        string receiverIDstr = directoryName.substr(directoryName.find(PREFIX_FOR_DIRECTORIES) + string(PREFIX_FOR_DIRECTORIES).size(), LENGTH_OF_GRIDRX_ID); 
        int receiverID;
        stringstream convert(receiverIDstr);
        
        // Build full directory path
        string fullDirectoryPath = configFile.topLevelDirectory + directoryName + "/";
        cout << "Importing directory: " << fullDirectoryPath << endl;
        
        if (!(convert >> receiverID)){
            cout << "Invalid receiver ID or naming convention. Skipping import." << endl;
        }
        else{
            importChannelData(receiverID, fullDirectoryPath);
            importIonoData(receiverID, fullDirectoryPath);
            importNavSolData(receiverID, fullDirectoryPath);
            importSCIntData(receiverID, fullDirectoryPath);
            importTXInfoData(receiverID, fullDirectoryPath);
        }
    }
}

int Importer::getdir(string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error opening " << dir << endl;
        return 1;
    }
    
    while ((dirp = readdir(dp)) != NULL) {
        // DT_DIR determines if the file is a directory, this only works on *nix based systems
        if(dirp->d_type == DT_DIR){
            string directoryName = string(dirp->d_name);
            if(directoryName.find(PREFIX_FOR_DIRECTORIES) != string::npos)
                files.push_back(directoryName);
        }
    }
    closedir(dp);
    return 0;
}


void Importer::importChannelData(int receiverID, string directoryPath){
    TableColumns channel = TableColumns(CHANNEL_COLUMN_NAME, configFile);
    channel.addTableColumnInt("receiverID", false, receiverID);
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
    
    DataFileReader dataFile = DataFileReader(receiverID, directoryPath + CHANNEL_FILENAME, channel);
    dataFile.importFile();
    channel.writeValuesToDB();
}

void Importer::importIonoData(int receiverID, string directoryPath){
    TableColumns iono = TableColumns(IONOSHPHERE_COLUMN_NAME, configFile);
    iono.addTableColumnInt("receiverID", false, receiverID);
    iono.addTableColumnInt("offsetWeekNumber");
    iono.addTableColumnInt("offsetWholeSecondsOfWeek");
    iono.addTableColumnDouble("offsetFractionalSecond");
    iono.addTableColumnDouble("pseudorangeDerivedSTEC");
    iono.addTableColumnDouble("pseudorangeDerivedSTECDot");
    iono.addTableColumnInt("transmitterID");
    
    DataFileReader dataFile = DataFileReader(receiverID, directoryPath + IONOSHPHERE_FILENAME, iono);
    dataFile.importFile();
    iono.writeValuesToDB();
}

void Importer::importNavSolData(int receiverID, string directoryPath){
    TableColumns navSol = TableColumns(NAVIGATION_SOLUTION_COLUMN_NAME, configFile);
    navSol.addTableColumnInt("receiverID", false, receiverID);
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
    
    DataFileReader dataFile = DataFileReader(receiverID, directoryPath + NAVIGATION_SOLUTION_FILENAME, navSol);
    dataFile.importFile();
    navSol.writeValuesToDB();
}

void Importer::importSCIntData(int receiverID, string directoryPath){
    TableColumns scInt = TableColumns(SCINTILLATION_COLUMN_NAME, configFile);
    scInt.addTableColumnInt("receiverID", false, receiverID);
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
    
    DataFileReader dataFile = DataFileReader(receiverID, directoryPath + SCINTILLATION_FILENAME, scInt);
    dataFile.importFile();
    scInt.writeValuesToDB();
}

void Importer::importTXInfoData(int receiverID, string directoryPath){
    TableColumns txInfo = TableColumns(TRANSMITTER_INFO_COLUMN_NAME, configFile);
    txInfo.addTableColumnInt("receiverID", false, receiverID);
    txInfo.addTableColumnInt("offsetWeekNumber");
    txInfo.addTableColumnInt("offsetWholeSecondsOfWeek");
    txInfo.addTableColumnDouble("offsetFractionalSecond");
    txInfo.addTableColumnDouble("azmiuth");
    txInfo.addTableColumnDouble("elevation");
    txInfo.addTableColumnInt("healthStatus");
    txInfo.addTableColumnInt("transmitterSystemID");
    txInfo.addTableColumnInt("transmitterID");
    
    DataFileReader dataFile = DataFileReader(receiverID, directoryPath + TRANSMITTER_INFO_FILENAME, txInfo);
    dataFile.importFile();
    txInfo.writeValuesToDB();
}
