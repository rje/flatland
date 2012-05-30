//
//  KeyboardBindings.h
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_KeyboardBindings_h
#define flatland_KeyboardBindings_h

#include <v8.h>

void KeyboardBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global);

#endif
