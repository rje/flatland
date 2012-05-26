//
//  Component.h
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Component_h
#define flatland_Component_h

#include <SDL2/SDL_opengl.h>

#include <vector>
using namespace std;

#include <v8.h>
using namespace v8;

class Entity;
class Component;
typedef vector<Component*> ComponentVector;
typedef ComponentVector::iterator CVIter;

class Component {
public:
    Component() {}
    virtual ~Component() {}
    
    virtual void Update(GLfloat delta) {};
    virtual void SetOwner(Entity* owner) { m_owner = owner; }
    virtual void Register() {}
    virtual void Unregister() {}
    
    virtual Persistent<Object> GetWrappedObject() = 0;
    virtual string& GetIdent() { return *m_ident; }
protected:
    Entity* m_owner;
    string* m_ident;
    Persistent<Object> m_wrappedJSVersion;
};

#endif
