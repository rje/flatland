//
//  MeshRendererBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "MeshRendererBindings.h"
#include "MeshRenderer.h"

using namespace v8;

Handle<Value> fl_mrb_SetColor(const Arguments& args) {
    HandleScope handle_scope;
    GLfloat r = (GLfloat)args[0]->NumberValue();
    GLfloat g = (GLfloat)args[1]->NumberValue();
    GLfloat b = (GLfloat)args[2]->NumberValue();
    GLfloat a = (GLfloat)args[3]->NumberValue();
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    MeshRenderer* meshRenderer = static_cast<MeshRenderer*>(entVal->Value());
    meshRenderer->SetColor(r, g, b, a);
    return handle_scope.Close(args.This());
}

Handle<FunctionTemplate> fl_mrb_GetTemplate() {
    HandleScope handle_scope;
    Handle<FunctionTemplate> templ = FunctionTemplate::New();
    Handle<ObjectTemplate> instance_templ = templ->InstanceTemplate();
    instance_templ->Set("setColor", FunctionTemplate::New(fl_mrb_SetColor));
    instance_templ->SetInternalFieldCount(1);
    return handle_scope.Close(templ);
}

Handle<Value> MeshRendererBindings_WrapMeshRenderer(MeshRenderer* toWrap) {
    static Persistent<FunctionTemplate> s_templ = Persistent<FunctionTemplate>::New(fl_mrb_GetTemplate());
    HandleScope handle_scope;
    Local<Object> meshRenderer_inst = s_templ->InstanceTemplate()->NewInstance();
    meshRenderer_inst->SetInternalField(0, External::New(toWrap));
    return handle_scope.Close(meshRenderer_inst);
}

Handle<Value> fl_mrb_ConstructorCall(const Arguments& args) {
    if(!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor like a function"));
    }
    HandleScope handle_scope;
    String::Utf8Value name(args[0]->ToString());
    MeshRenderer* meshRenderer = new MeshRenderer();
    return MeshRendererBindings_WrapMeshRenderer(meshRenderer);
}

void MeshRendererBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global) {
    HandleScope handle_scope;
    global->Set("MeshRenderer", FunctionTemplate::New(fl_mrb_ConstructorCall));
}
