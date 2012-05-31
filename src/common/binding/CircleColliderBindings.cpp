//
//  CircleColliderBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "CircleColliderBindings.h"
#include "CircleCollider.h"
#include "Entity.h"

using namespace v8;

Handle<Value> fl_cc_SetSize(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    CircleCollider* circleCollider = static_cast<CircleCollider*>(entVal->Value());
    GLfloat radius = args[0]->NumberValue();
    circleCollider->SetSize(radius);
    return Undefined();
}

Handle<Value> fl_cc_SetType(const Arguments& args) {
    HandleScope handle_scope;
    b2BodyType type = (b2BodyType)args[0]->Int32Value();
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    CircleCollider* circleCollider = static_cast<CircleCollider*>(entVal->Value());
    circleCollider->GetBox2DBody()->SetType(type);
    return Undefined();
}

Handle<Value> fl_cc_SetLinearVelocity(const Arguments& args) {
    HandleScope handle_scope;
    GLfloat vx = args[0]->NumberValue();
    GLfloat vy = args[1]->NumberValue();
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    CircleCollider* circleCollider = static_cast<CircleCollider*>(entVal->Value());
    circleCollider->GetBox2DBody()->SetLinearVelocity(b2Vec2(vx, vy));
    return Undefined();
}

Handle<Value> fl_cc_SetRestitution(const Arguments& args) {
    HandleScope handle_scope;
    GLfloat rest = args[0]->NumberValue();
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    CircleCollider* circleCollider = static_cast<CircleCollider*>(entVal->Value());
    circleCollider->SetRestitution(rest);
    return Undefined();
}

Handle<Value> fl_cc_GetParent(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    CircleCollider* circleCollider = static_cast<CircleCollider*>(entVal->Value());
    return handle_scope.Close(circleCollider->GetOwner()->GetWrappedObject());
}

Handle<FunctionTemplate> fl_cc_GetTemplate() {
    HandleScope handle_scope;
    Handle<FunctionTemplate> templ = FunctionTemplate::New();
    Handle<ObjectTemplate> instance_templ = templ->InstanceTemplate();
    instance_templ->Set("setSize", FunctionTemplate::New(fl_cc_SetSize));
    instance_templ->Set("setType", FunctionTemplate::New(fl_cc_SetType));
    instance_templ->Set("setLinearVelocity", FunctionTemplate::New(fl_cc_SetLinearVelocity));
    instance_templ->Set("setRestitution", FunctionTemplate::New(fl_cc_SetRestitution));
    instance_templ->Set("getParent", FunctionTemplate::New(fl_cc_GetParent));
    instance_templ->SetInternalFieldCount(1);
    return handle_scope.Close(templ);
}

Handle<Value> CircleColliderBindings_WrapCircleCollider(CircleCollider* toWrap) {
    static Persistent<FunctionTemplate> s_templ = Persistent<FunctionTemplate>::New(fl_cc_GetTemplate());
    HandleScope handle_scope;
    Local<Object> circleCollider_inst = s_templ->InstanceTemplate()->NewInstance();
    circleCollider_inst->SetInternalField(0, External::New(toWrap));
    Persistent<Object> ref = Persistent<Object>::New(circleCollider_inst->ToObject());
    toWrap->SetWrappedObject(ref);
    return handle_scope.Close(circleCollider_inst);
}

Handle<Value> fl_cc_ConstructorCall(const Arguments& args) {
    if(!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor like a function"));
    }
    HandleScope handle_scope;
    CircleCollider* circleCollider = new CircleCollider();
    return CircleColliderBindings_WrapCircleCollider(circleCollider);
}

void CircleColliderBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global) {
    HandleScope handle_scope;
    global->Set("CircleCollider", FunctionTemplate::New(fl_cc_ConstructorCall));
}
