//
//  ColliderBindings.h
//  flatland
//
//  Created by Ryan Evans on 5/31/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_ColliderBindings_h
#define flatland_ColliderBindings_h

#include <v8.h>
using namespace v8;

class Collider;

void ColliderBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global);
void ColliderBindings_AddMethodsToTemplate(v8::Handle<ObjectTemplate>& toAddTo);

#endif
