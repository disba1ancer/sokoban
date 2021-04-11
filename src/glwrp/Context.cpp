/*
 * Context.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: disba1ancer
 */

#include <glwrp/Context.h>
#include <glwrp/gl31.h>
#include <sokoban/Terminal.h>
#include <stdexcept>

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <commctrl.h>
#include <cstring>

namespace {

	const int pixelFormatAtributes[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0, 0
	};

	const int contextAtributes[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 1,
		//WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
		0, 0
	};

	struct DataStruct {
		HGLRC hglrc;
		HDC hdc;
	};

	struct TerminalSystemData {
		HWND hWnd;
		HDC hdc;
	};
}

namespace gl {

Context::Context(const void* winid) : context(nullptr) {
	if (winid) {
		int format;
		{
			sokoban::Terminal term;
			auto wData = reinterpret_cast<const TerminalSystemData*>(term.getSysDepId());
			//auto wData = reinterpret_cast<const TerminalSystemData*>(winid);
			PIXELFORMATDESCRIPTOR pfd;
			std::memset(&pfd, 0, sizeof(pfd));
			pfd.nSize = sizeof(pfd);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 24;
			pfd.cStencilBits = 8;
			pfd.iLayerType = PFD_MAIN_PLANE;
			format = ChoosePixelFormat(wData->hdc, &pfd);
			DescribePixelFormat(wData->hdc, format, sizeof(pfd), &pfd);
			if ((pfd.dwFlags & PFD_GENERIC_FORMAT) && !(pfd.dwFlags & PFD_GENERIC_ACCELERATED)) {
				throw std::runtime_error("Pixel format not accelerated");
			}
			SetPixelFormat(wData->hdc, format, &pfd);
			HGLRC glrc = wglCreateContext(wData->hdc);
			if (!glrc) {
				throw std::runtime_error("Couldn't create dummy OpenGL context");
			}
			//this->context = new DataStruct{glrc, wData->hdc};
			wglMakeCurrent(wData->hdc, glrc);
			wglChoosePixelFormatARB.load();
			wglCreateContextAttribsARB.load();
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(glrc);
		}
		auto wData = reinterpret_cast<const TerminalSystemData*>(winid);
		UINT formatCount;
		wglChoosePixelFormatARB(wData->hdc, pixelFormatAtributes, nullptr, 1, &format, &formatCount);
		SetPixelFormat(wData->hdc, format, nullptr);
		HGLRC context = wglCreateContextAttribsARB(wData->hdc, 0, contextAtributes);
		this->context = new DataStruct{context, wData->hdc};
		wglMakeCurrent(wData->hdc, context);
	}
}

Context::~Context() {
	if (context) {
		auto context = reinterpret_cast<DataStruct*>(this->context);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(context->hglrc);
		delete context;
	}
}

Context::Context(Context&& other) : context(other.context) {
	other.context = nullptr;
}

Context& Context::operator =(Context&& other) {
	context = other.context;
	other.context = nullptr;
	return *this;
}

} /* namespace gl */
