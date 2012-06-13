//
//  VertexShaderBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "VertexShaderBindings.h"
#include "VertexShader.h"
using namespace v8;

Handle<Value> fl_vert_SetSource(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    VertexShader* vert = static_cast<VertexShader*>(entVal->Value());
    Handle<Object> obj = args[0]->ToObject();
    String::Utf8Value stringVal(obj);
    string src(*stringVal);
    vert->SetSource(src);
    return handle_scope.Close(args.This());
}

Handle<Value> fl_vert_Compile(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    VertexShader* vert = static_cast<VertexShader*>(entVal->Value());
    vert->Compile();
    return handle_scope.Close(args.This());
}

Handle<FunctionTemplate> fl_vert_GetTemplate() {
    HandleScope handle_scope;
    Handle<FunctionTemplate> templ = FunctionTemplate::New();
    Handle<ObjectTemplate> instance_templ = templ->InstanceTemplate();
    instance_templ->Set("setSource", FunctionTemplate::New(fl_vert_SetSource));
    instance_templ->Set("compile", FunctionTemplate::New(fl_vert_Compile));
    instance_templ->SetInternalFieldCount(1);
    return handle_scope.Close(templ);
}

Handle<Value> VertexShaderBindings_WrapVertexShader(VertexShader* toWrap) {
    static Persistent<FunctionTemplate> s_templ = Persistent<FunctionTemplate>::New(fl_vert_GetTemplate());
    HandleScope handle_scope;
    Locker locker;
    Local<Object> vert_inst = s_templ->InstanceTemplate()->NewInstance();
    vert_inst->SetInternalField(0, External::New(toWrap));
    Persistent<Object> ref = Persistent<Object>::New(vert_inst->ToObject());
    toWrap->SetWrappedObject(ref);
    return handle_scope.Close(vert_inst);
}

Handle<Value> fl_vert_ConstructorCall(const Arguments& args) {
    if(!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor like a function"));
    }
    HandleScope handle_scope;
    VertexShader* vert = new VertexShader();
	return vert->GetWrappedObject();
}

void VertexShaderBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global) {
    HandleScope handle_scope;
    global->Set("VertexShader", FunctionTemplate::New(fl_vert_ConstructorCall));
}