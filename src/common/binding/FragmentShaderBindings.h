//
//  FragmentShaderBindings.h
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_FragmentShaderBindings_h
#define flatland_FragmentShaderBindings_h

#include <v8.h>
using namespace v8;

class FragmentShader;

void FragmentShaderBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global);
Handle<Value> FragmentShaderBindings_WrapFragmentShader(FragmentShader* toWrap);


#endif
