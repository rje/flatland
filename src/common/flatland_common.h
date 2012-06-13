//
//  flatland_common.h
//  flatland
//
//  Created by Ryan Evans on 6/8/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_flatland_common_h
#define flatland_flatland_common_h

#	define GL_GLEXT_PROTOTYPES 1
#include <string>
#include <vector>
#include <map>
#include <SDL_opengl.h>
#if defined(linux) || defined(__linux)
#	include <GL/gl.h>
#	include <GL/glext.h>
#endif

using std::string;
using std::vector;
using std::map;

typedef vector<string> StringVector;
typedef StringVector::iterator StringVectorIter;


#endif
