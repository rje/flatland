//
//  Shader.h
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Shader_h
#define flatland_Shader_h

#include "flatland_common.h"
#include "FragmentShader.h"
#include "VertexShader.h"

#include <v8.h>
using namespace v8;

class Shader {
public:
    Shader();
    virtual ~Shader();
    
    void AddFragmentShader(FragmentShader* toAdd);
    void AddVertexShader(VertexShader* toAdd);
    void LinkShader();
    void UseShader();
    
    GLuint GetProgram();
    
    static void CreateDefaultShaders();
    static Shader* defaultShader;
    static Shader* defaultNoTextureShader;
    
    virtual void SetWrappedObject(Persistent<Object>& handle);
    virtual Persistent<Object> GetWrappedObject();
    
private:
    GLuint m_program;
    FragmentShaderVector m_fragmentShaders;
    VertexShaderVector m_vertexShaders;
    Persistent<Object> m_wrappedObj;
};


#endif
