//
//  EntityBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "EntityBindings.h"
#include "Entity.h"

using namespace v8;

Handle<Value> fl_eb_AddComponent(const Arguments& args) {
    if(args.Length() != 1) {
        return ThrowException(String::New("Entity.addComponent must be passed exactly 1 component as a parameter"));
    }
    HandleScope handle_scope;
    Handle<Object> obj = args[0]->ToObject();
    Local<Value> intVal = obj->GetInternalField(0);
    if(!intVal->IsExternal()) {
        return ThrowException(String::New("Entity.addComponent must be passed exactly 1 component as a parameter"));
    }
    Local<External> extVal = Local<External>::Cast(intVal);
    Component* comp = static_cast<Component*>(extVal->Value());
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Entity* entity = static_cast<Entity*>(entVal->Value());
    entity->AddComponent(comp);
    return handle_scope.Close(obj);
}

Handle<Value> fl_eb_GetComponent(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Entity* entity = static_cast<Entity*>(entVal->Value());
    String::Utf8Value type(args[0]->ToString());
    string typeName = *type;
    Component* toReturn = entity->GetComponentByTypeName(typeName);
    if(toReturn == NULL) {
        return Undefined();
    }
    else {
        return toReturn->GetWrappedObject();
    }
}

Handle<Value> fl_eb_Destroy(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Entity* entity = static_cast<Entity*>(entVal->Value());
    entity->MarkForDestruction();
    return Undefined();
}

Handle<FunctionTemplate> fl_eb_GetTemplate() {
    HandleScope handle_scope;
    Handle<FunctionTemplate> templ = FunctionTemplate::New();
    Handle<ObjectTemplate> instance_templ = templ->InstanceTemplate();
    instance_templ->Set("addComponent", FunctionTemplate::New(fl_eb_AddComponent));
    instance_templ->Set("getComponent", FunctionTemplate::New(fl_eb_GetComponent));
    instance_templ->Set("destroy", FunctionTemplate::New(fl_eb_Destroy));
    instance_templ->SetInternalFieldCount(1);
    return handle_scope.Close(templ);
}

Handle<Value> EntityBindings_WrapEntity(Entity* toWrap) {
    static Persistent<FunctionTemplate> s_templ = Persistent<FunctionTemplate>::New(fl_eb_GetTemplate());
    HandleScope handle_scope;
    Local<Object> entity_inst = s_templ->InstanceTemplate()->NewInstance();
    entity_inst->SetInternalField(0, External::New(toWrap));
    Persistent<Object> ref = Persistent<Object>::New(entity_inst->ToObject());
    toWrap->SetWrappedObject(ref);
    return handle_scope.Close(entity_inst);
}

Handle<Value> fl_eb_ConstructorCall(const Arguments& args) {
    if(!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor like a function"));
    }
    HandleScope handle_scope;
    String::Utf8Value name(args[0]->ToString());
    Entity* entity = new Entity();
    entity->SetName(new string(*name));
    return EntityBindings_WrapEntity(entity);
}

void EntityBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global) {
    HandleScope handle_scope;
    global->Set("Entity", FunctionTemplate::New(fl_eb_ConstructorCall));
}
