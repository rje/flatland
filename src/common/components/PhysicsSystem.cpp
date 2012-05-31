//
//  PhysicsSystem.cpp
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "PhysicsSystem.h"
#include <math.h>

class PSDebugDraw : public b2Draw {
public:
    virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
        glColor4f(color.r, color.g, color.b, 1.0f);
        glEnableClientState(GL_VERTEX_ARRAY);
        GLfloat* verts = new GLfloat[vertexCount * 3];
        GLushort* indices = new GLushort[vertexCount];
        for(int i = 0; i < vertexCount; i++) {
            int base = i * 3;
            verts[base + 0] = vertices[i].x * 32.0f;
            verts[base + 1] = vertices[i].y * 32.0f;
            verts[base + 2] = 0.0f;
            indices[i] = i;
        }
        glVertexPointer(3, GL_FLOAT, 0, verts);
        glDrawElements(GL_LINE_LOOP, vertexCount, GL_UNSIGNED_SHORT, indices);
        delete verts;
        delete indices;
    }
    
    virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
        glColor4f(color.r, color.g, color.b, 0.5f);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GLfloat* verts = new GLfloat[vertexCount * 3];
        GLushort* indices = new GLushort[vertexCount];
        for(int i = 0; i < vertexCount; i++) {
            int base = i * 3;
            verts[base + 0] = vertices[i].x * 32.0f;
            verts[base + 1] = vertices[i].y * 32.0f;
            verts[base + 2] = 0.0f;
            indices[i] = i;
        }
        glVertexPointer(3, GL_FLOAT, 0, verts);
        glDrawElements(GL_TRIANGLE_FAN, vertexCount, GL_UNSIGNED_SHORT, indices);
        delete verts;
        delete indices;
    }
    
    virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
        GLint vertexCount = 36;
        glColor4f(color.r, color.g, color.b, 1.0f);
        glEnableClientState(GL_VERTEX_ARRAY);
        GLfloat* verts = new GLfloat[vertexCount * 3];
        GLushort* indices = new GLushort[vertexCount];
        for(int i = 0; i < vertexCount; i++) {
            int base = i * 3;
            verts[base + 0] = center.x + radius * cos(i * 10.0f * M_PI / 180.0f);
            verts[base + 1] = center.y + radius * sin(i * 10.0f * M_PI / 180.0f);
            verts[base + 2] = 0.0f;
            indices[i] = i;
        }
        glVertexPointer(3, GL_FLOAT, 0, verts);
        glDrawElements(GL_LINE_LOOP, vertexCount, GL_UNSIGNED_SHORT, indices);
    }
    
    virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
        GLint vertexCount = 36;
        glColor4f(color.r, color.g, color.b, 1.0f);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnable(GL_BLEND);
        GLfloat* verts = new GLfloat[vertexCount * 3];
        GLushort* indices = new GLushort[vertexCount];
        for(int i = 0; i < vertexCount; i++) {
            int base = i * 3;
            verts[base + 0] = (center.x + radius * cos(i * 10.0f * M_PI / 180.0f)) * 32.0f;
            verts[base + 1] = (center.y + radius * sin(i * 10.0f * M_PI / 180.0f)) * 32.0f;
            verts[base + 2] = 0.0f;
            indices[i] = i;
        }
        glVertexPointer(3, GL_FLOAT, 0, verts);
        glDrawElements(GL_TRIANGLE_FAN, vertexCount, GL_UNSIGNED_SHORT, indices);
        
    }
    
    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
        glColor4f(color.r, color.g, color.b, 1.0f);
        glEnableClientState(GL_VERTEX_ARRAY);
        GLfloat verts[] = {
            p1.x * 32.0f, p1.y * 32.0f, 0.0f,
            p2.x * 32.0f, p2.y * 32.0f, 0.0f
        };
        GLushort indices[] = {
            0, 1
        };
        glVertexPointer(3, GL_FLOAT, 0, verts);
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, indices);
    }
    
    virtual void DrawTransform(const b2Transform& xf) {
        
    }
};

class PSContactListner : public b2ContactListener {
    virtual void BeginContact(b2Contact* contact) {
        printf("Got a collision!\n");
        b2Body* a = contact->GetFixtureA()->GetBody();
        b2Body* b = contact->GetFixtureB()->GetBody();
        Collider* ac = (Collider*)a->GetUserData();
        Collider* bc = (Collider*)b->GetUserData();
        if(!ac->HandleCollision(bc)) {
            bc->HandleCollision(ac);
        }
        
    }
};

PhysicsSystem* PhysicsSystem::instance() {
    static PhysicsSystem* sm_ps_inst = NULL;
    if(sm_ps_inst == NULL) {
        sm_ps_inst = new PhysicsSystem();
        sm_ps_inst->Initialize();
    }
    
    return sm_ps_inst;
}

void PhysicsSystem::DoStep() {
    m_world->Step(0.016667f, 8, 3); // FIXME: expose settings for app-specific tuning
}

void PhysicsSystem::DrawDebugData() {
    m_world->DrawDebugData();
}

b2Body* PhysicsSystem::RegisterCollider(Collider* toRegister) {
    if(find(m_colliders.begin(), m_colliders.end(), toRegister) == m_colliders.end()) {
        m_colliders.push_back(toRegister);
        b2BodyDef bodyDef;
        bodyDef.userData = toRegister;
        b2Body* toReturn = m_world->CreateBody(&bodyDef);
        b2Shape* shape = toRegister->GetBodyShape();
        toReturn->SetTransform(b2Vec2(1, 1), 0);
        toReturn->CreateFixture(shape, 0.0f);
        return toReturn;
        
    }
    return NULL;
}

void PhysicsSystem::UnregisterCollider(Collider* toRemove) {
    for(ColliderVectorIter i = m_colliders.begin(); i != m_colliders.end(); ++i) {
        Collider* toCheck = *i;
        if(toRemove == toCheck) {
            m_colliders.erase(i);
            m_world->DestroyBody(toCheck->GetBox2DBody());
            return;
        }
    }
}

PhysicsSystem::PhysicsSystem() {
    
}

void PhysicsSystem::Initialize() {
    m_world = new b2World(b2Vec2(0.0, 0.0));
    m_world->SetAllowSleeping(true);
    PSDebugDraw* debug = new PSDebugDraw();
    debug->AppendFlags(b2Draw::e_shapeBit);
    debug->AppendFlags(b2Draw::e_aabbBit);
    debug->AppendFlags(b2Draw::e_pairBit);
    m_world->SetDebugDraw(debug);
    m_world->SetContactListener(new PSContactListner());
}

PhysicsSystem::~PhysicsSystem() {
    
}