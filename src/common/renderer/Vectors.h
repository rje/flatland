//
//  Vector3.h
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Vectors_h
#define flatland_Vectors_h

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>

typedef struct Vector2 {
    GLfloat x, y;
} Vector2;

typedef struct Vector3 {
    GLfloat x, y, z;
} Vector3;

typedef struct Vector4 {
    GLfloat x, y, z, w;
} Vector4;

#endif
