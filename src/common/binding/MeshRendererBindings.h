//
//  MeshRendererBindings.h
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_MeshRendererBindings_h
#define flatland_MeshRendererBindings_h

#include <v8.h>
using namespace v8;

class MeshRenderer;

void MeshRendererBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global);
Handle<Value> MeshRendererBindings_WrapMeshRenderer(MeshRenderer* toWrap);

#endif
