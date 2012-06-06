//
//  TextureBindings.h
//  flatland
//
//  Created by Ryan Evans on 6/6/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_TextureBinding_h
#define flatland_TextureBinding_h

#include <v8.h>
using namespace v8;

class Texture;

void TextureBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global);
Handle<Value> TextureBindings_WrapTexture(Texture* toWrap);

#endif
