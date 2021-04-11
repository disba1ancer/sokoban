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
#include <sokoban/ResizeEvent.h>
#include <sokoban/LevelLogic.h>
#include <util/observer1.h>
#include "../util/handlers2.h"
#include "KeyEvent.h"

#include <vector>
#include <thread>
#include <atomic>
#include <queue>
#include <functional>

namespace sokoban {

class Game {
public:
	Game(char* argv[]);
	virtual void onLoopStep();
	void renderLoop();
	virtual ~Game();
private:
	void onClose(CloseEvent& event);
	void onResize(ResizeEvent& event);
	void onKeyInput(KeyEvent& event);
	void makeBuffers();
	std::vector<char*> args;
	Terminal window;
	std::atomic<bool> stopRender;
	std::thread renderThread;
	LevelLogic level;
	std::queue<std::function<void()>> renderCommandQueue;
	std::vector<util::vec2> vertices;
	std::vector<unsigned> indices;
	bool inGame;
	util::Connection<void(util::Event&), UTIL_FUNCTOR(Game::onClose)> conOnClose = UTIL_FUNCTOR(Game::onClose)(this);
	util::Connection<void(util::Event&), UTIL_FUNCTOR(Game::onResize)> conOnResize = UTIL_FUNCTOR(Game::onResize)(this);
	util::Connection<void(util::Event&), UTIL_FUNCTOR(Game::onKeyInput)> conOnKeyInput = UTIL_FUNCTOR(Game::onKeyInput)(this);
};

} /* namespace sokoban */

#endif /* GAME_H_ */
