/*
 * Game.cpp
 *
 *  Created on: Oct 4, 2018
 *      Author: disba1ancer
 */

#include <sokoban/Game.h>
#include <util/util.h>
#include <iostream>
#include <util/vec.h>
#include <util/mat.h>
#include <glwrp/ShaderProgramMaker.h>
#include "shaderProgram.h"
#include <cmath>

namespace {
const unsigned char levelData[] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
		0,0,0,0,0,1,0,0,0,0,0,3,2,1,0,0,0,0,0,0,
		0,0,0,0,0,1,0,0,0,0,0,3,2,1,0,0,0,0,0,0,
		0,0,0,0,0,1,0,0,0,0,0,3,2,1,0,0,0,0,0,0,
		0,0,0,0,0,1,4,0,0,0,0,3,2,1,0,0,0,0,0,0,
		0,0,0,0,0,1,0,0,0,0,0,3,2,1,0,0,0,0,0,0,
		0,0,0,0,0,1,0,0,0,0,0,3,2,1,0,0,0,0,0,0,
		0,0,0,0,0,1,2,0,0,0,3,0,0,1,0,0,0,0,0,0,
		0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
}

namespace sokoban {

Game::Game(char* argv[]) :
	level(levelData, 20, 15),
	inGame(false),
	context(window.getSysDepId()),
	textureArray(16, 16, util::ITextureDataProvider::PF_RGBA8, 1),
	textureCrate("assets/textures/crate.bmp"),
	textureTarget("assets/textures/target.bmp"),
	textureWall("assets/textures/wall.bmp"),
	texturePlayer("assets/textures/player.bmp")
{
	while (*argv) {
		args.push_back(*argv);
		++argv;
	}

	std::cout << args.at(0) << std::endl;

	window.makeSizable(false);
	window.resize(640, 480);
	window.attach(Terminal::EVENT_ON_CLOSE, conOnClose);
	window.attach(Terminal::EVENT_ON_REDRAW, conOnRedraw);
	window.attach(Terminal::EVENT_ON_RESIZE, conOnResize);
	window.attach(Terminal::EVENT_ON_KEY_INPUT, conOnKeyInput);
	window.show(Terminal::SHOW);

	makeBuffers();
	initRender();
}

void Game::onLoopStep() {
	window.forceRedraw();
}

void Game::onClose(CloseEvent&) {
	util::softTerminate(0);
}

void Game::onRedraw(RedrawEvent& event)
{
	gl::glClear(GL_COLOR_BUFFER_BIT);

//	if (inGame) {
		makeBuffers();

		gl::glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned), indices.data());
		gl::glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(util::vec2), vertices.data());

		gl::glUniform1i(levelMode, 1);
		gl::glBindVertexArray(levelVAO);
		gl::glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		gl::glUniform1i(levelMode, 0);
		gl::glBindVertexArray(entitiesVAO);
		gl::glDrawElements(GL_TRIANGLES, (level.getCratesCount() + 1) * 6, GL_UNSIGNED_INT, 0);
//	} else {
//	}

	gl::SwapBuffers(context);
	//gl::glFinish();

//	while (!renderCommandQueue.empty()) {
//		renderCommandQueue.front()();
//		renderCommandQueue.pop();
//	}

	auto frameEnd = clock.now();
	std::chrono::duration<float, std::chrono::microseconds::period> frameTime = frameEnd - frameStart;
	std::cout << "\r" << frameTime.count();
	frameStart = frameEnd;
}

Game::~Game() {
	/*window.detach(Terminal::EVENT_ON_CLOSE, OBSERVER(&onClose), this);
	window.detach(Terminal::EVENT_ON_RESIZE, OBSERVER(&onResize), this);*/
	gl::glDeleteTextures(1, &arrayTexture);
	gl::glDeleteTextures(1, &levelTexture);
	gl::glDeleteVertexArrays(1, &entitiesVAO);
	gl::glDeleteVertexArrays(1, &levelVAO);
	gl::glDeleteBuffers(1, &entitiesVertBuf);
	gl::glDeleteBuffers(1, &entitiesElemBuf);
	gl::glDeleteBuffers(1, &quadBuffer);
	gl::glDeleteProgram(program);
}

void Game::onResize(ResizeEvent& event) {
	auto width = event.width;
	auto height = event.height;
	/*if (width < height) {
		gl::glViewport(0, (height - width) / 2, width, width);
	} else {
		gl::glViewport((width - height) / 2, 0, height, height);
	}*/
	gl::glViewport(0, 0, width, height);
}

void Game::makeBuffers() {
	auto count = (level.getCratesCount() + 1);

	indices.clear();
	for (unsigned i = 0; i < count * 4; i += 4) {
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
		indices.push_back(i);
		indices.push_back(i + 2);
		indices.push_back(i + 3);
	}

	using util::vec2;

	auto levelSize = vec2{level.getWidth() / 2.f, level.getHeight() / 2.f};

	vertices.clear();

	auto playerPos = level.getPlayer();
	vertices.push_back(vec2(playerPos) / vec2(levelSize) - 1.f);
	vertices.push_back((vec2(playerPos) + vec2{0, 1}) / vec2(levelSize) - 1.f);
	vertices.push_back((vec2(playerPos) + vec2{1, 1}) / vec2(levelSize) - 1.f);
	vertices.push_back((vec2(playerPos) + vec2{1, 0}) / vec2(levelSize) - 1.f);

	for (unsigned i = 0; i < level.getCratesCount(); ++i) {
		auto crate = level.getCrate(i);
		vertices.push_back(vec2(crate) / vec2(levelSize) - 1.f);
		vertices.push_back((vec2(crate) + vec2{0, 1}) / vec2(levelSize) - 1.f);
		vertices.push_back((vec2(crate) + vec2{1, 1}) / vec2(levelSize) - 1.f);
		vertices.push_back((vec2(crate) + vec2{1, 0}) / vec2(levelSize) - 1.f);
	}
}

void Game::onKeyInput(KeyEvent& event) {
	/*static const char * const states[] = {"UP", "DOWN", "PRESSED"};
	static const char * const keys[] = {"LEFT", "UP", "RIGHT", "DOWN"};*/
	enum Keys {
		LEFT = 37,
		UP,
		RIGHT,
		DOWN,
		ESC = 0x1B,
		KEY_R = 'R'
	};
	/*auto key = std::max(std::min(event.key, decltype(event.key)(DOWN)), decltype(event.key)(LEFT)) - LEFT;
	std::cout << states[event.state] << " " << keys[key] << std::endl;*/
	if (event.state == event.DOWN && event.key == ESC)
		util::softTerminate(0);

	if (event.state == event.DOWN /*&& inGame*/) {
		switch (event.key) {
		case LEFT:
			level.movePlayer(level.LEFT);
			break;
		case UP:
			level.movePlayer(level.UP);
			break;
		case RIGHT:
			level.movePlayer(level.RIGHT);
			break;
		case DOWN:
			level.movePlayer(level.DOWN);
			break;
		case KEY_R:
			level.reset();
			break;
		}
		if (level.checkWinCondition()) level.reset();
	}
}

void Game::initRender()
{
	gl::wglSwapIntervalEXT(1);

	{
		gl::ShaderProgramMaker maker;
		maker.addSource(vertShader, GL_VERTEX_SHADER);
		maker.addSource(fragShader, GL_FRAGMENT_SHADER);
		program = maker.makeProgram();
	}
	gl::glUseProgram(program);

	static const util::vec2 quad[] = {
		{-1.f, -1.f},
		{-1.f, 1.f},
		{1.f, 1.f},
		{1.f, -1.f}
	};

	gl::glGenBuffers(1, &quadBuffer);
	gl::glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
	gl::glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

	gl::glGenBuffers(1, &entitiesElemBuf);
	gl::glGenBuffers(1, &entitiesVertBuf);
	gl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entitiesElemBuf);
	gl::glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STREAM_DRAW);
	gl::glBindBuffer(GL_ARRAY_BUFFER, entitiesVertBuf);
	gl::glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(util::vec2), vertices.data(), GL_STREAM_DRAW);

	gl::glGenVertexArrays(1, &levelVAO);
	gl::glGenVertexArrays(1, &entitiesVAO);

	/*gl::glEnable(GL_BLEND);
	gl::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	textureArray.addTexture(&textureWall);
	textureArray.addTexture(&textureTarget);
	textureArray.addTexture(&textureCrate);
	textureArray.addTexture(&texturePlayer);

	gl::glActiveTexture(GL_TEXTURE0);
	gl::glGenTextures(1, &levelTexture);
	gl::glBindTexture(GL_TEXTURE_2D, levelTexture);
	gl::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	gl::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gl::glTexImage2D(GL_TEXTURE_2D, 0, GL_R8UI, level.getWidth(), level.getHeight(), 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, level.getLevelStaticView());

	gl::glActiveTexture(GL_TEXTURE0 + 1);
	gl::glGenTextures(1, &arrayTexture);
	gl::glBindTexture(GL_TEXTURE_2D_ARRAY, arrayTexture);
	gl::glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	gl::glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	{
		std::vector<char> textureData(textureArray.getWidth() * textureArray.getHeight() * textureArray.getDepth() * 4);
		textureArray.uploadData(textureData.data(), 0);
		gl::glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, textureArray.getWidth(), textureArray.getHeight(), textureArray.getDepth(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.data());
	}

	levelSampler = gl::glGetUniformLocation(program, "level");
	gl::glUniform1i(levelSampler, 0);

	textureArraySampler =  gl::glGetUniformLocation(program, "textureArray");
	gl::glUniform1i(textureArraySampler, 1);

	levelMode = gl::glGetUniformLocation(program, "levelMode");

	gl::glBindVertexArray(levelVAO);
	vertexLoc = gl::glGetAttribLocation(program, "vertex");
	gl::glEnableVertexAttribArray(vertexLoc);
	gl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	gl::glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
	gl::glVertexAttribPointer(vertexLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);

	gl::glBindVertexArray(entitiesVAO);
	gl::glEnableVertexAttribArray(vertexLoc);
	gl::glBindBuffer(GL_ARRAY_BUFFER, entitiesVertBuf);
	gl::glVertexAttribPointer(vertexLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	gl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entitiesElemBuf);

	gl::glClearColor(.0f, .0f, .0f, 1.f);

	frameStart = clock.now();
}

} /* namespace sokoban */

int main(int, char* argv[]){
	//util::vec<util::vec<float, 3>, 3> mat;
	std::cout.sync_with_stdio(false);
	sokoban::Game game(argv);
	return util::doSystemHandlers(&game);
}
