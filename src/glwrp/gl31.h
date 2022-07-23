/*
 * gl3.h
 *
 *  Created on: Sep 16, 2018
 *      Author: disba1ancer
 */

#ifndef GL31_H_
#define GL31_H_

#include <platform/win32.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wglext.h>
#include <glwrp/GLImportedFunction.h>

namespace gl {

	IMPORT_GL_FUNCTION(wglChoosePixelFormatARB, WGLCHOOSEPIXELFORMATARB);
	IMPORT_GL_FUNCTION(wglCreateContextAttribsARB, WGLCREATECONTEXTATTRIBSARB);
	IMPORT_GL_FUNCTION(glGenVertexArrays, GLGENVERTEXARRAYS);
	IMPORT_GL_FUNCTION(glBindVertexArray, GLBINDVERTEXARRAY);
	IMPORT_GL_FUNCTION(glDeleteVertexArrays, GLDELETEVERTEXARRAYS);
	IMPORT_GL_FUNCTION(glGenBuffers, GLGENBUFFERS);
	IMPORT_GL_FUNCTION(glBindBuffer, GLBINDBUFFER);
	IMPORT_GL_FUNCTION(glBufferData, GLBUFFERDATA);
	IMPORT_GL_FUNCTION(glDeleteBuffers, GLDELETEBUFFERS);
	IMPORT_GL_FUNCTION(glEnableVertexAttribArray, GLENABLEVERTEXATTRIBARRAY);
	IMPORT_GL_FUNCTION(glVertexAttribPointer, GLVERTEXATTRIBPOINTER);
	IMPORT_GL_FUNCTION(glDisableVertexAttribArray, GLDISABLEVERTEXATTRIBARRAY);
	IMPORT_GL_FUNCTION(glCreateShader, GLCREATESHADER);
	IMPORT_GL_FUNCTION(glShaderSource, GLSHADERSOURCE);
	IMPORT_GL_FUNCTION(glCompileShader, GLCOMPILESHADER);
	IMPORT_GL_FUNCTION(glCreateProgram, GLCREATEPROGRAM);
	IMPORT_GL_FUNCTION(glDeleteProgram, GLDELETEPROGRAM);
	IMPORT_GL_FUNCTION(glAttachShader, GLATTACHSHADER);
	IMPORT_GL_FUNCTION(glLinkProgram, GLLINKPROGRAM);
	IMPORT_GL_FUNCTION(glDeleteShader, GLDELETESHADER);
	IMPORT_GL_FUNCTION(glUseProgram, GLUSEPROGRAM);
	IMPORT_GL_FUNCTION(glGetUniformLocation, GLGETUNIFORMLOCATION);
	IMPORT_GL_FUNCTION(glUniformMatrix4fv, GLUNIFORMMATRIX4FV);
	IMPORT_GL_FUNCTION(glGenFramebuffers, GLGENFRAMEBUFFERS);
	IMPORT_GL_FUNCTION(glFramebufferTexture, GLFRAMEBUFFERTEXTURE);
	IMPORT_GL_FUNCTION(glBindFramebuffer, GLBINDFRAMEBUFFER);
	IMPORT_GL_FUNCTION(glBlitFramebuffer, GLBLITFRAMEBUFFER);
	IMPORT_GL_FUNCTION(glFramebufferRenderbuffer, GLFRAMEBUFFERRENDERBUFFER);
	IMPORT_GL_FUNCTION(glGetUniformfv, GLGETUNIFORMFV);
	IMPORT_GL_FUNCTION(glActiveTexture, GLACTIVETEXTURE);
	IMPORT_GL_FUNCTION(glGetAttribLocation, GLGETATTRIBLOCATION);
	IMPORT_GL_FUNCTION(glUniform1i, GLUNIFORM1I);
	IMPORT_GL_FUNCTION(glTexImage3D, GLTEXIMAGE3D);
	IMPORT_GL_FUNCTION(glGetShaderiv, GLGETSHADERIV);
	IMPORT_GL_FUNCTION(glGetShaderInfoLog, GLGETSHADERINFOLOG);
	IMPORT_GL_FUNCTION(glGetProgramiv, GLGETPROGRAMIV);
	IMPORT_GL_FUNCTION(glGetProgramInfoLog, GLGETPROGRAMINFOLOG);
	IMPORT_GL_FUNCTION(glBufferSubData, GLBUFFERSUBDATA);
	IMPORT_GL_FUNCTION(wglSwapIntervalEXT, WGLSWAPINTERVALEXT);

	using ::wglCreateContext;
	using ::wglMakeCurrent;
	using ::glDrawArrays;
	using ::glDrawElements;
	using ::glClearColor;
	using ::glClear;
	using ::glFinish;
	using ::glFlush;
	using ::glViewport;
	using ::glGenTextures;
	using ::glDeleteTextures;
	using ::glBindTexture;
	using ::glTexParameteri;
	using ::glTexImage2D;
	using ::glEnable;
	using ::glBlendFunc;

	class Context;

	void SwapBuffers(const void* sysID);
	void SwapBuffers(Context& context);

} /* namespace gl */

#endif /* GL31_H_ */
