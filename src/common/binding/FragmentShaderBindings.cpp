//
//  FragmentShaderBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "FragmentShaderBindings.h"
#include "FragmentShader.h"
using namespace v8;

Handle<Value> fl_frag_SetSource(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    FragmentShader* frag = static_cast<FragmentShader*>(entVal->Value());
    Handle<Object> obj = args[0]->ToObject();
    String::Utf8Value stringVal(obj);
    string src(*stringVal);
    frag->SetSource(src);
    return handle_scope.Close(args.This());
}

Handle<Value> fl_frag_Compile(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    FragmentShader* frag = static_cast<FragmentShader*>(entVal->Value());
    frag->Compile();
    return handle_scope.Close(args.This());
}

Handle<FunctionTemplate> fl_frag_GetTemplate() {
    HandleScope handle_scope;
    Handle<FunctionTemplate> templ = FunctionTemplate::New();
    Handle<ObjectTemplate> instance_templ = templ->InstanceTemplate();
    instance_templ->Set("setSource", FunctionTemplate::New(fl_frag_SetSource));
    instance_templ->Set("compile", FunctionTemplate::New(fl_frag_Compile));
    instance_templ->SetInternalFieldCount(1);
    return handle_scope.Close(templ);
}

Handle<Value> FragmentShaderBindings_WrapFragmentShader(FragmentShader* toWrap) {
    static Persistent<FunctionTemplate> s_templ = Persistent<FunctionTemplate>::New(fl_frag_GetTemplate());
    HandleScope handle_scope;
    Locker locker;
    Local<Object> frag_inst = s_templ->InstanceTemplate()->NewInstance();
    frag_inst->SetInternalField(0, External::New(toWrap));
    Persistent<Object> ref = Persistent<Object>::New(frag_inst->ToObject());
    toWrap->SetWrappedObject(ref);
    return handle_scope.Close(frag_inst);
}

Handle<Value> fl_frag_ConstructorCall(const Arguments& args) {
    if(!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor like a function"));
    }
    HandleScope handle_scope;
    FragmentShader* frag = new FragmentShader();
	return frag->GetWrappedObject();
}

void FragmentShaderBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global) {
    HandleScope handle_scope;
    global->Set("FragmentShader", FunctionTemplate::New(fl_frag_ConstructorCall));
}

