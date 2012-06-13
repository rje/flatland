//
//  FragmentShader.h
//  flatland
//
//  Created by Ryan Evans on 6/12/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_FragmentShader_h
#define flatland_FragmentShader_h

#include "flatland_common.h"

#include <v8.h>
using namespace v8;


// FIXME: move the sub shader types to their own files
class FragmentShader;

typedef vector<FragmentShader*> FragmentShaderVector;
typedef FragmentShaderVector::iterator FragmentShaderVectorIter;

class FragmentShader {
public:
    FragmentShader();
    virtual ~FragmentShader();
    
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
