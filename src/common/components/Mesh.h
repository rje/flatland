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

class Mesh : public Component {
public:
    Mesh();
    virtual ~Mesh();
    
    virtual void Update(GLfloat delta);
    
    static Mesh* CreateRect(GLfloat w, GLfloat h);
};


#endif
