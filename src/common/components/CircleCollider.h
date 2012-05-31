//
//  CircleCollider.h
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_CircleCollider_h
#define flatland_CircleCollider_h

#include "Collider.h"

class CircleCollider : public Collider {
public:
    CircleCollider();
    virtual ~CircleCollider();
    virtual void SetSize(GLfloat radius);
    virtual void Register();
    virtual void Unregister();
    virtual void Update(GLfloat delta);
    virtual void UpdateWithTransform(Transform* t, GLboolean pos, GLboolean angle);
    virtual Persistent<Object> GetWrappedObject();
protected:
    GLfloat m_radius;
};

#endif
