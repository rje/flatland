//
//  ShaderBindings.h
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_ShaderBindings_h
#define flatland_ShaderBindings_h

#include <v8.h>
using namespace v8;

class Shader;

void ShaderBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global);
Handle<Value> ShaderBindings_WrapShader(Shader* toWrap);


#endif
