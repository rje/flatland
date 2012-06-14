//
//  Collider.cpp
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Collider.h"
#include <v8.h>
#include "JSInterpreter.h"

using namespace v8;

Collider::Collider() : 
        m_body(NULL), 
        m_shape(NULL), 
        m_bodyType(b2_staticBody), 
        m_restitution(0.0f),
        m_friction(0.5f),
        m_density(1.0f) {
    
}

Collider::~Collider() {
    delete m_shape;
}

void Collider::SetType(b2BodyType newType) {
    m_bodyType = newType;
    if(m_body != NULL) {
        m_body->SetType(newType);
    }
}

void Collider::SetRestitution(GLfloat rest) {
    m_restitution = rest;
    if(m_body != NULL) {
        m_body->GetFixtureList()->SetRestitution(rest);
    }
}
void Collider::SetFriction(GLfloat friction) {
    m_friction = friction;
    if(m_body != NULL) {
        m_body->GetFixtureList()->SetFriction(friction);
    }
}

void Collider::SetDensity(GLfloat density) {
    m_density = density;
    if(m_body != NULL) {
        m_body->GetFixtureList()->SetDensity(density);
    }
}

b2BodyType Collider::GetType() {
    return m_bodyType;
}

GLfloat Collider::GetRestitution() {
    return m_restitution;
}

GLfloat Collider::GetFriction() {
    return m_friction;
}

GLfloat Collider::GetDensity() {
    return m_density;
}

Handle<Object> Collider::WrapContact(b2Contact* toWrap) {
    Locker locker;
    HandleScope handle_scope;
    Handle<Object> toReturn = Object::New();
    toReturn->Set(String::New("isTouching"), Boolean::New(toWrap->IsTouching()));
    b2WorldManifold worldManifold;
    toWrap->GetWorldManifold( &worldManifold );
    Handle<Array> points = Array::New(b2_maxManifoldPoints);
    for(int i = 0; i < b2_maxManifoldPoints; i++) {
        Handle<Object> toAdd = Object::New();
        toAdd->Set(String::New("x"), Number::New(worldManifold.points[i].x - m_body->GetPosition().x));
        toAdd->Set(String::New("y"), Number::New(worldManifold.points[i].y - m_body->GetPosition().y));
        points->Set(i, toAdd);
    }
    toReturn->Set(String::New("points"), points);
    return handle_scope.Close(toReturn);
}

GLboolean Collider::HandleCollision(b2Contact* contact, Collider* other) {
    Locker locker;
    HandleScope handle_scope;
    Context::Scope context_scope(JSInterpreter::Instance()->m_context);
    if(m_wrappedJSVersion->Has(String::New("onCollision"))) {
        Handle<Value> argv[] = { WrapContact(contact), other->GetWrappedObject() };
        Local<Value> result = m_wrappedJSVersion->Get(String::New("onCollision")).As<Function>()->Call(m_wrappedJSVersion, 2, argv);
        return result->BooleanValue();
    }
    return false;
}