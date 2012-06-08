//
//  Window.h
//  flatland
//
//  Created by Ryan Evans on 5/22/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Window_h
#define flatland_Window_h

#include <SDL.h>
#include <SDL_opengl.h>

#include <v8.h>

class Renderer;

enum WindowDirtyMask {
    WINDOW_NONE          = 0x0000,
    WINDOW_SIZE          = 0x0001,
    WINDOW_VIEWPORT_SIZE = 0x0002,
    WINDOW_CLEAR_COLOR   = 0x0004,
    WINDOW_CENTER        = 0x0008
};

class Window {
public:
    static Window* GetWindow();
    virtual void SetSize(GLfloat x, GLfloat y);
    virtual void SetViewportSize(GLfloat x, GLfloat y);
    virtual void Flush();
    virtual void SetClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
    virtual void HandleUpdates();
    
    virtual GLfloat GetWidth();
    virtual GLfloat GetHeight();
    
    virtual void SetResizeable(GLboolean canResize);
    virtual void CenterOnScreen();
    
    virtual Renderer* GetRenderer();
private:
    Window();
    virtual ~Window();
    
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    GLfloat m_width, m_height;
    GLuint m_isDirty;
    GLclampf m_clearR, m_clearG, m_clearB, m_clearA;
    GLfloat m_vpWidth, m_vpHeight;
    GLboolean m_canResize;
    Renderer* m_renderer;
};


#endif
