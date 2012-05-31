//
//  BoxCollider.cpp
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "BoxCollider.h"
#include "PhysicsSystem.h"
#include "BoxColliderBindings.h"
#include "Transform.h"
#include "Entity.h"

BoxCollider::BoxCollider() {
    m_ident = new string("BoxCollider");
}

BoxCollider::~BoxCollider() {
    PhysicsSystem::instance()->UnregisterCollider(this);
}

Persistent<Object> BoxCollider::GetWrappedObject() {
    HandleScope handle_scope;
    if(m_wrappedJSVersion.IsEmpty()) {
        m_wrappedJSVersion = 
            Persistent<Object>::New(BoxColliderBindings_WrapBoxCollider(this)->ToObject());
    }
    return m_wrappedJSVersion;
}

void BoxCollider::SetSize(GLfloat halfWidth, GLfloat halfHeight) {
    m_shape.SetAsBox(halfWidth, halfHeight);
}

void BoxCollider::Register() {
    m_body = PhysicsSystem::instance()->RegisterCollider(this);
    Transform* t = m_owner->GetComponent<Transform>();
    if(t != NULL) {
        UpdateWithTransform(t);
    }
}

void BoxCollider::Unregister() {
    PhysicsSystem::instance()->UnregisterCollider(this);
}

void BoxCollider::Update(GLfloat delta) {
    Transform* t = m_owner->GetComponent<Transform>();
    t->PhysicsUpdate(m_body->GetPosition().x * 32.0f, m_body->GetPosition().y * 32.0f, m_body->GetAngle());
}

void BoxCollider::UpdateWithTransform(Transform* t) {
    Vector3& vec = t->GetPosition();
    m_body->SetTransform(b2Vec2(vec.x / 32.0f, vec.y / 32.0f), t->GetAngle());
    
}