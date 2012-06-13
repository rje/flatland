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
    static Mesh* CreateCircle(GLfloat radius, GLint numPoints);
    
    Vector3* GetVertexArray();
    GLushort* GetIndexArray();
    Vector2* GetUVArray();
    GLint GetIndexCount();
    GLenum GetMeshType();
    
    void BindBuffers(GLboolean enableUVs);
    
protected:
    Vector3* m_verts;
    Vector2* m_uvs;
    GLushort* m_indices;
    GLint m_numVerts;
    GLint m_indexCount;
    GLenum m_meshType;
    
    GLuint m_vertBuffer;
    GLuint m_uvBuffer;
    GLuint m_indexBuffer;
    
    void CreateBuffers();
};


#endif
