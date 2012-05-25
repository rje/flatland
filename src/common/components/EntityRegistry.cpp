//
//  EntityRegistry.cpp
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "EntityRegistry.h"
#define LOG printf

EntityRegistry* EntityRegistry::instance() {
    static EntityRegistry* s_reg = NULL;
    if(s_reg == NULL) {
        s_reg = new EntityRegistry();
        s_reg->Init();
    }
    
    return s_reg;
}

void EntityRegistry::RegisterEntity(Entity* toAdd) {
    m_entities.push_back(toAdd);
}

void EntityRegistry::UnregisterEntity(Entity* toRemove) {
    for(vector<Entity*>::iterator i = m_entities.begin(); i != m_entities.end(); ++i) {
        Entity* toCheck = *i;
        if(toRemove == toCheck) {
            m_entities.erase(i);
            return;
        }
    }
}

EntityRegistry::EntityRegistry() {
    
}

void EntityRegistry::Init() {
    LOG("EntityRegistry::Init()\n");
}

EntityRegistry::~EntityRegistry() {
    
}


const vector<Entity*> EntityRegistry::GetEntities() {
    return m_entities;
}