//
//  Collider.cpp
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Collider.h"
#include <v8.h>

using namespace v8;

Collider::Collider() {
    
}

Collider::~Collider() {
    delete m_shape;
}

GLboolean Collider::HandleCollision(Collider* other) {
    Locker locker;
    HandleScope handle_scope;
    if(m_wrappedJSVersion->Has(String::New("onCollision"))) {
        Handle<Value> argv[] = { other->GetWrappedObject() };
        Local<Value> result = m_wrappedJSVersion->Get(String::New("onCollision")).As<Function>()->Call(m_wrappedJSVersion, 1, argv);
        return result->BooleanValue();
    }
    return false;
}