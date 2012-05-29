//
//  EntityBindings.h
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_EntityBindings_h
#define flatland_EntityBindings_h

#include <v8.h>
using namespace v8;
class Entity;

Handle<Value> EntityBindings_WrapEntity(Entity* toWrap);
void EntityBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global);

#endif
