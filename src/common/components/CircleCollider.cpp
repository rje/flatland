//
//  CircleCollider.cpp
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "CircleCollider.h"
#include "PhysicsSystem.h"
#include "CircleColliderBindings.h"
#include "Transform.h"
#include "Entity.h"
#include <math.h>

CircleCollider::CircleCollider() {
    m_ident = new string("CircleCollider");
    m_shape = new b2CircleShape();
}

CircleCollider::~CircleCollider() {
    PhysicsSystem::instance()->UnregisterCollider(this);
}

Persistent<Object> CircleCollider::GetWrappedObject() {
    HandleScope handle_scope;
    if(m_wrappedJSVersion.IsEmpty()) {
        m_wrappedJSVersion = 
        Persistent<Object>::New(CircleColliderBindings_WrapCircleCollider(this)->ToObject());
    }
    return m_wrappedJSVersion;
}

void CircleCollider::SetSize(GLfloat radius) {
    b2CircleShape* s = static_cast<b2CircleShape*>(m_shape);
    s->m_radius = radius;
}

void CircleCollider::Register() {
    m_body = PhysicsSystem::instance()->RegisterCollider(this);
    b2MassData mass;
    mass.mass = 100;
    mass.I = 100;
    m_body->SetMassData(&mass);
    Transform* t = m_owner->GetComponent<Transform>();
    if(t != NULL) {
        UpdateWithTransform(t, true, true);
    }
}

void CircleCollider::Unregister() {
    PhysicsSystem::instance()->UnregisterCollider(this);
}

void CircleCollider::Update(GLfloat delta) {
    Transform* t = m_owner->GetComponent<Transform>();
    t->PhysicsUpdate(m_body->GetPosition().x * 32.0f, m_body->GetPosition().y * 32.0f, m_body->GetAngle());
}

void CircleCollider::UpdateWithTransform(Transform* t, GLboolean pos, GLboolean angle) {
    Vector3& vec = t->GetPosition();
    GLfloat x = pos ? vec.x / 32.0f : m_body->GetPosition().x;
    GLfloat y = pos ? vec.y / 32.0f : m_body->GetPosition().y;
    GLfloat a = angle ? t->GetAngle() : m_body->GetAngle();
    m_body->SetTransform(b2Vec2(x, y), a);
}
