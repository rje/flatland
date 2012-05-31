//
//  BoxCollider.h
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_BoxCollider_h
#define flatland_BoxCollider_h

#include "Collider.h"

class BoxCollider : public Collider {
public:
    BoxCollider();
    virtual ~BoxCollider();
    virtual void SetSize(GLfloat halfWidth, GLfloat halfHeight);
    virtual void Register();
    virtual void Unregister();
    virtual void Update(GLfloat delta);
    virtual void UpdateWithTransform(Transform* t);
    virtual Persistent<Object> GetWrappedObject();
protected:
    GLfloat m_halfWidth;
    GLfloat m_halfHeight;
};


#endif
