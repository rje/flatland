//
//  ColliderBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 5/31/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "ColliderBindings.h"
#include "Collider.h"
#include "ComponentBindings.h"

using namespace v8;

Handle<Value> fl_col_SetType(const Arguments& args) {
    HandleScope handle_scope;
    b2BodyType type = (b2BodyType)args[0]->Int32Value();
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Collider* boxCollider = static_cast<Collider*>(entVal->Value());
    boxCollider->GetBox2DBody()->SetType(type);
    return Undefined();
}

Handle<Value> fl_col_SetLinearVelocity(const Arguments& args) {
    HandleScope handle_scope;
    GLfloat vx = (GLfloat)args[0]->NumberValue();
    GLfloat vy = (GLfloat)args[1]->NumberValue();
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Collider* boxCollider = static_cast<Collider*>(entVal->Value());
    boxCollider->GetBox2DBody()->SetLinearVelocity(b2Vec2(vx, vy));
    return Undefined();
}

Handle<Value> fl_col_GetLinearVelocity(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Collider* boxCollider = static_cast<Collider*>(entVal->Value());
    const b2Vec2 vel = boxCollider->GetBox2DBody()->GetLinearVelocity();
    Handle<Object> toReturn = Object::New();
    toReturn->Set(String::New("x"), Number::New(vel.x));
    toReturn->Set(String::New("y"), Number::New(vel.y));
    return handle_scope.Close(toReturn);
}

Handle<Value> fl_col_SetRestitution(const Arguments& args) {
    HandleScope handle_scope;
    GLfloat rest = (GLfloat)args[0]->NumberValue();
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Collider* boxCollider = static_cast<Collider*>(entVal->Value());
    boxCollider->SetRestitution(rest);
    return Undefined();
}

Handle<Value> fl_col_SetFriction(const Arguments& args) {
    HandleScope handle_scope;
    GLfloat friction = (GLfloat)args[0]->NumberValue();
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Collider* boxCollider = static_cast<Collider*>(entVal->Value());
    boxCollider->SetFriction(friction);
    return Undefined();
}

Handle<Value> fl_col_SetDensity(const Arguments& args) {
    HandleScope handle_scope;
    GLfloat friction = (GLfloat)args[0]->NumberValue();
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Collider* boxCollider = static_cast<Collider*>(entVal->Value());
    boxCollider->SetDensity(friction);
    return Undefined();
}

Handle<Value> fl_col_SetPhysicsProperties(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Collider* collider = static_cast<Collider*>(entVal->Value());
    Handle<Object> dict = args[0]->ToObject();
    if(dict->Has(String::New("type"))) {
        b2BodyType type = (b2BodyType)dict->Get(String::New("type"))->Int32Value();
        collider->SetType(type);
    }
    if(dict->Has(String::New("restitution"))) {
        GLfloat rest = (GLfloat)dict->Get(String::New("restitution"))->NumberValue();
        collider->SetRestitution(rest);
    }
    if(dict->Has(String::New("friction"))) {
        GLfloat friction = (GLfloat)dict->Get(String::New("friction"))->NumberValue();
        collider->SetFriction(friction);
    }
    if(dict->Has(String::New("density"))) {
        GLfloat density = (GLfloat)dict->Get(String::New("density"))->NumberValue();
        collider->SetDensity(density);
    }
    return Undefined();
}

Handle<Value> fl_col_GetType(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Collider* collider = static_cast<Collider*>(entVal->Value());
    return handle_scope.Close(Integer::New(collider->GetType()));
}

Handle<Value> fl_col_GetRestitution(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Collider* collider = static_cast<Collider*>(entVal->Value());
    return handle_scope.Close(Number::New(collider->GetRestitution()));
}

Handle<Value> fl_col_GetFriction(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Collider* collider = static_cast<Collider*>(entVal->Value());
    return handle_scope.Close(Number::New(collider->GetFriction()));
}

Handle<Value> fl_col_GetDensity(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Collider* collider = static_cast<Collider*>(entVal->Value());
    return handle_scope.Close(Number::New(collider->GetDensity()));
}

void ColliderBindings_AddMethodsToTemplate(Handle<ObjectTemplate>& instance_templ) {
    instance_templ->Set("setType", FunctionTemplate::New(fl_col_SetType));
    instance_templ->Set("getLinearVelocity", FunctionTemplate::New(fl_col_GetLinearVelocity));
    instance_templ->Set("setLinearVelocity", FunctionTemplate::New(fl_col_SetLinearVelocity));
    instance_templ->Set("setRestitution", FunctionTemplate::New(fl_col_SetRestitution));
    instance_templ->Set("setFriction", FunctionTemplate::New(fl_col_SetFriction));
    instance_templ->Set("setDensity", FunctionTemplate::New(fl_col_SetDensity));
    instance_templ->Set("setPhysicsProperties", FunctionTemplate::New(fl_col_SetPhysicsProperties));
    instance_templ->Set("getType", FunctionTemplate::New(fl_col_GetType));
    instance_templ->Set("getRestitution", FunctionTemplate::New(fl_col_GetRestitution));
    instance_templ->Set("getFriction", FunctionTemplate::New(fl_col_GetFriction));
    instance_templ->Set("getDensity", FunctionTemplate::New(fl_col_GetDensity));
    ComponentBindings_AddMethodsToTemplate(instance_templ);
}

void ColliderBindings_BindToGlobal(Persistent<ObjectTemplate>& global) {
    Handle<ObjectTemplate> constants = ObjectTemplate::New();
    constants->Set("static", Integer::New(0));
    constants->Set("kinematic", Integer::New(1));
    constants->Set("dynamic", Integer::New(2));
    global->Set("Collider", constants);
}