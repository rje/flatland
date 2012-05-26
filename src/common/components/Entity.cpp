//
//  Entity.cpp
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Entity.h"
#define LOG printf

#include "EntityRegistry.h"
#include "Transform.h"

Entity::Entity() : m_name(NULL) {
    LOG("Entity::Entity()\n");
    Transform* t = new Transform();
    t->SetPosition(10, 10);
    this->AddComponent(t);
    EntityRegistry::instance()->RegisterEntity(this);
}

Entity::~Entity() {
    LOG("Entity::~Entity()\n");
    EntityRegistry::instance()->UnregisterEntity(this);
    if(m_name) {
        delete m_name;
    }
}

void Entity::SetName(string* name) {
    m_name = name;
}

string* Entity::GetName() {
    return m_name;
}

void Entity::AddComponent(Component* toAdd) {
    m_components.push_back(toAdd);
    toAdd->SetOwner(this);
    toAdd->Register();
}

void Entity::RemoveComponent(Component* toRemove) {
    for(ComponentVector::iterator i = m_components.begin(); i != m_components.end(); ++i){
        Component* toCheck = *i;
        if(toCheck == toRemove) {
            m_components.erase(i);
            return;
        }
    }
}

Component* Entity::GetComponentByTypeName(string& type) {
    for(ComponentVector::iterator i = m_components.begin(); i != m_components.end(); ++i){
        Component* toCheck = *i;
        if(toCheck->GetIdent() == type) {
            return toCheck;
        }
    }
    return NULL;
}