//
//  CameraBindings.h
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_CameraBindings_h
#define flatland_CameraBindings_h

#include <v8.h>
using namespace v8;

class Camera;

void CameraBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global);
Handle<Value> CameraBindings_WrapCamera(Camera* toWrap);

#endif
