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

void EntityRegistry::CallUpdates(GLfloat delta) {
    for(vector<Entity*>::iterator i = m_entities.begin(); i != m_entities.end(); ++i) {
        Entity* toCall = *i;
        toCall->Update(delta);
    } 
}

void EntityRegistry::DestroyMarked() {
    vector<Entity*>::iterator iter = m_entities.begin();
    while(iter != m_entities.end()) {
        Entity* toCheck = *iter;
        if(toCheck->ShouldDestroy()) {
            iter = m_entities.erase(iter);
            delete toCheck;
        }
        else {
            ++iter;
        }
    }
}

EntityRegistry::EntityRegistry() {
    
}

void EntityRegistry::Init() {
}

EntityRegistry::~EntityRegistry() {
    
}

const vector<Entity*> EntityRegistry::GetEntities() {
    return m_entities;
}


void EntityRegistry::AddCamera(Camera* toAdd) {
    m_cameras.push_back(toAdd);
}

void EntityRegistry::RemoveCamera(Camera* toRemove) {
    vector<Camera*>::iterator i = find(m_cameras.begin(), m_cameras.end(), toRemove);
    if(i != m_cameras.end()) {
        m_cameras.erase(i);
    }
}

const vector<Camera*> EntityRegistry::GetCameras() {
    return m_cameras;
}