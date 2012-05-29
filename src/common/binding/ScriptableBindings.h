//
//  ScriptableBindings.h
//  flatland
//
//  Created by Ryan Evans on 5/29/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_ScriptableBindings_h
#define flatland_ScriptableBindings_h

#include <v8.h>
using namespace v8;

class Scriptable;

void ScriptableBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global);
Handle<Value> ScriptableBindings_WrapScriptable(Scriptable* toWrap);

#endif
