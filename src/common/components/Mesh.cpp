//
//  Mesh.cpp
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Mesh.h"
#include "Entity.h"
#include "MeshBindings.h"
#define _USE_MATH_DEFINES // needed for the windows build, yay windows
#include <math.h>

Mesh::Mesh() : m_verts(NULL), m_uvs(NULL), m_indices(NULL) {
    m_ident = new string("Mesh");
}

Persistent<Object> Mesh::GetWrappedObject() {
    HandleScope handle_scope;
    if(m_wrappedJSVersion.IsEmpty()) {
        m_wrappedJSVersion = Persistent<Object>::New(MeshBindings_WrapMesh(this)->ToObject());
    }
    return m_wrappedJSVersion;
}

Mesh::~Mesh() {
    
}

Mesh* Mesh::CreateRect(GLfloat w, GLfloat h) {
    Mesh* toReturn = new Mesh();
    toReturn->m_verts = new Vector3[4];
    toReturn->m_uvs = new Vector2[4];
    toReturn->m_indices = new GLushort[6];
    GLfloat wd2 = w / 2.0f;
    GLfloat hd2 = h / 2.0f;
    for(int i = 0; i < 4; i++) {
        toReturn->m_verts[i].x = (i % 2 == 0) ? -wd2 : wd2;
        toReturn->m_verts[i].y = (i / 2 == 0) ? hd2 : -hd2;
        toReturn->m_verts[i].z = 0;
        toReturn->m_uvs[i].x = (i % 2 == 0) ? 0 : 1;
        toReturn->m_uvs[i].y = (i / 2 == 0) ? 1 : 0;
    }
    toReturn->m_indices[0] = 0;
    toReturn->m_indices[1] = 1;
    toReturn->m_indices[2] = 2;
    toReturn->m_indices[3] = 1;
    toReturn->m_indices[4] = 2;
    toReturn->m_indices[5] = 3;
    toReturn->m_indexCount = 6;
    toReturn->m_meshType = GL_TRIANGLES;
    return toReturn;
}

Mesh* Mesh::CreateCircle(GLfloat radius, GLint numPoints) {
    Mesh* toReturn = new Mesh();
    toReturn->m_verts = new Vector3[numPoints];
    toReturn->m_uvs = new Vector2[numPoints];
    toReturn->m_indices = new GLushort[numPoints];
    for(int i = 0; i < numPoints; i++) {
        GLfloat cx = cos(2 * M_PI * i / (GLfloat)numPoints);
        GLfloat sy = sin(2 * M_PI * i / (GLfloat)numPoints);
        toReturn->m_verts[i].x = radius * cx;
        toReturn->m_verts[i].y = radius * sy;
        toReturn->m_verts[i].z = 0;
        toReturn->m_uvs[i].x = 0.5 + cx/2;
        toReturn->m_uvs[i].y = 0.5 + sy/2;
        toReturn->m_indices[i] = i;
    }
    toReturn->m_indexCount = numPoints;
    toReturn->m_meshType = GL_TRIANGLE_FAN;
    
    return toReturn;
}

Vector3* Mesh::GetVertexArray() {
    return m_verts;
}

Vector2* Mesh::GetUVArray() {
    return m_uvs;
}

GLushort* Mesh::GetIndexArray() {
    return m_indices;
}

GLint Mesh::GetIndexCount() {
    return m_indexCount;
}

GLenum Mesh::GetMeshType() {
    return m_meshType;
}