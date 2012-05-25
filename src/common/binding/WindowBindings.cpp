//
//  WindowBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 5/22/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "WindowBindings.h"
#include "Window.h"

using namespace v8;

Handle<Value> fl_wb_SetSize(const Arguments& args) {
    Locker locker;
    HandleScope handle_scope;
    Handle<Value> widthVal = args[0];
    Handle<Value> heightVal = args[1];
    GLfloat width = (GLfloat)widthVal->ToNumber()->NumberValue();
    GLfloat height = (GLfloat)heightVal->ToNumber()->NumberValue();
    Window::GetWindow()->SetSize(width, height);
    return Undefined();
}

Handle<Value> fl_wb_SetClearColor(const Arguments& args) {
    Locker locker;
    HandleScope handle_scope;
    GLfloat r = (GLfloat)args[0]->ToNumber()->NumberValue();
    GLfloat g = (GLfloat)args[1]->ToNumber()->NumberValue();
    GLfloat b = (GLfloat)args[2]->ToNumber()->NumberValue();
    GLfloat a = (GLfloat)args[3]->ToNumber()->NumberValue();
    Window::GetWindow()->SetClearColor(r, g, b, a);
    return Undefined();
}


void WindowBindings_BindToGlobal(Persistent<ObjectTemplate>& global) {
    Locker locker;
    HandleScope handle_scope;
    Handle<ObjectTemplate> window = ObjectTemplate::New();
    window->Set(String::New("setSize"), FunctionTemplate::New(fl_wb_SetSize));
    window->Set(String::New("setClearColor"), FunctionTemplate::New(fl_wb_SetClearColor));
    global->Set("window", window);
}