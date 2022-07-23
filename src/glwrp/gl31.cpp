/*
 * gl31.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: disba1ancer
 */

#include <glwrp/gl31.h>
#include "Context.h"

namespace {

	struct ContextDataStruct {
		HGLRC hglrc;
		HDC hdc;
	};

	struct TerminalSystemData {
		HWND hWnd;
		HDC hdc;
	};

}

namespace gl {

	IMPLEMENT_GL_FUNCTION(wglChoosePixelFormatARB, WGLCHOOSEPIXELFORMATARB);
	IMPLEMENT_GL_FUNCTION(wglCreateContextAttribsARB, WGLCREATECONTEXTATTRIBSARB);
	IMPLEMENT_GL_FUNCTION(glGenVertexArrays, GLGENVERTEXARRAYS);
	IMPLEMENT_GL_FUNCTION(glBindVertexArray, GLBINDVERTEXARRAY);
	IMPLEMENT_GL_FUNCTION(glDeleteVertexArrays, GLDELETEVERTEXARRAYS);
	IMPLEMENT_GL_FUNCTION(glGenBuffers, GLGENBUFFERS);
	IMPLEMENT_GL_FUNCTION(glBindBuffer, GLBINDBUFFER);
	IMPLEMENT_GL_FUNCTION(glBufferData, GLBUFFERDATA);
	IMPLEMENT_GL_FUNCTION(glDeleteBuffers, GLDELETEBUFFERS);
	IMPLEMENT_GL_FUNCTION(glEnableVertexAttribArray, GLENABLEVERTEXATTRIBARRAY);
	IMPLEMENT_GL_FUNCTION(glVertexAttribPointer, GLVERTEXATTRIBPOINTER);
	IMPLEMENT_GL_FUNCTION(glDisableVertexAttribArray, GLDISABLEVERTEXATTRIBARRAY);
	IMPLEMENT_GL_FUNCTION(glCreateShader, GLCREATESHADER);
	IMPLEMENT_GL_FUNCTION(glShaderSource, GLSHADERSOURCE);
	IMPLEMENT_GL_FUNCTION(glCompileShader, GLCOMPILESHADER);
	IMPLEMENT_GL_FUNCTION(glCreateProgram, GLCREATEPROGRAM);
	IMPLEMENT_GL_FUNCTION(glDeleteProgram, GLDELETEPROGRAM);
	IMPLEMENT_GL_FUNCTION(glAttachShader, GLATTACHSHADER);
	IMPLEMENT_GL_FUNCTION(glLinkProgram, GLLINKPROGRAM);
	IMPLEMENT_GL_FUNCTION(glDeleteShader, GLDELETESHADER);
	IMPLEMENT_GL_FUNCTION(glUseProgram, GLUSEPROGRAM);
	IMPLEMENT_GL_FUNCTION(glGetUniformLocation, GLGETUNIFORMLOCATION);
	IMPLEMENT_GL_FUNCTION(glUniformMatrix4fv, GLUNIFORMMATRIX4FV);
	IMPLEMENT_GL_FUNCTION(glGenFramebuffers, GLGENFRAMEBUFFERS);
	IMPLEMENT_GL_FUNCTION(glFramebufferTexture, GLFRAMEBUFFERTEXTURE);
	IMPLEMENT_GL_FUNCTION(glBindFramebuffer, GLBINDFRAMEBUFFER);
	IMPLEMENT_GL_FUNCTION(glBlitFramebuffer, GLBLITFRAMEBUFFER);
	IMPLEMENT_GL_FUNCTION(glFramebufferRenderbuffer, GLFRAMEBUFFERRENDERBUFFER);
	IMPLEMENT_GL_FUNCTION(glGetUniformfv, GLGETUNIFORMFV);
	IMPLEMENT_GL_FUNCTION(glActiveTexture, GLACTIVETEXTURE);
	IMPLEMENT_GL_FUNCTION(glGetAttribLocation, GLGETATTRIBLOCATION);
	IMPLEMENT_GL_FUNCTION(glUniform1i, GLUNIFORM1I);
	IMPLEMENT_GL_FUNCTION(glTexImage3D, GLTEXIMAGE3D);
	IMPLEMENT_GL_FUNCTION(glGetShaderiv, GLGETSHADERIV);
	IMPLEMENT_GL_FUNCTION(glGetShaderInfoLog, GLGETSHADERINFOLOG);
	IMPLEMENT_GL_FUNCTION(glGetProgramiv, GLGETPROGRAMIV);
	IMPLEMENT_GL_FUNCTION(glGetProgramInfoLog, GLGETPROGRAMINFOLOG);
	IMPLEMENT_GL_FUNCTION(glBufferSubData, GLBUFFERSUBDATA);
	IMPLEMENT_GL_FUNCTION(wglSwapIntervalEXT, WGLSWAPINTERVALEXT);

	void SwapBuffers(const void* sysID) {
		auto sysData = reinterpret_cast<const TerminalSystemData*>(sysID);
		::SwapBuffers(sysData->hdc);
	}

	void SwapBuffers(Context& context) {
		auto contData = reinterpret_cast<const ContextDataStruct*>(context.context);
		::SwapBuffers(contData->hdc);
	}

} /* namespace gl */
