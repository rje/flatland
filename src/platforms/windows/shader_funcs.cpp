
#include "shader_funcs.h"

PFNGLGENBUFFERSPROC					glGenBuffers = NULL;
PFNGLBINDBUFFERPROC					glBindBuffer = NULL;
PFNGLVERTEXATTRIBPOINTERPROC		glVertexAttribPointer = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC	glEnableVertexAttribArray = NULL;
PFNGLUNIFORMMATRIX4FVPROC			glUniformMatrix4fv = NULL;
PFNGLUNIFORM4FPROC					glUniform4f = NULL;
PFNGLGETUNIFORMLOCATIONPROC			glGetUniformLocation = NULL;
PFNGLUNIFORM1FPROC					glUniform1f = NULL;
PFNGLUNIFORM1IPROC					glUniform1i = NULL;
PFNGLUSEPROGRAMPROC					glUseProgram = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC	glDisableVertexAttribArray = NULL;
PFNGLSHADERSOURCEPROC				glShaderSource = NULL;
PFNGLGETSHADERIVPROC				glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC			glGetShaderInfoLog = NULL;
PFNGLCREATESHADERPROC				glCreateShader = NULL;
PFNGLCOMPILESHADERPROC				glCompileShader = NULL;
PFNGLCREATEPROGRAMPROC				glCreateProgram = NULL;
PFNGLLINKPROGRAMPROC				glLinkProgram = NULL;
PFNGLGETPROGRAMINFOLOGPROC			glGetProgramInfoLog = NULL;
PFNGLATTACHSHADERPROC				glAttachShader = NULL;
PFNGLGETPROGRAMIVPROC				glGetProgramiv = NULL;
PFNGLBINDATTRIBLOCATIONPROC			glBindAttribLocation = NULL;
PFNGLBUFFERDATAPROC					glBufferData = NULL;

void flatland_setupRequiredGLCalls() {
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
}