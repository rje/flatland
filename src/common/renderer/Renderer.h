//
//  Renderer.h
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Renderer_h
#define flatland_Renderer_h

#include <vector>
#include "Vectors.h"

class Window;

using namespace std;

class Renderer {
public:
    Renderer(Window* owningWindow);
    virtual ~Renderer();
    
    void Prepare();
    void Draw();
    void Flush();
    
protected:
    Window* m_owner;
};


#endif
