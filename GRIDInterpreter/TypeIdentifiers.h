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

#include "lib/cppconn/driver.h"
#include "lib/cppconn/exception.h"
#include "lib/cppconn/warning.h"
#include "lib/cppconn/metadata.h"
#include "lib/cppconn/prepared_statement.h"
#include "lib/cppconn/resultset.h"
#include "lib/cppconn/resultset_metadata.h"
#include "lib/cppconn/statement.h"
#include "mysql_driver.h"

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#include <iterator>
#include <fstream>
#include <string>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <cstdlib>

const char INT_VALUE = 1;
const char FLOAT_VALUE = 2;
const char DOUBLE_VALUE = 3;
const char STRING_VALUE = 4;

//Config file definitions
#define CONFIG_FILE_NAME "gridinterpreter.config"
#define CONFIG_DB_NAME "db_name"
#define CONFIG_DB_HOSTNAME "db_hostname"
#define CONFIG_DB_USERNAME "db_username"
#define CONFIG_DB_PASSWORD "db_password"
#define TOP_LEVEL_DIRECOTRY "top_level_directory"
#define DELETE_LOG_FILES_AFTER_IMPORT "delete_log_file_after_import"

// TODO: Find the length a different way, possibly have prefix stated in the config file.
#define LENGTH_OF_GRIDRX_ID 3
#define PREFIX_FOR_DIRECTORIES "GRID"

#define CHANNEL_COLUMN_NAME "channel_imports"
#define IONOSHPHERE_COLUMN_NAME "ionosphere_imports"
#define NAVIGATION_SOLUTION_COLUMN_NAME "navigation_imports"
#define SCINTILLATION_COLUMN_NAME "scintillation_imports"
#define TRANSMITTER_INFO_COLUMN_NAME "transmitter_imports"

#define CHANNEL_FILENAME "channel.log"
#define IONOSHPHERE_FILENAME "iono.log"
#define NAVIGATION_SOLUTION_FILENAME "navsol.log"
#define SCINTILLATION_FILENAME "scint.log"
#define TRANSMITTER_INFO_FILENAME "txinfo.log"

#endif
