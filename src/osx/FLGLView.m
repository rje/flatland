//
//  FLGLView.m
//  flatland
//
//  Created by Ryan Evans on 5/22/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#import "FLGLView.h"
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
@implementation FLGLView

+ (NSOpenGLPixelFormat*) basicPixelFormat
{
    NSOpenGLPixelFormatAttribute attributes [] = {
        NSOpenGLPFAWindow,
        NSOpenGLPFADoubleBuffer,    // double buffered
        NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute)16, // 16 bit depth buffer
        (NSOpenGLPixelFormatAttribute)nil
    };
    return [[[NSOpenGLPixelFormat alloc] initWithAttributes:attributes] autorelease];
}

-(id) initWithFrame: (NSRect) frameRect
{
    NSOpenGLPixelFormat * pf = [FLGLView basicPixelFormat];
    
    self = [super initWithFrame: frameRect pixelFormat: pf];
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    glViewport(0, 0, self.bounds.size.width, self.bounds.size.height);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.85f, 0.35f);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(  0.0,  0.6, 0.0);
        glVertex3f( -0.2, -0.3, 0.0);
        glVertex3f(  0.2, -0.3 ,0.0);
    }
    glEnd();
    glFlush();
    GLenum err = glGetError();
    NSLog(@"GL Error 0x%x", err);
}

- (void)update {
    [super update];
}

@end
