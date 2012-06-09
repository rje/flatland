//
//  Collider.h
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Collider_h
#define flatland_Collider_h

#include "Component.h"
#include <Box2D/Box2D.h>
#include <vector>

using namespace std;

class Collider;
class Transform;

typedef vector<Collider*> ColliderVector;
typedef ColliderVector::iterator ColliderVectorIter;

class Collider : public Component {
public:
    Collider();
    virtual ~Collider();
    virtual void Update(GLfloat delta) {};
    virtual b2Body* GetBox2DBody() { return m_body; }
    virtual b2Shape* GetBodyShape() { return m_shape; }
    virtual void UpdateWithTransform(Transform* t, GLboolean pos, GLboolean angle) = 0;
    
    virtual GLboolean HandleCollision(b2Contact* contact, Collider* other);
    
    virtual void SetType(b2BodyType newType);
    virtual void SetRestitution(GLfloat rest);
    virtual void SetFriction(GLfloat friction);
    virtual void SetDensity(GLfloat density);
    
    virtual b2BodyType GetType();
    virtual GLfloat GetRestitution();
    virtual GLfloat GetFriction();
    virtual GLfloat GetDensity();
    
protected:
    v8::Handle<v8::Object> WrapContact(b2Contact* contact);
    b2Body* m_body;
    b2Shape* m_shape;
    
    b2BodyType m_bodyType;
    GLfloat m_restitution;
    GLfloat m_friction;
    GLfloat m_density;
};

#endif
