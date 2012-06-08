//
//  ProgramArguments.cpp
//  flatland
//
//  Created by Ryan Evans on 6/8/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "ProgramArguments.h"

ProgramArguments::ProgramArguments(int argc, char** argv) : m_args() {
    this->ProcessArgs(argc, argv);
}

ProgramArguments::~ProgramArguments() {
    
}

StringVector& ProgramArguments::GetArguments() {
    return m_args;
}

void ProgramArguments::ProcessArgs(int argc, char** argv) {
    for(int i = 1; i < argc; i++) {
        m_args.push_back(string(argv[i]));
    }
}