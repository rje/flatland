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

MeshRenderer::MeshRenderer() : m_r(1), m_g(1), m_b(1), m_a(1) {
    m_ident = new string("MeshRenderer");
}

MeshRenderer::~MeshRenderer() {
    printf("MeshRenderer::~MeshRenderer()\n");
}

void MeshRenderer::Register() {
}

void MeshRenderer::Unregister() {
    
}

void MeshRenderer::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    m_r = r;
    m_g = g;
    m_b = b;
    m_a = a;
}

void MeshRenderer::Render() {
    Mesh* m = m_owner->GetComponent<Mesh>();
    if(m) {
        glColor4f(m_r, m_g, m_b, m_a);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, m->GetVertexArray());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, m->GetIndexArray());
    }
}