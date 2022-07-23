/*
 * Game.h
 *
 *  Created on: Oct 4, 2018
 *      Author: disba1ancer
 */

#ifndef GAME_H_
#define GAME_H_

#include <sokoban/Terminal.h>
#include <sokoban/CloseEvent.h>
#include <sokoban/RedrawEvent.h>
#include <sokoban/ResizeEvent.h>
#include <sokoban/LevelLogic.h>
#include <util/observer1.h>
#include "../util/handlers2.h"
#include "KeyEvent.h"
#include <glwrp/gl31.h>
#include <glwrp/Context.h>
#include <util/BitmapTextureDataProvider.h>
#include <util/ArrayTextureDataProvider.h>

#include <vector>
#include <thread>
#include <atomic>
#include <queue>
#include <functional>
#include <chrono>

namespace sokoban {

class Game {
	std::vector<char*> args;
	Terminal window;
	LevelLogic level;
//	std::queue<std::function<void()>> renderCommandQueue;
	std::vector<util::vec2> vertices;
	std::vector<unsigned> indices;
	bool inGame;
	gl::Context context;
	GLuint program;
	GLuint quadBuffer;
	GLuint entitiesElemBuf, entitiesVertBuf;
	GLuint levelVAO;
	GLuint entitiesVAO;
	util::ArrayTextureDataProvider textureArray;
	util::BitmapTextureDataProvider textureCrate;
	util::BitmapTextureDataProvider textureTarget;
	util::BitmapTextureDataProvider textureWall;
	util::BitmapTextureDataProvider texturePlayer;
	GLuint levelTexture;
	GLuint arrayTexture;
	GLint levelSampler;
	GLint textureArraySampler;
	GLint levelMode;
	GLint vertexLoc;
	std::chrono::steady_clock clock;
	std::chrono::steady_clock::time_point frameStart;
public:
	Game(char* argv[]);
	virtual void onLoopStep();
	virtual ~Game();
private:
	void onClose(CloseEvent& event);
	void onRedraw(RedrawEvent& event);
	void onResize(ResizeEvent& event);
	void onKeyInput(KeyEvent& event);
	void initRender();
	void makeBuffers();

	util::Connection<void(util::Event&), UTIL_FUNCTOR(Game::onClose)> conOnClose = UTIL_FUNCTOR(Game::onClose)(this);
	util::Connection<void(util::Event&), UTIL_FUNCTOR(Game::onRedraw)> conOnRedraw = UTIL_FUNCTOR(Game::onRedraw)(this);
	util::Connection<void(util::Event&), UTIL_FUNCTOR(Game::onResize)> conOnResize = UTIL_FUNCTOR(Game::onResize)(this);
	util::Connection<void(util::Event&), UTIL_FUNCTOR(Game::onKeyInput)> conOnKeyInput = UTIL_FUNCTOR(Game::onKeyInput)(this);
};

} /* namespace sokoban */

#endif /* GAME_H_ */
