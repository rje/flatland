//
//  ShaderBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "ShaderBindings.h"
#include "Shader.h"
using namespace v8;

Handle<Value> fl_shad_AddFragmentShader(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Shader* shader = static_cast<Shader*>(entVal->Value());
    Handle<Object> obj = args[0]->ToObject();
    Local<Value> intVal = obj->GetInternalField(0);
    Local<External> extVal = Local<External>::Cast(intVal);
    FragmentShader* toAdd = static_cast<FragmentShader*>(extVal->Value());
    shader->AddFragmentShader(toAdd);
    return handle_scope.Close(args.This());
}

Handle<Value> fl_shad_AddVertexShader(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Shader* shader = static_cast<Shader*>(entVal->Value());
    Handle<Object> obj = args[0]->ToObject();
    Local<Value> intVal = obj->GetInternalField(0);
    Local<External> extVal = Local<External>::Cast(intVal);
    VertexShader* toAdd = static_cast<VertexShader*>(extVal->Value());
    shader->AddVertexShader(toAdd);
    return handle_scope.Close(args.This());
}

Handle<Value> fl_shad_LinkShader(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Shader* shader = static_cast<Shader*>(entVal->Value());
    shader->LinkShader();
    return handle_scope.Close(args.This());
}

Handle<FunctionTemplate> fl_shad_GetTemplate() {
    HandleScope handle_scope;
    Handle<FunctionTemplate> templ = FunctionTemplate::New();
    Handle<ObjectTemplate> instance_templ = templ->InstanceTemplate();
    instance_templ->Set("addFragmentShader", FunctionTemplate::New(fl_shad_AddFragmentShader));
    instance_templ->Set("addVertexShader", FunctionTemplate::New(fl_shad_AddVertexShader));
    instance_templ->Set("linkShader", FunctionTemplate::New(fl_shad_LinkShader));
    instance_templ->SetInternalFieldCount(1);
    return handle_scope.Close(templ);
}

Handle<Value> ShaderBindings_WrapShader(Shader* toWrap) {
    static Persistent<FunctionTemplate> s_templ = Persistent<FunctionTemplate>::New(fl_shad_GetTemplate());
    HandleScope handle_scope;
    Locker locker;
    Local<Object> texture_inst = s_templ->InstanceTemplate()->NewInstance();
    texture_inst->SetInternalField(0, External::New(toWrap));
    Persistent<Object> ref = Persistent<Object>::New(texture_inst->ToObject());
    toWrap->SetWrappedObject(ref);
    return handle_scope.Close(texture_inst);
}

Handle<Value> fl_sha_ConstructorCall(const Arguments& args) {
    if(!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor like a function"));
    }
    HandleScope handle_scope;
    Shader* s = new Shader();
	return s->GetWrappedObject();
}

Handle<Value> fl_sha_GetDefaultShader(const Arguments& args) {
    HandleScope handle_scope;
    return handle_scope.Close(Shader::defaultShader->GetWrappedObject());
}

Handle<Value> fl_sha_GetDefaultNoTextureShader(const Arguments& args) {
    HandleScope handle_scope;
    return handle_scope.Close(Shader::defaultShader->GetWrappedObject());
}

void ShaderBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global) {
    HandleScope handle_scope;
    Handle<FunctionTemplate> shader = FunctionTemplate::New(fl_sha_ConstructorCall);
    shader->Set("getDefaultShader", FunctionTemplate::New(fl_sha_GetDefaultShader));
    shader->Set("getDefaultNoTextureShader", FunctionTemplate::New(fl_sha_GetDefaultNoTextureShader));
    global->Set("Shader", shader);
}
