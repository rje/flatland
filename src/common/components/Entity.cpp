//
//  Entity.cpp
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Entity.h"
#define LOG printf


Entity::Entity() : m_name(NULL) {
    LOG("Entity::Entity()\n");
}

Entity::~Entity() {
    LOG("Entity::~Entity()\n");
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
}
