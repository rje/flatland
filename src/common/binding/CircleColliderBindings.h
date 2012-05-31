//
//  CircleColliderBindings.h
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_CircleColliderBindings_h
#define flatland_CircleColliderBindings_h

#include <v8.h>
using namespace v8;

class CircleCollider;

void CircleColliderBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global);
Handle<Value> CircleColliderBindings_WrapCircleCollider(CircleCollider* toWrap);

#endif
