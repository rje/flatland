//
//  Shader.cpp
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "Shader.h"
#include "ShaderBindings.h"

string defaultNoTextureVertShader = string("attribute vec4 position;") +
    "uniform mat4 u_pMatrix;" +
    "uniform mat4 u_mvMatrix;" +
    "" +
    "void main() {" +
    "    gl_Position = u_pMatrix * u_mvMatrix * position;" +
    "}";

string defaultNoTextureFragShader = string("//precision lowp float;\n") +
    "uniform vec4 u_color;" +
    "" +
    "void main() {" +
    "    gl_FragColor = vec4(u_color);" +
    "}";

string defaultVertShader = string("attribute vec4 position;") +
    "attribute vec2 uv;" +
    "uniform mat4 u_pMatrix;" +
    "uniform mat4 u_mvMatrix;" +
    "varying vec2 v_texCoords;" +
    "" +
    "void main() {" +
    "    v_texCoords = uv;" +
    "    gl_Position = u_pMatrix * u_mvMatrix * position;" +
    "}";

string defaultFragShader = string("//precision lowp float;\n") +
    "uniform vec4 u_color;" +
    "uniform sampler2D u_tex;" +
    "varying vec2 v_texCoords;" +
    "" +
    "void main() {" +
    "    gl_FragColor = texture2D(u_tex, v_texCoords) * u_color;" +
    "}";

Shader* Shader::defaultShader = NULL;
Shader* Shader::defaultNoTextureShader = NULL;

Shader::Shader() : m_program(0) {
    
}

Shader::~Shader() {
    
}

void Shader::AddFragmentShader(FragmentShader* toAdd) {
    m_fragmentShaders.push_back(toAdd);
}

void Shader::AddVertexShader(VertexShader* toAdd) {
    m_vertexShaders.push_back(toAdd);
}

void Shader::LinkShader() {
    m_program = glCreateProgram();
    for(VertexShaderVectorIter i = m_vertexShaders.begin(); i != m_vertexShaders.end(); ++i) {
        VertexShader* toAdd = *i;
        glAttachShader(m_program, toAdd->GetShaderID());
    }
    for(FragmentShaderVectorIter i = m_fragmentShaders.begin(); i != m_fragmentShaders.end(); ++i) {
        FragmentShader* toAdd = *i;
        glAttachShader(m_program, toAdd->GetShaderID());
    }
    // FIXME: Make this data driven
    glBindAttribLocation(m_program, 0, "position");
    glLinkProgram(m_program);
    
    GLint linked;
    glGetProgramiv(m_program, GL_LINK_STATUS, &linked);
    if(!linked) {
        GLint infoLen = 0;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 1) {
            char* infoLog = new char[infoLen];
            glGetProgramInfoLog(m_program, infoLen, NULL, infoLog);
            printf("****ERROR LINKING SHADER PROGRAM: %s", infoLog);
            delete [] infoLog;
        }
    }
}

void Shader::UseShader() {
    glUseProgram(m_program);
}

GLuint Shader::GetProgram() {
    return m_program;
}

void Shader::CreateDefaultShaders() {
    Shader* s = new Shader();
    FragmentShader* fs = new FragmentShader();
    fs->SetSource(defaultFragShader);
    fs->Compile();
    s->AddFragmentShader(fs);
    VertexShader* vs = new VertexShader();
    vs->SetSource(defaultVertShader);
    vs->Compile();
    s->AddVertexShader(vs);
    s->LinkShader();
    Shader::defaultShader = s;
    
    s = new Shader();
    fs = new FragmentShader();
    fs->SetSource(defaultNoTextureFragShader);
    fs->Compile();
    s->AddFragmentShader(fs);
    vs = new VertexShader();
    vs->SetSource(defaultNoTextureVertShader);
    vs->Compile();
    s->AddVertexShader(vs);
    s->LinkShader();
    Shader::defaultNoTextureShader = s;
}

void Shader::SetWrappedObject(Persistent<Object>& handle) {
    m_wrappedObj = handle;
}

Persistent<Object> Shader::GetWrappedObject() {
    HandleScope handle_scope;
    if(m_wrappedObj.IsEmpty()) {
        m_wrappedObj = Persistent<Object>::New(ShaderBindings_WrapShader(this)->ToObject());
    }
    return m_wrappedObj;
}
