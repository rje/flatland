//
//  TransformBindings.h
//  flatland
//
//  Created by Ryan Evans on 5/25/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_TransformBindings_h
#define flatland_TransformBindings_h

#include <v8.h>
using namespace v8;

class Transform;

void TransformBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global);
Handle<Value> TransformBindings_WrapTransform(Transform* toWrap);


#endif
