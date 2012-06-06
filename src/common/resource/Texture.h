//
//  Texture.h
//  flatland
//
//  Created by Ryan Evans on 6/5/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_Texture_h
#define flatland_Texture_h
#include <string>
#include <SDL_opengl.h>
#include <v8.h>
using namespace v8;
using namespace std;

class Texture {
public:
    Texture();
    virtual ~Texture();
    
    void InitWithFile(string& filepath);
    void SetAsActive();
    
    virtual void SetWrappedObject(Persistent<Object>& handle);
    virtual Persistent<Object> GetWrappedObject();
    
protected:
    GLuint m_glTextureID;
    GLuint m_width;
    GLuint m_height;
    GLenum m_targetType;
    GLenum m_pixelFormat;
    GLenum m_dataType;
    Persistent<Object> m_wrappedObj;
};

#endif
