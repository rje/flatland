//
//  Window.cpp
//  flatland
//
//  Created by Ryan Evans on 5/22/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Window.h"
#include "Renderer.h"
#include <stdio.h>
#include <v8.h>
#include <SDL.h>

#ifdef WIN32
#include "shader_funcs.h"
#endif

Window::Window() : m_window(NULL) {
    printf("Creating window\n");
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    m_window = SDL_CreateWindow("flatland", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 
                                       SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);
    SDL_GL_MakeCurrent(m_window, m_glContext);
#ifdef WIN32
	flatland_setupRequiredGLCalls();
#endif
    glClearColor(0, 0, 0, 0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    SDL_ShowWindow(m_window);
    m_isDirty = WINDOW_NONE;
    m_canResize = true;
    m_renderer = new Renderer(this);
}

Window::~Window() {
    if(m_window) {
        SDL_DestroyWindow(this->m_window);
    }
}

Window* Window::GetWindow() {
    static Window* sm_window = new Window();
    return sm_window;
}

void Window::SetSize(GLfloat x, GLfloat y) { 
    if(!m_canResize) {
        return;
    }
    m_width = x;
    m_height = y;
    m_isDirty |= WINDOW_SIZE;
}

GLfloat Window::GetWidth() {
    return m_width;
}

GLfloat Window::GetHeight() {
    return m_height;
}

void Window::Flush() {
    glFlush();
    SDL_GL_SwapWindow(this->m_window);
    
}

void Window::SetClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a) {
    m_clearR = r;
    m_clearG = g;
    m_clearB = b;
    m_clearA = a;
    m_isDirty |= WINDOW_CLEAR_COLOR;
}

void Window::CenterOnScreen() {
    m_isDirty |= WINDOW_CENTER;
}

void Window::HandleUpdates() {
    if(m_isDirty & WINDOW_SIZE) {
        SDL_SetWindowSize(m_window, (int)m_width, (int)m_height);
        glViewport(0, 0, (GLsizei)m_width, (GLsizei)m_height);
        m_isDirty &= ~WINDOW_SIZE;
    }
    if(m_isDirty & WINDOW_CLEAR_COLOR) {
        glClearColor(m_clearR, m_clearG, m_clearB, m_clearA);
        m_isDirty &= ~WINDOW_CLEAR_COLOR;
    }
    if(m_isDirty & WINDOW_CENTER) {
        SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        m_isDirty &= ~WINDOW_CENTER;
    }
}

void Window::SetResizeable(GLboolean canResize) {
    m_canResize = canResize;
}

Renderer* Window::GetRenderer() {
    return m_renderer;
}
