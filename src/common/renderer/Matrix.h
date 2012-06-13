//
//  Matrix.h
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Matrix_h
#define flatland_Matrix_h

#include "Vectors.h"

class Matrix4 {
public:
    Matrix4() {
        
    }
    virtual ~Matrix4() {
        
    }
    
    static Matrix4 Identity() {
        Matrix4 toReturn;
        toReturn.m_data[0] = 1;
        toReturn.m_data[1] = 0;
        toReturn.m_data[2] = 0;
        toReturn.m_data[3] = 0;
        toReturn.m_data[4] = 0;
        toReturn.m_data[5] = 1;
        toReturn.m_data[6] = 0;
        toReturn.m_data[7] = 0;
        toReturn.m_data[8] = 0;
        toReturn.m_data[9] = 0;
        toReturn.m_data[10] = 1;
        toReturn.m_data[11] = 0;
        toReturn.m_data[12] = 0;
        toReturn.m_data[13] = 0;
        toReturn.m_data[14] = 0;
        toReturn.m_data[15] = 1;
        return toReturn;
    }
    static Matrix4 Translate(Vector3& trans) {
        Matrix4 toReturn = Matrix4::Identity();
        toReturn.m_data[12] = trans.x;
        toReturn.m_data[13] = trans.y;
        toReturn.m_data[14] = trans.z;
        return toReturn;
    }
    static Matrix4 Ortho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far) {
        Matrix4 toReturn;
        GLfloat rl = (right - left);
        GLfloat tb = (top - bottom);
        GLfloat fn = (far - near);
        toReturn.m_data[0] = 2 / rl;
        toReturn.m_data[1] = 0;
        toReturn.m_data[2] = 0;
        toReturn.m_data[3] = 0;
        toReturn.m_data[4] = 0;
        toReturn.m_data[5] = 2 / tb;
        toReturn.m_data[6] = 0;
        toReturn.m_data[7] = 0;
        toReturn.m_data[8] = 0;
        toReturn.m_data[9] = 0;
        toReturn.m_data[10] = -2 / fn;
        toReturn.m_data[11] = 0;
        toReturn.m_data[12] = -(left + right) / rl;
        toReturn.m_data[13] = -(top + bottom) / tb;
        toReturn.m_data[14] = -(far + near) / fn;
        toReturn.m_data[15] = 1;
        return toReturn;
    }
    static Matrix4 Perspective(GLfloat fovy, GLfloat aspect, GLfloat near, GLfloat far) {
        Matrix4 toReturn;
        return toReturn;
    }
    
    GLfloat* GetData() {
        return m_data;
    }
protected:
    GLfloat m_data[16];
};


#endif
