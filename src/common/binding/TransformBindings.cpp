//
//  TransformBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 5/25/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "TransformBindings.h"
#include "Transform.h"

using namespace v8;

Handle<Value> fl_tf_SetPosition(const Arguments& args) {
    HandleScope handle_scope;
    GLfloat x, y, z;
    GLboolean hasZ = true;
    x = (GLfloat)args[0]->NumberValue();
    y = (GLfloat)args[1]->NumberValue();
    if(args.Length() == 3) {
        z = (GLfloat)args[2]->NumberValue();
    }
    else {
        hasZ = false;
    }
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Transform* transform = static_cast<Transform*>(entVal->Value());
    if(hasZ) {
        transform->SetPosition(x, y, z);
    }
    else {
        transform->SetPosition(x, y);
    }
    return handle_scope.Close(args.This());
}

Handle<Value> fl_tf_GetPosition(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Transform* transform = static_cast<Transform*>(entVal->Value());
    Vector3 vec = transform->GetPosition();
    Handle<Object> toReturn = Object::New();
    toReturn->Set(String::New("x"), Number::New(vec.x));
    toReturn->Set(String::New("y"), Number::New(vec.y));
    toReturn->Set(String::New("z"), Number::New(vec.z));
    
    return handle_scope.Close(toReturn);
}

Handle<FunctionTemplate> fl_tf_GetTemplate() {
    HandleScope handle_scope;
    Handle<FunctionTemplate> templ = FunctionTemplate::New();
    Handle<ObjectTemplate> instance_templ = templ->InstanceTemplate();
    instance_templ->Set("setPosition", FunctionTemplate::New(fl_tf_SetPosition));
    instance_templ->Set("getPosition", FunctionTemplate::New(fl_tf_GetPosition));
    instance_templ->SetInternalFieldCount(1);
    return handle_scope.Close(templ);
}

Handle<Value> TransformBindings_WrapTransform(Transform* toWrap) {
    static Persistent<FunctionTemplate> s_templ = Persistent<FunctionTemplate>::New(fl_tf_GetTemplate());
    HandleScope handle_scope;
    Local<Object> transform_inst = s_templ->InstanceTemplate()->NewInstance();
    transform_inst->SetInternalField(0, External::New(toWrap));
    Persistent<Object> ref = Persistent<Object>::New(transform_inst->ToObject());
    toWrap->SetWrappedObject(ref);
    return handle_scope.Close(transform_inst);
}

Handle<Value> fl_tf_ConstructorCall(const Arguments& args) {
    if(!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor like a function"));
    }
    HandleScope handle_scope;
    Transform* transform = new Transform();
    return TransformBindings_WrapTransform(transform);
}

void TransformBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global) {
    HandleScope handle_scope;
    global->Set("Transform", FunctionTemplate::New(fl_tf_ConstructorCall));
}
