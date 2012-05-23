//
//  WindowBindings.h
//  flatland
//
//  Created by Ryan Evans on 5/22/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_WindowBindings_h
#define flatland_WindowBindings_h

#include <v8.h>

void WindowBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global);

#endif
