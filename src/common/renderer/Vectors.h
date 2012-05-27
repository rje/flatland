//
//  Vector3.h
//  flatland
//
//  Created by Ryan Evans on 5/23/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Vectors_h
#define flatland_Vectors_h

#include <SDL2/SDL_opengl.h>

typedef struct Vector2 {
    GLfloat x, y;
} Vector2;

typedef struct Vector3 {
    Vector3(GLfloat nx, GLfloat ny, GLfloat nz) : x(nx), y(ny), z(nz) {}    
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    GLfloat x, y, z;
} Vector3;

typedef struct Vector4 {
    GLfloat x, y, z, w;
} Vector4;

#endif
