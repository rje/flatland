//
//  Entity.h
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Entity_h
#define flatland_Entity_h

#include "Component.h"
#include <vector>
#include <string>

using namespace std;

class Entity {
public:
    Entity();
    virtual ~Entity();
    void SetName(string* name);
    string* GetName();
    
    virtual void AddComponent(Component* toAdd);
    virtual void RemoveComponent(Component* toRemove);
    
    template <class T> T* GetComponent() {
        for(ComponentVector::iterator i = m_components.begin(); i != m_components.end(); ++i) {
            Component* toCheck = *i;
            T* val = dynamic_cast<T*>(toCheck);
            if(val) {
                return val;
            }
        }
        return NULL;
    };

protected:
    ComponentVector m_components;
    string* m_name;
};

#endif
