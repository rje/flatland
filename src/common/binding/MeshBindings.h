//
//  MeshBindings.h
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_MeshBindings_h
#define flatland_MeshBindings_h

#include <v8.h>

class Mesh;

void MeshBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global);
v8::Handle<v8::Value> MeshBindings_WrapMesh(Mesh* toWrap);

#endif
