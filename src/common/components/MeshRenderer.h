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

class MeshRenderer : public Component {
public:
    MeshRenderer();
    virtual ~MeshRenderer();
    
    virtual void Register();
    virtual void Unregister();
    virtual void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

protected:
    GLfloat m_r, m_g, m_b, m_a;
};

#endif
