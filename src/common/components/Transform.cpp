//
//  Transform.cpp
//  flatland
//
//  Created by Ryan Evans on 5/25/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Transform.h"
#include "Entity.h"
#include "TransformBindings.h"

Transform::Transform() : m_pos(0.0f, 0.0f, 0.0f), m_angle(0.0f) {
    m_ident = new string("Transform");
}

Transform::~Transform() {
    
}

Persistent<Object> Transform::GetWrappedObject() {
    HandleScope handle_scope;
    if(m_wrappedJSVersion.IsEmpty()) {
        m_wrappedJSVersion = Persistent<Object>::New(TransformBindings_WrapTransform(this)->ToObject());
    }
    return m_wrappedJSVersion;
}

void Transform::SetPosition(GLfloat x, GLfloat y) {
    m_pos.x = x;
    m_pos.y = y;
}

void Transform::SetPosition(GLfloat x, GLfloat y, GLfloat z) {
    m_pos.x = x;
    m_pos.y = y;
    m_pos.z = z;
}

void Transform::SetDepth(GLfloat z) {
    m_pos.z = z;
}

void Transform::SetRotation(GLfloat angle) {
    m_angle = angle;
}

Vector3& Transform::GetPosition() {
    return m_pos; 
}

GLfloat& Transform::GetAngle() {
    return m_angle;
}