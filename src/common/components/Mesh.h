//
//  Mesh.h
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Mesh_h
#define flatland_Mesh_h

#include "Component.h"
#include "Vectors.h"

class Mesh : public Component {
public:
    Mesh();
    virtual ~Mesh();
    virtual Persistent<Object> GetWrappedObject();
    
    static Mesh* CreateRect(GLfloat w, GLfloat h);
    
    Vector3* GetVertexArray();
    GLushort* GetIndexArray();
    
protected:
    Vector3* m_verts;
    Vector2* m_uvs;
    GLushort* m_indices;
};


#endif
