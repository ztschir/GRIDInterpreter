//
//  TypeIdentifiers.h
//  GRIDInterpreter
//
//  Hold all of the includes in a single header file, and define value types.
//
//
//  Created by Zachary Tschirhart on 2/27/12.
//  Copyright (c) 2012 Radio Navigation Lab. All rights reserved.
//

#ifndef GRIDInterpreter_TypeIdentifiers_h
#define GRIDInterpreter_TypeIdentifiers_h

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>
#include <cppconn/metadata.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/statement.h>

#include <iterator>
#include <fstream>
#include <string>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <sstream>


const char INT_VALUE = 1;
const char FLOAT_VALUE = 2;
const char DOUBLE_VALUE = 3;
const char STRING_VALUE = 4;

#define CONFIG_FILE_NAME "gridinterpreter.config"
#define CONFIG_DB_NAME "db_name"
#define CONFIG_DB_HOSTNAME "db_hostname"
#define CONFIG_DB_USERNAME "db_username"
#define CONFIG_DB_PASSWORD "db_password"
#define TOP_LEVEL_DIRECOTRY "top_level_directory"

#define LENGTH_OF_GRIDRX_ID 3
#define PREFIX_FOR_DIRECTORIES "GRID"

#define CHANNEL_COLUMN_NAME "channel"
#define IONOSHPHERE_COLUMN_NAME "iono"
#define NAVIGATION_SOLUTION_COLUMN_NAME "navigationSolution"
#define SCINTILLATION_COLUMN_NAME "scintillation"
#define TRANSMITTER_INFO_COLUMN_NAME "transmitterInfo"

#define CHANNEL_FILENAME "channel.log"
#define IONOSHPHERE_FILENAME "iono.log"
#define NAVIGATION_SOLUTION_FILENAME "navsol.log"
#define SCINTILLATION_FILENAME "scint.log"
#define TRANSMITTER_INFO_FILENAME "txinfo.log"

#endif
