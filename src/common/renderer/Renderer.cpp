//
//  Renderer.cpp
//  flatland
//
//  Created by Ryan Evans on 5/25/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Renderer.h"
#include "Window.h"
#include "EntityRegistry.h"
#include "Entity.h"
#include "MeshRenderer.h"

Renderer::Renderer(Window* owningWindow) : m_owner(owningWindow) {
    
}

Renderer::~Renderer() {
    
}

void Renderer::Prepare() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw() {
    const vector<Entity*> entityVec = EntityRegistry::instance()->GetEntities();
    for(vector<Entity*>::const_iterator i = entityVec.begin(); i != entityVec.end(); ++i) {
        Entity* e = *i;
        MeshRenderer* mr = e->GetComponent<MeshRenderer>();
        if(mr) {
            mr->Render();
        }
    }
}

void Renderer::Flush() {
    m_owner->Flush();
}