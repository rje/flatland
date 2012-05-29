//
//  Scriptable.cpp
//  flatland
//
//  Created by Ryan Evans on 5/29/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Scriptable.h"
#include "ScriptableBindings.h"
#include "JSInterpreter.h"

Scriptable::Scriptable(string& name) : m_name(name) {
    m_ident = new string("Scriptable");
}

Scriptable::~Scriptable() {
    
}

Persistent<Object> Scriptable::GetWrappedObject() {
    HandleScope handle_scope;
    if(m_wrappedJSVersion.IsEmpty()) {
        m_wrappedJSVersion = Persistent<Object>::New(ScriptableBindings_WrapScriptable(this)->ToObject());
    }
    return m_wrappedJSVersion;
}

void Scriptable::Update(GLfloat delta) {
    Locker locker;
    HandleScope handle_scope;
    Context::Scope context_scope(JSInterpreter::Instance()->m_context);
    GetWrappedObject()->Has(String::New("onUpdate"));
    Handle<Function> toCall = GetWrappedObject()->Get(String::New("onUpdate")).As<Function>();
    Handle<Value> argv[] = { Number::New(delta) };
    toCall->Call(GetWrappedObject(), 1, argv);
}

