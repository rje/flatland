//
//  Entity.cpp
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Entity.h"

#include "EntityBindings.h"
#include "EntityRegistry.h"
#include "Transform.h"

Entity::Entity() : m_name(NULL) {
    this->AddComponent(new Transform());
    EntityRegistry::instance()->RegisterEntity(this);
}

Entity::~Entity() {
    EntityRegistry::instance()->UnregisterEntity(this);
    if(m_name) {
        delete m_name;
    }
}

void Entity::Update(GLfloat delta) {
    for(ComponentVector::iterator i = m_components.begin(); i != m_components.end(); ++i){
        Component* toCheck = *i;
        toCheck->Update(delta);
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

void Entity::SetWrappedObject(Persistent<Object>& handle) {
    m_wrappedObj = handle;
}

Persistent<Object> Entity::GetWrappedObject() {
    HandleScope handle_scope;
    if(m_wrappedObj.IsEmpty()) {
        m_wrappedObj = Persistent<Object>::New(EntityBindings_WrapEntity(this)->ToObject());
    }
    return m_wrappedObj;
}
