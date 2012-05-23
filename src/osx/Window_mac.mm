//
//  Window_mac.mm
//  flatland
//
//  Created by Ryan Evans on 5/22/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Window.h"
#include <stdio.h>
#import "FLGLView.h"
#import "AppDelegate.h"
#import <v8.h>

GLfloat titleBarHeight() {
    NSRect frame = NSMakeRect(0, 0, 100, 100);
    NSRect contentRect = [NSWindow contentRectForFrameRect:frame styleMask:NSTitledWindowMask];
    
    return frame.size.height - contentRect.size.height;    
}

Window::Window() {
    printf("Creating window\n");
    AppDelegate* delegate = (AppDelegate*)[NSApplication sharedApplication].delegate;
    m_window = delegate.window;
    m_glview = delegate.glView;
}

Window::~Window() {
    
}

Window* Window::GetWindow() {
    static Window* sm_window = new Window();
    return sm_window;
}

void Window::SetSize(GLfloat x, GLfloat y) { 
    NSRect frame = m_window.frame;
    [m_window setFrame:NSMakeRect(frame.origin.x, frame.origin.y, x, y + titleBarHeight()) display:NO animate:NO];
}

void Window::Flush() {
    glFlush();
    
}

void Window::SetClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a) {
    glClearColor(r, g, b, a);
    
}