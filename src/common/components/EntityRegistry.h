//
//  EntityRegistry.h
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_EntityRegistry_h
#define flatland_EntityRegistry_h

#include "Entity.h"
#include <vector>

using namespace std;

class EntityRegistry {
public:
    static EntityRegistry* instance();
    
    void RegisterEntity(Entity* toAdd);
    void UnregisterEntity(Entity* toRemove);
    
private:
    EntityRegistry();
    void Init();
    virtual ~EntityRegistry();
    
    vector<Entity*> m_entities;
};

#endif
