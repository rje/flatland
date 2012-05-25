//
//  MeshRenderer.cpp
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "MeshRenderer.h"
#include "Entity.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer() {
    
}

MeshRenderer::~MeshRenderer() {
    
}

void MeshRenderer::Register() {
    m_owner->GetComponent<Mesh>();
}

void MeshRenderer::Unregister() {
    
}

void MeshRenderer::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    m_r = r;
    m_g = g;
    m_b = b;
    m_a = a;
}