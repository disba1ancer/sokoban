/*
 * util.cpp
 *
 *  Created on: Jul 23, 2017
 *      Author: Anton
 */

#include <platform/win32.h>
#include <cmath>
#include <sokoban/Game.h>

#include "util.h"

namespace util {

int doSystemHandlers(sokoban::Game* game) {
	MSG msg;

	while (true) {
		if (PeekMessage(&msg, 0, 0 ,0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else if (game) {
			game->onLoopStep();
		}
	}

	return msg.wParam;
}

void softTerminate(int returnValue) {
	PostQuitMessage(returnValue);
}

/*matrixmath::matrix4f projectionMatrix(float left, float right, float bottom,
		float top, float zNear, float zFar) {
	float dblZNear = 2 * zNear;
	float rtLtDiff = right - left;
	float tpBmDiff = top - bottom;
	float frNrDiff = zFar - zNear;
	float a = (right + left) / rtLtDiff;
	float b = (top + bottom) / tpBmDiff;
	float c = (zFar + zNear) / frNrDiff;
	float d = dblZNear * zFar / frNrDiff;
	return matrixmath::matrix4f{ {
		{dblZNear / rtLtDiff, 0, a, 0},
		{0, dblZNear / tpBmDiff, b, 0},
		{0, 0, c, d},
		{0, 0, -1, 0}
	} };
}

matrixmath::matrix4f orthoMatrix(float left, float right, float bottom,
		float top, float zNear, float zFar) {
	float rtLtDiff = right - left;
	float tpBmDiff = top - bottom;
	float frNrDiff = zFar - zNear;
	float tx = -(right + left) / rtLtDiff;
	float ty = -(top + bottom) / tpBmDiff;
	float tz = -(zFar + zNear) / frNrDiff;
	return matrixmath::matrix4f{ {
		{2 / rtLtDiff, 0, 0, tx},
		{0, 2 / tpBmDiff, 0, ty},
		{0, 0, 2 / frNrDiff, tz},
		{0, 0, 0, 0}
	} };
}

matrixmath::matrix4f translateMatrix(float x, float y, float z) {
	return matrixmath::matrix4f{ {
		{1, 0, 0, x},
		{0, 1, 0, y},
		{0, 0, 1, z},
		{0, 0, 0, 1}
	} };
}

matrixmath::matrix4f scaleMatrix(float x, float y, float z) {
	return matrixmath::matrix4f{ {
		{x, 0, 0, 0},
		{0, y, 0, 0},
		{0, 0, z, 0},
		{0, 0, 0, 1}
	} };
}

matrixmath::matrix4f rotateXMatrix(float x) {
	using namespace std;
	return matrixmath::matrix4f{ {
		{1, 0,                 0,                0},
		{0, cos(degToRad(x)),  sin(degToRad(x)), 0},
		{0, -sin(degToRad(x)), cos(degToRad(x)), 0},
		{0, 0,                 0,                1}
	} };
}

matrixmath::matrix4f rotateYMatrix(float y) {
	using namespace std;
	return matrixmath::matrix4f{ {
		{cos(degToRad(y)),  0, sin(degToRad(y)), 0},
		{0,                 1, 0,                0},
		{-sin(degToRad(y)), 0, cos(degToRad(y)), 0},
		{0,                 0, 0,                1}
	} };
}*/

int standartUILoop() {
	MSG msg;
	BOOL result;
	while ( (result = GetMessage(&msg, 0, 0, 0)) ) {
		if (result == -1) return -1;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

/*matrixmath::matrix4f rotateZMatrix(float z) {
	using namespace std;
	return matrixmath::matrix4f{ {
		{cos(degToRad(z)),  sin(degToRad(z)), 0, 0},
		{-sin(degToRad(z)), cos(degToRad(z)), 0, 0},
		{0,                 0,                1, 0},
		{0,                 0,                0, 1}
	} };
}*/

} /* namespace util */
