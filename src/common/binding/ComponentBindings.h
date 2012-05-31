//
//  ComponentBindings.h
//  flatland
//
//  Created by Ryan Evans on 5/31/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_ComponentBindings_h
#define flatland_ComponentBindings_h

#include <v8.h>
using namespace v8;

class Component;

void ComponentBindings_AddMethodsToTemplate(v8::Handle<ObjectTemplate>& toAddTo);


#endif
