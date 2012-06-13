//
//  VertexShaderBindings.h
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_VertexShaderBindings_h
#define flatland_VertexShaderBindings_h

#include <v8.h>
using namespace v8;

class VertexShader;

void VertexShaderBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global);
Handle<Value> VertexShaderBindings_WrapVertexShader(VertexShader* toWrap);

#endif
