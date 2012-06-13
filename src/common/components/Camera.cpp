//
//  Camera.cpp
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Camera.h"
#include "CameraBindings.h"
#include "EntityRegistry.h"

Camera::Camera() {
    
}

Camera::~Camera() {
    
}

void Camera::SetOrtho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far) {
    m_matrix = Matrix4::Ortho(left, right, bottom, top, near, far);
}

Matrix4& Camera::GetMatrix() {
    return m_matrix;
}

Persistent<Object> Camera::GetWrappedObject() {
    HandleScope handle_scope;
    if(m_wrappedJSVersion.IsEmpty()) {
        m_wrappedJSVersion = Persistent<Object>::New(CameraBindings_WrapCamera(this)->ToObject());
    }
    return m_wrappedJSVersion;
}

void Camera::Register() {
    EntityRegistry::instance()->AddCamera(this);
}

void Camera::Unregister() {
    EntityRegistry::instance()->RemoveCamera(this);
}