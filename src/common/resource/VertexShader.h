//
//  VertexShader.h
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_VertexShader_h
#define flatland_VertexShader_h

#include "flatland_common.h"

#include <v8.h>
using namespace v8;

class VertexShader;

typedef vector<VertexShader*> VertexShaderVector;
typedef VertexShaderVector::iterator VertexShaderVectorIter;

class VertexShader {
public:
    VertexShader();
    virtual ~VertexShader();
    
    GLuint GetShaderID();
    void SetSource(string source);
    void Compile();
    
    virtual void SetWrappedObject(Persistent<Object>& handle);
    virtual Persistent<Object> GetWrappedObject();
    
private:
    GLuint m_shaderID;
    string m_src;
    Persistent<Object> m_wrappedObj;
};


#endif
