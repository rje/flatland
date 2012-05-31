//
//  BoxColliderBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "BoxColliderBindings.h"
#include "ColliderBindings.h"
#include "BoxCollider.h"
#include "Entity.h"

using namespace v8;

Handle<Value> fl_bc_SetSize(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    BoxCollider* boxCollider = static_cast<BoxCollider*>(entVal->Value());
    GLfloat hw = args[0]->NumberValue();
    GLfloat hh = args[1]->NumberValue();
    boxCollider->SetSize(hw, hh);
    return Undefined();
}

Handle<FunctionTemplate> fl_bc_GetTemplate() {
    HandleScope handle_scope;
    Handle<FunctionTemplate> templ = FunctionTemplate::New();
    Handle<ObjectTemplate> instance_templ = templ->InstanceTemplate();
    instance_templ->Set("setSize", FunctionTemplate::New(fl_bc_SetSize));
    ColliderBindings_AddMethodsToTemplate(instance_templ);
    instance_templ->SetInternalFieldCount(1);
    return handle_scope.Close(templ);
}

Handle<Value> BoxColliderBindings_WrapBoxCollider(BoxCollider* toWrap) {
    static Persistent<FunctionTemplate> s_templ = Persistent<FunctionTemplate>::New(fl_bc_GetTemplate());
    HandleScope handle_scope;
    Local<Object> boxCollider_inst = s_templ->InstanceTemplate()->NewInstance();
    boxCollider_inst->SetInternalField(0, External::New(toWrap));
    Persistent<Object> ref = Persistent<Object>::New(boxCollider_inst->ToObject());
    toWrap->SetWrappedObject(ref);
    return handle_scope.Close(boxCollider_inst);
}

Handle<Value> fl_bc_ConstructorCall(const Arguments& args) {
    if(!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor like a function"));
    }
    HandleScope handle_scope;
    BoxCollider* boxCollider = new BoxCollider();
    if(args.Length() == 2) {
        GLfloat w = args[0]->NumberValue();
        GLfloat h = args[1]->NumberValue();
        boxCollider->SetSize(w, h);
    }
    return BoxColliderBindings_WrapBoxCollider(boxCollider);
}

void BoxColliderBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global) {
    HandleScope handle_scope;
    global->Set("BoxCollider", FunctionTemplate::New(fl_bc_ConstructorCall));
}
