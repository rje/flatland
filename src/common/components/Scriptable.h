//
//  Scriptable.h
//  flatland
//
//  Created by Ryan Evans on 5/29/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Scriptable_h
#define flatland_Scriptable_h

#include "Component.h"

class Scriptable : public Component {
public:    
    Scriptable();
    virtual ~Scriptable();
    
    virtual Persistent<Object> GetWrappedObject();
    virtual void Update(GLfloat delta);
};

#endif
