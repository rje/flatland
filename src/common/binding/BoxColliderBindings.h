//
//  BoxColliderBindings.h
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_BoxColliderBindings_h
#define flatland_BoxColliderBindings_h

#include <v8.h>
using namespace v8;

class BoxCollider;

void BoxColliderBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global);
Handle<Value> BoxColliderBindings_WrapBoxCollider(BoxCollider* toWrap);


#endif
