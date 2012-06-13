//
//  MeshRendererBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "MeshRendererBindings.h"
#include "MeshRenderer.h"
#include "ComponentBindings.h"
#include "Texture.h"
#include "Shader.h"

using namespace v8;

Handle<Value> fl_mrb_SetColor(const Arguments& args) {
    HandleScope handle_scope;
    GLfloat r = (GLfloat)args[0]->NumberValue();
    GLfloat g = (GLfloat)args[1]->NumberValue();
    GLfloat b = (GLfloat)args[2]->NumberValue();
    GLfloat a = 1.0f;
    if(args.Length() == 4) {
        a = (GLfloat)args[3]->NumberValue();
    }
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    MeshRenderer* meshRenderer = static_cast<MeshRenderer*>(entVal->Value());
    meshRenderer->SetColor(r, g, b, a);
    return handle_scope.Close(args.This());
}

Handle<Value> fl_mrb_SetTexture(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    MeshRenderer* meshRenderer = static_cast<MeshRenderer*>(entVal->Value());
    
    Local<Value> intVal = args[0]->ToObject()->GetInternalField(0);
    if(!intVal->IsExternal()) {
        return ThrowException(String::New("Entity.addComponent must be passed exactly 1 component as a parameter"));
    }
    Local<External> extVal = Local<External>::Cast(intVal);
    Texture* t = static_cast<Texture*>(extVal->Value());
    if(t) {
        meshRenderer->SetTexture(t);
    }
    
    return handle_scope.Close(args.This());
}

Handle<Value> fl_mrb_GetColor(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    MeshRenderer* meshRenderer = static_cast<MeshRenderer*>(entVal->Value());
    Color c = meshRenderer->GetColor();
    Local<Object> toReturn = Object::New();
    toReturn->Set(String::New("r"), Number::New(c.r));
    toReturn->Set(String::New("g"), Number::New(c.g));
    toReturn->Set(String::New("b"), Number::New(c.b));
    toReturn->Set(String::New("a"), Number::New(c.a));
    
    return handle_scope.Close(toReturn);
}

Handle<Value> fl_mrb_GetTexture(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    MeshRenderer* meshRenderer = static_cast<MeshRenderer*>(entVal->Value());
    if(meshRenderer->GetTexture()) {
        return handle_scope.Close(meshRenderer->GetTexture()->GetWrappedObject());
    }
    else {
        return Undefined();
    }
}

Handle<Value> fl_mrb_SetShader(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    MeshRenderer* meshRenderer = static_cast<MeshRenderer*>(entVal->Value());
    
    Local<Value> intVal = args[0]->ToObject()->GetInternalField(0);
    if(!intVal->IsExternal()) {
        return ThrowException(String::New("Entity.addComponent must be passed exactly 1 component as a parameter"));
    }
    Local<External> extVal = Local<External>::Cast(intVal);
    Shader* s = static_cast<Shader*>(extVal->Value());
    if(s) {
        meshRenderer->SetShader(s);
    }
    
    return handle_scope.Close(args.This());
}

Handle<FunctionTemplate> fl_mrb_GetTemplate() {
    HandleScope handle_scope;
    Handle<FunctionTemplate> templ = FunctionTemplate::New();
    Handle<ObjectTemplate> instance_templ = templ->InstanceTemplate();
    instance_templ->Set("setColor", FunctionTemplate::New(fl_mrb_SetColor));
    instance_templ->Set("setTexture", FunctionTemplate::New(fl_mrb_SetTexture));
    instance_templ->Set("getColor", FunctionTemplate::New(fl_mrb_GetColor));
    instance_templ->Set("getTexture", FunctionTemplate::New(fl_mrb_GetTexture));
    instance_templ->Set("setShader", FunctionTemplate::New(fl_mrb_SetShader));
    
    ComponentBindings_AddMethodsToTemplate(instance_templ);
    instance_templ->SetInternalFieldCount(1);
    return handle_scope.Close(templ);
}

Handle<Value> MeshRendererBindings_WrapMeshRenderer(MeshRenderer* toWrap) {
    static Persistent<FunctionTemplate> s_templ = Persistent<FunctionTemplate>::New(fl_mrb_GetTemplate());
    HandleScope handle_scope;
    Local<Object> meshRenderer_inst = s_templ->InstanceTemplate()->NewInstance();
    meshRenderer_inst->SetInternalField(0, External::New(toWrap));
    Persistent<Object> ref = Persistent<Object>::New(meshRenderer_inst->ToObject());
    toWrap->SetWrappedObject(ref);
    return handle_scope.Close(meshRenderer_inst);
}

Handle<Value> fl_mrb_ConstructorCall(const Arguments& args) {
    if(!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor like a function"));
    }
    HandleScope handle_scope;
    MeshRenderer* meshRenderer = new MeshRenderer();
    // FIXME: Eventually expose setshader call from javascript side
    meshRenderer->SetShader(Shader::defaultShader);
    return MeshRendererBindings_WrapMeshRenderer(meshRenderer);
}

void MeshRendererBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global) {
    HandleScope handle_scope;
    global->Set("MeshRenderer", FunctionTemplate::New(fl_mrb_ConstructorCall));
}
