//
//  PhysicsSystem.cpp
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "PhysicsSystem.h"
#define _USE_MATH_DEFINES // needed for the windows build, yay windows
#include <math.h>
#include "EntityRegistry.h"
#include "Camera.h"
#include "Shader.h"
#include "flatland_common.h"

class PSDebugDraw : public b2Draw {
public:
    virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
        GLfloat* verts = new GLfloat[vertexCount * 3];
        GLushort* indices = new GLushort[vertexCount];
        for(int i = 0; i < vertexCount; i++) {
            int base = i * 3;
            verts[base + 0] = vertices[i].x;
            verts[base + 1] = vertices[i].y;
            verts[base + 2] = 0.0f;
            indices[i] = i;
        }
        Shader* s = Shader::defaultNoTextureShader;
        Camera* cam = EntityRegistry::instance()->GetCameras()[0];
        glUseProgram(s->GetProgram());
        
        glEnableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        
        if(!m_vertBuffer) {
            glGenBuffers(1, &m_vertBuffer);
        }
        glBindBuffer(GL_ARRAY_BUFFER, m_vertBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * vertexCount, verts, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
        
        if(!m_indexBuffer) {
            glGenBuffers(1, &m_indexBuffer);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * vertexCount, indices, GL_STATIC_DRAW);
        
        glUniform4f(glGetUniformLocation(s->GetProgram(), "u_color"), color.r, color.g, color.b, 1.0f);
        glUniformMatrix4fv(glGetUniformLocation(s->GetProgram(), "u_pMatrix"), 
                            1, false, cam->GetMatrix().GetData());
        glUniformMatrix4fv(glGetUniformLocation(s->GetProgram(), "u_mvMatrix"),
                            1, false, Matrix4::Identity().GetData());
        
        glDrawElements(GL_LINE_LOOP, vertexCount, GL_UNSIGNED_SHORT, 0);
        delete verts;
        delete indices;
    }
    
    virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
        GLfloat* verts = new GLfloat[vertexCount * 3];
        GLushort* indices = new GLushort[vertexCount];
        for(int i = 0; i < vertexCount; i++) {
            int base = i * 3;
            verts[base + 0] = vertices[i].x;
            verts[base + 1] = vertices[i].y;
            verts[base + 2] = 0.0f;
            indices[i] = i;
        }
        Shader* s = Shader::defaultNoTextureShader;
        Camera* cam = EntityRegistry::instance()->GetCameras()[0];
        glUseProgram(s->GetProgram());
        
        glEnableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        
        if(!m_vertBuffer) {
            glGenBuffers(1, &m_vertBuffer);
        }
        glBindBuffer(GL_ARRAY_BUFFER, m_vertBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * vertexCount, verts, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
        
        if(!m_indexBuffer) {
            glGenBuffers(1, &m_indexBuffer);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * vertexCount, indices, GL_STATIC_DRAW);
        
        glUniform4f(glGetUniformLocation(s->GetProgram(), "u_color"), color.r, color.g, color.b, 0.5f);
        glUniformMatrix4fv(glGetUniformLocation(s->GetProgram(), "u_pMatrix"), 
                           1, false, cam->GetMatrix().GetData());
        glUniformMatrix4fv(glGetUniformLocation(s->GetProgram(), "u_mvMatrix"),
                           1, false, Matrix4::Identity().GetData());
        
        glDrawElements(GL_TRIANGLE_FAN, vertexCount, GL_UNSIGNED_SHORT, 0);
        delete verts;
        delete indices;
    }
    
    virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
        GLint vertexCount = 36;
        glColor4f(color.r, color.g, color.b, 1.0f);
        glUseProgram(0);
        glEnableClientState(GL_VERTEX_ARRAY);
        GLfloat* verts = new GLfloat[vertexCount * 3];
        GLushort* indices = new GLushort[vertexCount];
        for(int i = 0; i < vertexCount; i++) {
            int base = i * 3;
            verts[base + 0] = (GLfloat)(center.x + radius * cos(i * 10.0f * M_PI / 180.0f));
            verts[base + 1] = (GLfloat)(center.y + radius * sin(i * 10.0f * M_PI / 180.0f));
            verts[base + 2] = 0.0f;
            indices[i] = i;
        }
        glVertexPointer(3, GL_FLOAT, 0, verts);
        glDrawElements(GL_LINE_LOOP, vertexCount, GL_UNSIGNED_SHORT, indices);
    }
    
    virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
        GLint vertexCount = 36;
        glColor4f(color.r, color.g, color.b, 1.0f);
        glUseProgram(0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnable(GL_BLEND);
        GLfloat* verts = new GLfloat[vertexCount * 3];
        GLushort* indices = new GLushort[vertexCount];
        for(int i = 0; i < vertexCount; i++) {
            int base = i * 3;
            verts[base + 0] = (GLfloat)(center.x + radius * cos(i * 10.0f * M_PI / 180.0f));
            verts[base + 1] = (GLfloat)(center.y + radius * sin(i * 10.0f * M_PI / 180.0f));
            verts[base + 2] = 0.0f;
            indices[i] = i;
        }
        glVertexPointer(3, GL_FLOAT, 0, verts);
        glDrawElements(GL_TRIANGLE_FAN, vertexCount, GL_UNSIGNED_SHORT, indices);
        
    }
    
    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
        glColor4f(color.r, color.g, color.b, 1.0f);
        glEnableClientState(GL_VERTEX_ARRAY);
        glUseProgram(0);
        GLfloat verts[] = {
            p1.x, p1.y, 0.0f,
            p2.x, p2.y, 0.0f
        };
        GLushort indices[] = {
            0, 1
        };
        glVertexPointer(3, GL_FLOAT, 0, verts);
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, indices);
    }
    
    virtual void DrawTransform(const b2Transform& xf) {
        glUseProgram(0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glColor4f(1, 1, 1, 1);
        GLfloat verts[] = {
            xf.p.x,                       xf.p.y, 0.0f,
            (xf.p.x + xf.q.GetXAxis().x), (xf.p.y + xf.q.GetXAxis().y), 0.0f,
            xf.p.x,                       xf.p.y, 0.0f,
            (xf.p.x + xf.q.GetYAxis().x), (xf.p.y + xf.q.GetYAxis().y), 0.0f
        };
        GLushort indices[] = {
            0, 1, 2, 3
        };
        glVertexPointer(3, GL_FLOAT, 0, verts);
        glDrawElements(GL_LINES, 4, GL_UNSIGNED_SHORT, indices);
    }
private:
    GLuint m_vertBuffer, m_indexBuffer;
};

class PSContactListner : public b2ContactListener {
    virtual void BeginContact(b2Contact* contact) {
        if(!contact->IsTouching()) {
            return;
        }
        b2Body* a = contact->GetFixtureA()->GetBody();
        b2Body* b = contact->GetFixtureB()->GetBody();
        Collider* ac = (Collider*)a->GetUserData();
        Collider* bc = (Collider*)b->GetUserData();
        if(!ac->HandleCollision(contact, bc)) {
            bc->HandleCollision(contact, ac);
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
        bodyDef.type = toRegister->GetType();
        b2Body* toReturn = m_world->CreateBody(&bodyDef);
        b2Shape* shape = toRegister->GetBodyShape();
        toReturn->SetTransform(b2Vec2(1, 1), 0);
        b2Fixture* fix = toReturn->CreateFixture(shape, toRegister->GetDensity());
        fix->SetFriction(toRegister->GetFriction());
        fix->SetRestitution(toRegister->GetRestitution());
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

void PhysicsSystem::ToggleDebugDrawFlag(GLuint flag, GLboolean state) {
    if(state) {
        m_debug->AppendFlags(flag);
    }
    else {
        m_debug->ClearFlags(flag);
    }
}

void PhysicsSystem::SetGravity(GLfloat x, GLfloat y) {
    m_world->SetGravity(b2Vec2(x, y));
}

b2Vec2 PhysicsSystem::GetGravity() {
    return m_world->GetGravity();
}

void PhysicsSystem::Initialize() {
    m_world = new b2World(b2Vec2(0.0, 0.0));
    m_world->SetAllowSleeping(true);
    m_debug = new PSDebugDraw();
    m_world->SetDebugDraw(m_debug);
    m_world->SetContactListener(new PSContactListner());
}

PhysicsSystem::~PhysicsSystem() {
    
}
