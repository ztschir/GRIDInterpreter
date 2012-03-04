//
//  ConfigValues.h
//  GRIDInterpreter
//
//  Created by Zachary Tschirhart on 2/20/12.
//  Copyright (c) 2012 Radio Navigation Lab. All rights reserved.
//

#ifndef GRIDInterpreter_ConfigValues_h
#define GRIDInterpreter_ConfigValues_h

using namespace std;

class ConfigValues{
public:
    bool isValid;
    string dbNameValue;
    string dbHostnameValue;
    string dbUsernameValue;
    string dbPasswordValue;
};

#endif
