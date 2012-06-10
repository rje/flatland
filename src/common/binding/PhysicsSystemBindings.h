//
//  PhysicsSystemBindings.h
//  flatland
//
//  Created by Ryan Evans on 6/9/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_PhysicsSystemBindings_h
#define flatland_PhysicsSystemBindings_h

#include <v8.h>

using namespace v8;

void PhysicsSystemBindings_BindToGlobal(Persistent<ObjectTemplate>& global);

#endif
