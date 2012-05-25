//
//  Mesh.cpp
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Mesh.h"


Mesh::Mesh() {
    
}

Mesh::~Mesh() {
    
}

Mesh* Mesh::CreateRect(GLfloat w, GLfloat h) {
    Mesh* toReturn = new Mesh();
    toReturn->m_verts = new Vector3[4];
    toReturn->m_uvs = new Vector2[4];
    toReturn->m_indices = new GLshort[6];
    for(int i = 0; i < 4; i++) {
        toReturn->m_verts[i].x = (i % 2 == 0) ? 0 : w;
        toReturn->m_verts[i].y = (i / 2 == 0) ? 0 : h;
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
    
    return toReturn;
}