
#ifndef _flatland_shader_funcs_h_
#define _flatland_shader_funcs_h_

#ifdef WIN32

#include "flatland_common.h"

extern void flatland_setupRequiredGLCalls();

extern "C" PFNGLGENBUFFERSPROC					glGenBuffers;
extern "C" PFNGLBINDBUFFERPROC					glBindBuffer;
extern "C" PFNGLVERTEXATTRIBPOINTERPROC			glVertexAttribPointer;
extern "C" PFNGLENABLEVERTEXATTRIBARRAYPROC		glEnableVertexAttribArray;
extern "C" PFNGLUNIFORMMATRIX4FVPROC			glUniformMatrix4fv;
extern "C" PFNGLUNIFORM4FPROC					glUniform4f;
extern "C" PFNGLGETUNIFORMLOCATIONPROC			glGetUniformLocation;
extern "C" PFNGLUNIFORM1FPROC					glUniform1f;
extern "C" PFNGLUNIFORM1IPROC					glUniform1i;
extern "C" PFNGLUSEPROGRAMPROC					glUseProgram;
extern "C" PFNGLDISABLEVERTEXATTRIBARRAYPROC	glDisableVertexAttribArray;
extern "C" PFNGLSHADERSOURCEPROC				glShaderSource;
extern "C" PFNGLGETSHADERIVPROC					glGetShaderiv;
extern "C" PFNGLGETSHADERINFOLOGPROC			glGetShaderInfoLog;
extern "C" PFNGLCREATESHADERPROC				glCreateShader;
extern "C" PFNGLCOMPILESHADERPROC				glCompileShader;
extern "C" PFNGLCREATEPROGRAMPROC				glCreateProgram;
extern "C" PFNGLLINKPROGRAMPROC					glLinkProgram;
extern "C" PFNGLGETPROGRAMINFOLOGPROC			glGetProgramInfoLog;
extern "C" PFNGLATTACHSHADERPROC				glAttachShader;
extern "C" PFNGLGETPROGRAMIVPROC				glGetProgramiv;
extern "C" PFNGLBINDATTRIBLOCATIONPROC			glBindAttribLocation;
extern "C" PFNGLBUFFERDATAPROC					glBufferData;

#endif

#endif
