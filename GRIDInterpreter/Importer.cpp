//
//  Importer.cpp
//  GRIDInterpreter
//
//  Created by Zachary Tschirhart on 3/5/12.
//  Copyright (c) 2012 Radio Navigation Lab. All rights reserved.
//

#include "Importer.h"

Importer::Importer(ConfigValues& configFileIn){
    configFile = configFileIn;
    
}

void Importer::startImport(){
    
    vector<string> directoriesInTopDirectory;
    getdir(configFile.topLevelDirectory, directoriesInTopDirectory);
    
    long size = directoriesInTopDirectory.size();
    for(int i = 0; i < size; i++){
        string directoryName = directoriesInTopDirectory[i];
        // Extract the Receiver ID
        string receiverIDstr = directoryName.substr(directoryName.find(PREFIX_FOR_DIRECTORIES) + string(PREFIX_FOR_DIRECTORIES).size(), LENGTH_OF_GRIDRX_ID); 
        int receiverID;
        stringstream convert(receiverIDstr);
        
        // Build full directory path
        string fullDirectoryPath = configFile.topLevelDirectory + directoryName + "/";
        cout << "Importing directory: " << fullDirectoryPath << endl;
        
        if (!(convert >> receiverID)){
            cout << "Invalid receiver ID or naming convention for directory. Skipping import." << endl;
        }
        else{
            importChannelData(receiverID, fullDirectoryPath);
            importIonoData(receiverID, fullDirectoryPath);
            importNavSolData(receiverID, fullDirectoryPath);
            importSCIntData(receiverID, fullDirectoryPath);
            importTXInfoData(receiverID, fullDirectoryPath);
            
            // This won't remove the directory unless it's empty.
            // TODO: Not deleting even when empty
            if(configFile.deleteLogFileAfterImport)
                rmdir(directoryName.c_str());
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
    string fullPathToFile = directoryPath + CHANNEL_FILENAME;
    TableColumns channel = TableColumns(CHANNEL_COLUMN_NAME, configFile);
    channel.addTableColumnInt("receiver_id", false, receiverID);
    channel.addTableColumnInt("receiver_week_number");
    channel.addTableColumnDouble("receiver_seconds_of_week");
    channel.addTableColumnInt("offset_week_number");
    channel.addTableColumnInt("offset_whole_seconds_of_week");
    channel.addTableColumnDouble("offset_fractional_second");
    
    channel.addTableColumnDouble("apparent_doppler");
    channel.addTableColumnDouble("beat_carrier_phase");
    channel.addTableColumnDouble("pseudorange");
    channel.addTableColumnDouble("carrier_to_noise_ratio");
    channel.addTableColumnInt("is_valid_pseudorange_and_phase");
    channel.addTableColumnInt("is_anomaly_detected");
    channel.addTableColumnInt("channel_status_id");
    channel.addTableColumnInt("signal_type_id");
    channel.addTableColumnInt("transmitter_id");
    
    DataFileReader dataFile = DataFileReader(receiverID, fullPathToFile, channel);
    dataFile.importFile();
    channel.writeValuesToDB();
    
    if(configFile.deleteLogFileAfterImport)
        remove(fullPathToFile.c_str());
}

void Importer::importIonoData(int receiverID, string directoryPath){
    string fullPathToFile = directoryPath + IONOSHPHERE_FILENAME;
    TableColumns iono = TableColumns(IONOSHPHERE_COLUMN_NAME, configFile);
    iono.addTableColumnInt("receiver_id", false, receiverID);
    iono.addTableColumnInt("offset_week_number");
    iono.addTableColumnInt("offset_whole_seconds_of_week");
    iono.addTableColumnDouble("offset_fractional_second");
    
    iono.addTableColumnDouble("pseudorange_derived_stec");
    iono.addTableColumnDouble("pseudorange_derived_stec_dot");
    iono.addTableColumnInt("transmitter_id");
    
    DataFileReader dataFile = DataFileReader(receiverID, fullPathToFile, iono);
    dataFile.importFile();
    iono.writeValuesToDB();
    
    if(configFile.deleteLogFileAfterImport)
        remove(fullPathToFile.c_str());
}

void Importer::importNavSolData(int receiverID, string directoryPath){
    string fullPathToFile = directoryPath + NAVIGATION_SOLUTION_FILENAME;
    TableColumns navSol = TableColumns(NAVIGATION_SOLUTION_COLUMN_NAME, configFile);
    navSol.addTableColumnInt("receiver_id", false, receiverID);
    navSol.addTableColumnInt("offset_week_number");
    navSol.addTableColumnInt("offset_whole_seconds_of_week");
    navSol.addTableColumnDouble("offset_fractional_second");
    
    navSol.addTableColumnDouble("x_position");
    navSol.addTableColumnDouble("y_position");
    navSol.addTableColumnDouble("z_position");
    navSol.addTableColumnDouble("delta_receiver_clock_error");
    navSol.addTableColumnDouble("x_velocity");
    navSol.addTableColumnDouble("y_velocity");
    navSol.addTableColumnDouble("z_velocity");
    navSol.addTableColumnDouble("delta_receiver_clock_error_dot");
    navSol.addTableColumnInt("navigation_solver_id");
    
    DataFileReader dataFile = DataFileReader(receiverID, fullPathToFile, navSol);
    dataFile.importFile();
    navSol.writeValuesToDB();
    
    if(configFile.deleteLogFileAfterImport)
        remove(fullPathToFile.c_str());
}

void Importer::importSCIntData(int receiverID, string directoryPath){
    string fullPathToFile = directoryPath + SCINTILLATION_FILENAME;
    TableColumns scInt = TableColumns(SCINTILLATION_COLUMN_NAME, configFile);
    scInt.addTableColumnInt("receiver_id", false, receiverID);
    scInt.addTableColumnInt("offset_week_number");
    scInt.addTableColumnInt("offset_whole_seconds_of_week");
    scInt.addTableColumnDouble("offset_fractional_second");
    
    scInt.addTableColumnDouble("measurement_interval_length");
    scInt.addTableColumnDouble("s4_whole_interval");
    scInt.addTableColumnDouble("s4_first_half_interval");
    scInt.addTableColumnDouble("s4_second_half_interval");
    scInt.addTableColumnDouble("sigma_phi_whole_interval");
    scInt.addTableColumnDouble("sigma_phi_first_half_interval");
    scInt.addTableColumnDouble("sigma_phi_second_half_interval");
    scInt.addTableColumnDouble("tau0");
    scInt.addTableColumnDouble("scintillation_power_ratio");
    scInt.addTableColumnInt("reference_channel_indicator");
    scInt.addTableColumnInt("signal_type_id");
    scInt.addTableColumnInt("transmitter_id");
    
    DataFileReader dataFile = DataFileReader(receiverID, fullPathToFile, scInt);
    dataFile.importFile();
    scInt.writeValuesToDB();
    
    if(configFile.deleteLogFileAfterImport)
        remove(fullPathToFile.c_str());
}

void Importer::importTXInfoData(int receiverID, string directoryPath){
    string fullPathToFile = directoryPath + TRANSMITTER_INFO_FILENAME;
    TableColumns txInfo = TableColumns(TRANSMITTER_INFO_COLUMN_NAME, configFile);
    txInfo.addTableColumnInt("receiver_id", false, receiverID);
    txInfo.addTableColumnInt("offset_week_number");
    txInfo.addTableColumnInt("offset_whole_seconds_of_week");
    txInfo.addTableColumnDouble("offset_fractional_second");
    
    txInfo.addTableColumnDouble("azmiuth");
    txInfo.addTableColumnDouble("elevation");
    txInfo.addTableColumnInt("health_status_id");
    txInfo.addTableColumnInt("transmitter_system_id");
    txInfo.addTableColumnInt("transmitter_id");
    
    DataFileReader dataFile = DataFileReader(receiverID, fullPathToFile, txInfo);
    dataFile.importFile();
    txInfo.writeValuesToDB();
    
    if(configFile.deleteLogFileAfterImport)
        remove(fullPathToFile.c_str());
}
