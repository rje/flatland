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
#include <Box2D/box2d.h>
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
    virtual b2PolygonShape& GetBodyShape() { return m_shape; }
    virtual void UpdateWithTransform(Transform* t) = 0;
    virtual void SetType(b2BodyType newType) { m_body->SetType(newType); }
    virtual GLboolean HandleCollision(Collider* other);
    virtual void SetRestitution(GLfloat rest) { m_body->GetFixtureList()->SetRestitution(1); }
protected:
    b2Body* m_body;
    b2PolygonShape m_shape;
};

#endif
