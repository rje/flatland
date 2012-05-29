//
//  ScriptableBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 5/29/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "ScriptableBindings.h"
#include "Scriptable.h"

using namespace v8;

Handle<FunctionTemplate> fl_scr_GetTemplate() {
    HandleScope handle_scope;
    Handle<FunctionTemplate> templ = FunctionTemplate::New();
    Handle<ObjectTemplate> instance_templ = templ->InstanceTemplate();
    instance_templ->SetInternalFieldCount(1);
    return handle_scope.Close(templ);
}

Handle<Value> ScriptableBindings_WrapScriptable(Scriptable* toWrap) {
    static Persistent<FunctionTemplate> s_templ = Persistent<FunctionTemplate>::New(fl_scr_GetTemplate());
    HandleScope handle_scope;
    Local<Object> scriptable_inst = s_templ->InstanceTemplate()->NewInstance();
    scriptable_inst->SetInternalField(0, External::New(toWrap));
    Persistent<Object> ref = Persistent<Object>::New(scriptable_inst->ToObject());
    toWrap->SetWrappedObject(ref);
    return handle_scope.Close(scriptable_inst);
}

Handle<Value> fl_scr_ConstructorCall(const Arguments& args) {
    if(!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor like a function"));
    }
    HandleScope handle_scope;
    String::Utf8Value name(args[0]->ToString());
    Scriptable* scriptable = new Scriptable();
    return ScriptableBindings_WrapScriptable(scriptable);
}

void ScriptableBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global) {
    HandleScope handle_scope;
    global->Set("Scriptable", FunctionTemplate::New(fl_scr_ConstructorCall));
}
