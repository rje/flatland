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
#include "Shader.h"
#include "EntityRegistry.h"
#include "Camera.h"

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

void MeshRenderer::SetShader(Shader* shader) {
    m_shader = shader;
}

Color MeshRenderer::GetColor() {
    Color toReturn;
    toReturn.r = m_r;
    toReturn.g = m_g;
    toReturn.b = m_b;
    toReturn.a = m_a;
    return toReturn;
}

Texture* MeshRenderer::GetTexture() {
    return m_texture;
}

Shader* MeshRenderer::GetShader() {
    return m_shader;
}

void MeshRenderer::Render() {
    m_shader->UseShader();
    Mesh* m = m_owner->GetComponent<Mesh>();
    Transform* t = m_owner->GetComponent<Transform>();
    Camera* cam = EntityRegistry::instance()->GetCameras()[0];
    if(m_texture) {
        m_texture->SetAsActive();
        glUniform1f(glGetUniformLocation(m_shader->GetProgram(), "u_tex"), m_texture->GetTextureID());
    }
    else {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    if(m) {
        glUniform4f(glGetUniformLocation(m_shader->GetProgram(), "u_color"), m_r, m_g, m_b, m_a);
        glUniformMatrix4fv(glGetUniformLocation(m_shader->GetProgram(), "u_pMatrix"), 
                           1, false, cam->GetMatrix().GetData());
        glUniformMatrix4fv(glGetUniformLocation(m_shader->GetProgram(), "u_mvMatrix"),
                           1, false, t->GetMatrix().GetData());
        m->BindBuffers();
        glDrawElements(m->GetMeshType(), m->GetIndexCount(), GL_UNSIGNED_SHORT, 0);
    }
}
