//
//  MeshRenderer.h
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_MeshRenderer_h
#define flatland_MeshRenderer_h

#include "Component.h"
#include "Vectors.h"

class Texture;
class Shader;

class MeshRenderer : public Component {
public:
    MeshRenderer();
    virtual ~MeshRenderer();
    virtual Persistent<Object> GetWrappedObject();

    
    virtual void Register();
    virtual void Unregister();
    virtual void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    virtual void SetTexture(Texture* tex);
    virtual void SetShader(Shader* shader);
    virtual Color GetColor();
    virtual Texture* GetTexture();
    virtual Shader* GetShader();
    virtual void Render();

protected:
    GLfloat m_r, m_g, m_b, m_a;
    Texture* m_texture;
    Shader* m_shader;
};

#endif
