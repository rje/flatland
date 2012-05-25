//
//  Window.h
//  flatland
//
//  Created by Ryan Evans on 5/22/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Window_h
#define flatland_Window_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <v8.h>

class Renderer;

enum WindowDirtyMask {
    WINDOW_NONE = 0,
    WINDOW_SIZE,
    WINDOW_CLEAR_COLOR
};

class Window {
public:
    static Window* GetWindow();
    virtual void SetSize(GLfloat x, GLfloat y);
    virtual void Flush();
    virtual void SetClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
    virtual void HandleUpdates();
    
    virtual Renderer* GetRenderer();
private:
    Window();
    virtual ~Window();
    
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    GLfloat m_width, m_height;
    GLuint m_isDirty;
    GLclampf m_clearR, m_clearG, m_clearB, m_clearA;
    Renderer* m_renderer;
};


#endif
