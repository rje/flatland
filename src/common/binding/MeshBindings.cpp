//
//  MeshBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "MeshBindings.h"
#include "Mesh.h"
#include "ComponentBindings.h"

using namespace v8;

Handle<Value> fl_mb_CreateRect(const Arguments& args);

Handle<FunctionTemplate> fl_mb_GetTemplate() {
    HandleScope handle_scope;
    Handle<FunctionTemplate> templ = FunctionTemplate::New();
    Handle<ObjectTemplate> instance_templ = templ->InstanceTemplate();
    instance_templ->SetInternalFieldCount(1);
    ComponentBindings_AddMethodsToTemplate(instance_templ);
    return handle_scope.Close(templ);
}

Handle<Value> MeshBindings_WrapMesh(Mesh* toWrap) {
    static Persistent<FunctionTemplate> s_templ = Persistent<FunctionTemplate>::New(fl_mb_GetTemplate());
    HandleScope handle_scope;
    Local<Object> mesh_inst = s_templ->InstanceTemplate()->NewInstance();
    mesh_inst->SetInternalField(0, External::New(toWrap));
    Persistent<Object> ref = Persistent<Object>::New(mesh_inst->ToObject());
    toWrap->SetWrappedObject(ref);
    return handle_scope.Close(mesh_inst);
}

Handle<Value> fl_mb_ConstructorCall(const Arguments& args) {
    if(!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor like a function"));
    }
    HandleScope handle_scope;
    Mesh* mesh = new Mesh();
    return MeshBindings_WrapMesh(mesh);
}

Handle<Value> fl_mb_CreateRect(const Arguments& args) {
    HandleScope handle_scope;
    GLfloat width = args[0]->NumberValue();
    GLfloat height = args[1]->NumberValue();
    Mesh* mesh = Mesh::CreateRect(width, height);
    return MeshBindings_WrapMesh(mesh);
}

void MeshBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global) {
    HandleScope handle_scope;
    Handle<FunctionTemplate> meshObj = FunctionTemplate::New(fl_mb_ConstructorCall);
    meshObj->Set("createRect", FunctionTemplate::New(fl_mb_CreateRect));
    global->Set("Mesh", meshObj);
}
