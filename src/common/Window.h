//
//  Window.h
//  flatland
//
//  Created by Ryan Evans on 5/22/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Window_h
#define flatland_Window_h

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <v8.h>

@class NSWindow;
@class FLGLView;

class Window {
public:
    static Window* GetWindow();
    virtual void SetSize(GLfloat x, GLfloat y);
    virtual void Flush();
    virtual void SetClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
private:
    Window();
    virtual ~Window();
    NSWindow* m_window;
    FLGLView* m_glview;
};


#endif
