//
//  CameraBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "CameraBindings.h"
#include "Camera.h"
#include "ComponentBindings.h"

using namespace v8;

Handle<Value> fl_cam_SetOrtho(const Arguments& args) {
    HandleScope handle_scope;
    GLfloat left = (GLfloat)(args[0]->NumberValue());
    GLfloat right = (GLfloat)(args[1]->NumberValue());
    GLfloat bottom = (GLfloat)(args[2]->NumberValue());
    GLfloat top = (GLfloat)(args[3]->NumberValue());
    GLfloat nearPlane = (GLfloat)(args[4]->NumberValue());
    GLfloat farPlane = (GLfloat)(args[5]->NumberValue());
    
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Camera* cam = static_cast<Camera*>(entVal->Value());
    cam->SetOrtho(left, right, bottom, top, nearPlane, farPlane);
    
    return handle_scope.Close(args.This());
}

Handle<FunctionTemplate> fl_cam_GetTemplate() {
    HandleScope handle_scope;
    Handle<FunctionTemplate> templ = FunctionTemplate::New();
    Handle<ObjectTemplate> instance_templ = templ->InstanceTemplate();
    ComponentBindings_AddMethodsToTemplate(instance_templ);
    instance_templ->SetInternalFieldCount(1);
    instance_templ->Set("setOrtho", FunctionTemplate::New(fl_cam_SetOrtho));
    return handle_scope.Close(templ);
}

Handle<Value> CameraBindings_WrapCamera(Camera* toWrap) {
    static Persistent<FunctionTemplate> s_templ = Persistent<FunctionTemplate>::New(fl_cam_GetTemplate());
    HandleScope handle_scope;
    Local<Object> cam_inst = s_templ->InstanceTemplate()->NewInstance();
    cam_inst->SetInternalField(0, External::New(toWrap));
    Persistent<Object> ref = Persistent<Object>::New(cam_inst->ToObject());
    toWrap->SetWrappedObject(ref);
    return handle_scope.Close(cam_inst);
}

Handle<Value> fl_cam_ConstructorCall(const Arguments& args) {
    if(!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor like a function"));
    }
    HandleScope handle_scope;
    Camera* cam = new Camera();
    return CameraBindings_WrapCamera(cam);
}

void CameraBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global) {
    HandleScope handle_scope;
    global->Set("Camera", FunctionTemplate::New(fl_cam_ConstructorCall));
}
