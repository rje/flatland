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
#include "Transform.h"
#include "Texture.h"
#include "MeshRendererBindings.h"

MeshRenderer::MeshRenderer() : m_r(1), m_g(1), m_b(1), m_a(1), m_texture(NULL) {
    m_ident = new string("MeshRenderer");
}

Persistent<Object> MeshRenderer::GetWrappedObject() {
    HandleScope handle_scope;
    if(m_wrappedJSVersion.IsEmpty()) {
        m_wrappedJSVersion = Persistent<Object>::New(MeshRendererBindings_WrapMeshRenderer(this)->ToObject());
    }
    return m_wrappedJSVersion;
}

MeshRenderer::~MeshRenderer() {
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

void MeshRenderer::SetTexture(Texture* tex) {
    m_texture = tex;
}

void MeshRenderer::Render() {
    Mesh* m = m_owner->GetComponent<Mesh>();
    Transform* t = m_owner->GetComponent<Transform>();
    glPushMatrix();
    glRotatef(t->GetAngle(), 0.0f, 0.0f, 1.0f);
    glTranslatef(t->GetPosition().x, t->GetPosition().y, t->GetPosition().z);
    if(m_texture) {
        m_texture->SetAsActive();
    }
    else {
        glBindTexture(GL_TEXTURE_2D, NULL);
    }
    if(m) {
        glColor4f(m_r, m_g, m_b, m_a);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, m->GetVertexArray());
        if(m->GetUVArray()) {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2, GL_FLOAT, 0, m->GetUVArray());
        }
        else {
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        glDrawElements(m->GetMeshType(), m->GetIndexCount(), GL_UNSIGNED_SHORT, m->GetIndexArray());
    }
    glPopMatrix();
}