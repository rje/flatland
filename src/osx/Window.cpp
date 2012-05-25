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


Window::Window() : m_windowSurface(NULL) {
    printf("Creating window\n");
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    m_windowSurface = SDL_CreateWindow("flatland", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 
                                       SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    m_glContext = SDL_GL_CreateContext(m_windowSurface);
    SDL_GL_MakeCurrent(m_windowSurface, m_glContext);
}

Window::~Window() {
    if(m_windowSurface) {
        SDL_DestroyWindow(this->m_windowSurface);
    }
}

Window* Window::GetWindow() {
    static Window* sm_window = new Window();
    return sm_window;
}

void Window::SetSize(GLfloat x, GLfloat y) { 
    SDL_SetWindowSize(this->m_windowSurface, x, y);
    glViewport(0, 0, x, y);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Flush() {
    glFlush();
    SDL_GL_SwapWindow(this->m_windowSurface);
    
}

void Window::SetClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a) {
    glClearColor(r, g, b, a);
    
}