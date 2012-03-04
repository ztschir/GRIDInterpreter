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

#endif
