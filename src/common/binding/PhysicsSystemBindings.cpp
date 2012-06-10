//
//  PhysicsSystemBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 6/9/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "PhysicsSystemBindings.h"
#include "PhysicsSystem.h"

using namespace v8;

Handle<Value> fl_ps_SetGravity(const Arguments& args) {
    Locker locker;
    HandleScope handle_scope;
    GLfloat width = args[0]->NumberValue();
    GLfloat height = args[1]->NumberValue();
    PhysicsSystem::instance()->SetGravity(width, height);
    return handle_scope.Close(args.This());
}

Handle<Value> fl_ps_GetGravity(const Arguments& args) {
    Locker locker;
    HandleScope handle_scope;
    Handle<Object> toReturn = Object::New();
    b2Vec2 g = PhysicsSystem::instance()->GetGravity();
    toReturn->Set(String::New("x"), Number::New(g.x));
    toReturn->Set(String::New("y"), Number::New(g.y));
    return handle_scope.Close(toReturn);
}

Handle<Value> fl_ps_ToggleDebugDrawFlag(const Arguments& args) {
    Locker locker;
    HandleScope handle_scope;
    GLuint flag = args[0]->Uint32Value();
    GLboolean state = args[1]->BooleanValue();
    PhysicsSystem::instance()->ToggleDebugDrawFlag(flag, state);
    return handle_scope.Close(args.This());
}

void PhysicsSystemBindings_BindToGlobal(Persistent<ObjectTemplate>& global) {
    Locker locker;
    HandleScope handle_scope;
    Handle<ObjectTemplate> ps = ObjectTemplate::New();
    ps->Set(String::New("setGravity"), FunctionTemplate::New(fl_ps_SetGravity));
    ps->Set(String::New("getGravity"), FunctionTemplate::New(fl_ps_GetGravity));
    ps->Set(String::New("toggleDebugDrawFlag"), FunctionTemplate::New(fl_ps_ToggleDebugDrawFlag));
    Handle<ObjectTemplate> debugFlags = ObjectTemplate::New();
    debugFlags->Set("shape", Integer::New(b2Draw::e_shapeBit));
    debugFlags->Set("aabb", Integer::New(b2Draw::e_aabbBit));
    debugFlags->Set("centerOfMass", Integer::New(b2Draw::e_centerOfMassBit));
    debugFlags->Set("joint", Integer::New(b2Draw::e_jointBit));
    debugFlags->Set("pair", Integer::New(b2Draw::e_pairBit));
    ps->Set("debugFlags", debugFlags);
    global->Set("PhysicsSystem", ps);
}