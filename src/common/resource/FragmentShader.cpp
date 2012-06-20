//
//  FragmentShader.cpp
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "FragmentShader.h"
#include "FragmentShaderBindings.h"

FragmentShader::FragmentShader() : m_shaderID(0) {
    
}

FragmentShader::~FragmentShader() {
    
}

GLuint FragmentShader::GetShaderID() {
    return m_shaderID;
}

void FragmentShader::SetSource(string source) {
    m_src = source;
}

void FragmentShader::Compile() {
    m_shaderID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* shaderSource[1] = { m_src.c_str() };
    glShaderSource(m_shaderID, 1, shaderSource, NULL);
    glCompileShader(m_shaderID);
    GLint compiled;
    glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &compiled);
    if(!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(m_shaderID, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 1) {
            char* infoLog = new char[infoLen];
            glGetShaderInfoLog(m_shaderID, infoLen, NULL, infoLog);
            printf("ERROR COMPILING FRAGMENT SHADER: %s", infoLog);
            delete[] infoLog;
        }
    }
}

void FragmentShader::SetWrappedObject(Persistent<Object>& handle) {
    m_wrappedObj = handle;
}

Persistent<Object> FragmentShader::GetWrappedObject() {
    HandleScope handle_scope;
    if(m_wrappedObj.IsEmpty()) {
        m_wrappedObj = Persistent<Object>::New(FragmentShaderBindings_WrapFragmentShader(this)->ToObject());
    }
    return m_wrappedObj;
}
