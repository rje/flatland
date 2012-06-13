//
//  VertexShader.cpp
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "VertexShader.h"
#include "VertexShaderBindings.h"

VertexShader::VertexShader() : m_shaderID(NULL) {
    
}

VertexShader::~VertexShader() {
    
}

GLuint VertexShader::GetShaderID() {
    return m_shaderID;
}

void VertexShader::SetSource(string source) {
    m_src = source;
}

void VertexShader::Compile() {
    m_shaderID = glCreateShader(GL_VERTEX_SHADER);
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
            printf("ERROR COMPILING VERTEX SHADER: %s", infoLog);
            delete[] infoLog;
        }
    }
}

void VertexShader::SetWrappedObject(Persistent<Object>& handle) {
    m_wrappedObj = handle;
}

Persistent<Object> VertexShader::GetWrappedObject() {
    HandleScope handle_scope;
    if(m_wrappedObj.IsEmpty()) {
        m_wrappedObj = Persistent<Object>::New(VertexShaderBindings_WrapVertexShader(this)->ToObject());
    }
    return m_wrappedObj;
}