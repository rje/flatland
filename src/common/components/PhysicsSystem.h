//
//  PhysicsSystem.h
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_PhysicsSystem_h
#define flatland_PhysicsSystem_h

#include <Box2D/box2d.h>
#include "Collider.h"

using namespace std;

class PhysicsSystem {
public:
    static PhysicsSystem* instance();
    void DoStep();
    b2Body* RegisterCollider(Collider* toRegister);
    void UnregisterCollider(Collider* toRemove);
    void DrawDebugData();
private:
    PhysicsSystem();
    void Initialize();
    virtual ~PhysicsSystem();
    
    b2World* m_world;
    ColliderVector m_colliders;
};


#endif
