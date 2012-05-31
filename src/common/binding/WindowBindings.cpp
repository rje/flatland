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
    GLfloat width = args[0]->NumberValue();
    GLfloat height = args[1]->NumberValue();
    Window::GetWindow()->SetSize(width, height);
    return Undefined();
}

Handle<Value> fl_wb_SetViewportSize(const Arguments& args) {
    Locker locker;
    HandleScope handle_scope;
    GLfloat width = args[0]->NumberValue();
    GLfloat height = args[1]->NumberValue();
    Window::GetWindow()->SetViewportSize(width, height);
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

Handle<Value> fl_wb_GetSize(const Arguments& args) {
    Locker locker;
    HandleScope handle_scope;
    Handle<Object> toReturn = Object::New();
    toReturn->Set(String::New("width"), Number::New(Window::GetWindow()->GetWidth()));
    toReturn->Set(String::New("height"), Number::New(Window::GetWindow()->GetHeight()));
    return handle_scope.Close(toReturn);
}

Handle<Value> fl_wb_SetResizable(const Arguments& args) {
    Locker locker;
    HandleScope handle_scope;
    GLboolean val = args[0]->ToBoolean()->Value();
    Window::GetWindow()->SetResizeable(val);
    return Undefined();
}

void WindowBindings_BindToGlobal(Persistent<ObjectTemplate>& global) {
    Locker locker;
    HandleScope handle_scope;
    Handle<ObjectTemplate> window = ObjectTemplate::New();
    window->Set(String::New("setSize"), FunctionTemplate::New(fl_wb_SetSize));
    window->Set(String::New("getSize"), FunctionTemplate::New(fl_wb_GetSize));
    window->Set(String::New("setClearColor"), FunctionTemplate::New(fl_wb_SetClearColor));
    window->Set(String::New("setResizable"), FunctionTemplate::New(fl_wb_SetResizable));
    window->Set(String::New("setViewportSize"), FunctionTemplate::New(fl_wb_SetViewportSize));
    global->Set("window", window);
}