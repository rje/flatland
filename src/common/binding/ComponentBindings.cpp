//
//  ComponentBindings.cpp
//  flatland
//
//  Created by Ryan Evans on 5/31/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "ComponentBindings.h"
#include "Component.h"
#include "Entity.h"

using namespace v8;

Handle<Value> fl_comp_GetParent(const Arguments& args) {
    HandleScope handle_scope;
    Local<External> entVal  = Local<External>::Cast(args.This()->GetInternalField(0));
    Component* comp = static_cast<Component*>(entVal->Value());
    return handle_scope.Close(comp->GetOwner()->GetWrappedObject());
}

void ComponentBindings_AddMethodsToTemplate(Handle<ObjectTemplate>& instance_templ) {
    instance_templ->Set("getParent", FunctionTemplate::New(fl_comp_GetParent));
}