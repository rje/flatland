//
//  ProgramArguments.h
//  flatland
//
//  Created by Ryan Evans on 6/8/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_ProgramArguments_h
#define flatland_ProgramArguments_h

#include "flatland_common.h"

class ProgramArguments {
public:
    ProgramArguments(int argc, char** argv);
    virtual ~ProgramArguments();
    virtual StringVector& GetArguments();
    
private:
    void ProcessArgs(int argc, char** argv);
    StringVector m_args;
};


#endif
