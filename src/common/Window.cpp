//
//  Window_mac.mm
//  flatland
//
//  Created by Ryan Evans on 5/22/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Window.h"
#include <stdio.h>
#include <v8.h>
#include <SDL/SDL.h>

void Window::Test() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.85f, 0.35f);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(  0.0,  0.6, 0.0);
        glVertex3f( -0.2, -0.3, 0.0);
        glVertex3f(  0.2, -0.3 ,0.0);
    }
    glEnd();
    this->Flush();
}


Window::Window() : m_window(NULL) {
    printf("Creating window\n");
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    m_window = SDL_CreateWindow("flatland", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 
                                       SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    m_glContext = SDL_GL_CreateContext(m_window);
    SDL_GL_MakeCurrent(m_window, m_glContext);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    this->Test();
    SDL_ShowWindow(m_window);
    m_isDirty = WINDOW_NONE;
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
    m_width = x;
    m_height = y;
    m_isDirty |= WINDOW_SIZE;
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

void Window::HandleUpdates() {
    if(m_isDirty && WINDOW_SIZE) {
        SDL_SetWindowSize(m_window, m_width, m_height);
        glViewport(0, 0, m_width, m_height);
        m_isDirty &= !WINDOW_SIZE;
    }
    if(m_isDirty && WINDOW_CLEAR_COLOR) {
        glClearColor(m_clearR, m_clearG, m_clearB, m_clearA);
        m_isDirty &= !WINDOW_CLEAR_COLOR;
    }
}