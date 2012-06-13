//
//  TextureBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 6/6/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "TextureBindings.h"
#include "Texture.h"
#include "Entity.h"

using namespace v8;

Handle<Value> fl_tex_InitWithFile(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Texture* texture = static_cast<Texture*>(entVal->Value());
    String::Utf8Value arg(args[0]);
    string path(*arg);
    texture->InitWithFile(path);
    return handle_scope.Close(args.This());
}

Handle<FunctionTemplate> fl_tex_GetTemplate() {
    HandleScope handle_scope;
    Handle<FunctionTemplate> templ = FunctionTemplate::New();
    Handle<ObjectTemplate> instance_templ = templ->InstanceTemplate();
    instance_templ->Set("initWithFile", FunctionTemplate::New(fl_tex_InitWithFile));
    instance_templ->SetInternalFieldCount(1);
    return handle_scope.Close(templ);
}

Handle<Value> TextureBindings_WrapTexture(Texture* toWrap) {
    static Persistent<FunctionTemplate> s_templ = Persistent<FunctionTemplate>::New(fl_tex_GetTemplate());
    HandleScope handle_scope;
    Local<Object> texture_inst = s_templ->InstanceTemplate()->NewInstance();
    texture_inst->SetInternalField(0, External::New(toWrap));
    Persistent<Object> ref = Persistent<Object>::New(texture_inst->ToObject());
    toWrap->SetWrappedObject(ref);
    return handle_scope.Close(texture_inst);
}

Handle<Value> fl_tex_ConstructorCall(const Arguments& args) {
    if(!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor like a function"));
    }
    HandleScope handle_scope;
    if(args.Length() == 1) {
        String::Utf8Value arg(args[0]);
        string path(*arg);
		Texture* t = Texture::TextureForFile(path);
		return t->GetWrappedObject();
    }
	else {
		return Undefined();
	}
}

Handle<Value> fl_tex_GetTexture(const Arguments& args) {
    HandleScope handle_scope;
    String::Utf8Value arg(args[0]);
    string path(*arg);
    Texture* t = Texture::TextureForFile(path);
    return handle_scope.Close(t->GetWrappedObject());
}

void TextureBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global) {
    HandleScope handle_scope;
    Handle<ObjectTemplate> tc = ObjectTemplate::New();
    tc->Set("getTexture", FunctionTemplate::New(fl_tex_GetTexture));
    global->Set("TextureCache", tc);
}
