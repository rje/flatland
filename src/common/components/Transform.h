//
//  Transform.h
//  flatland
//
//  Created by Ryan Evans on 5/25/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Transform_h
#define flatland_Transform_h

#include "Component.h"
#include "Vectors.h"

class Transform : public Component {
public:
    Transform();
    virtual ~Transform();
    virtual Persistent<Object> GetWrappedObject();
    
    void SetPosition(GLfloat x, GLfloat y);
    void SetPosition(GLfloat x, GLfloat y, GLfloat z);
    void SetDepth(GLfloat z);
    void SetAngle(GLfloat angle);
    void PhysicsUpdate(GLfloat x, GLfloat y, GLfloat angle);
    
    Vector3& GetPosition();
    GLfloat& GetAngle();
    
private:
    Vector3 m_pos;
    GLfloat m_angle;
};

#endif
