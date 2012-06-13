//
//  Camera.h
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Camera_h
#define flatland_Camera_h

#include "flatland_common.h"
#include "Matrix.h"
#include "Component.h"

class Camera : public Component {
public:
    Camera();
    virtual ~Camera();
    
    virtual Persistent<Object> GetWrappedObject();
    void SetOrtho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
    Matrix4& GetMatrix();
    
    virtual void Register();
    virtual void Unregister();
protected:
    Matrix4 m_matrix;
};

#endif
