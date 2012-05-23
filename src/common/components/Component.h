//
//  Component.h
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Component_h
#define flatland_Component_h

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>

#include <vector>
using namespace std;

class Component;
typedef vector<Component*> ComponentVector;
typedef ComponentVector::iterator CVIter;

class Component {
public:
    Component() {}
    virtual ~Component() {}
    
    virtual void Update(GLfloat delta) {};
};

#endif
