/*
 * LevelLogic.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: disba1ancer
 */

#include <sokoban/LevelLogic.h>
#include <util/util.h>

namespace {
	enum LevelTiles {
		TILE_NONE,
		TILE_WALL,
		TILE_TARGET,
		TILE_CRATE,
		TILE_PLAYER,
		TILE_COUNT
	};

	util::ivec2 directions[] = {
			{ 0, 1 },
			{ 0, -1 },
			{ -1, 0 },
			{ 1, 0 }
	};
}

namespace sokoban {

LevelLogic::LevelLogic(const unsigned char* leveldata, int width, int height)
:
		levelData(leveldata),
		width(width),
		widthA(static_cast<int>(util::alignSize(4, static_cast<std::size_t>(width)))),
		height(height),
		level(std::size_t(widthA) * std::size_t(height))
{
	reset();
}

LevelLogic::~LevelLogic() {
	// TODO Auto-generated destructor stub
}

void LevelLogic::movePlayer(Direction direction) {
	using namespace util;
	auto newPlayerPos = player + directions[direction];
	if (newPlayerPos[X] >= 0 && newPlayerPos[X] < width &&
			newPlayerPos[Y] >= 0 && newPlayerPos[Y] < height &&
			level[std::size_t(newPlayerPos[X]) + std::size_t(newPlayerPos[Y]) * std::size_t(widthA)] != TILE_WALL)
	{
		for (auto& i : crates) {
			if (newPlayerPos == i) {
				auto newCratePos = newPlayerPos + directions[direction];
				if (newCratePos[X] >= 0 && newCratePos[X] < width &&
						newCratePos[Y] >= 0 && newCratePos[Y] < height &&
						level[std::size_t(newCratePos[X]) + std::size_t(newCratePos[Y]) * std::size_t(widthA)] != TILE_WALL)
				{
					for (auto& i : crates) {
						if (newCratePos == i) {
							return;
						}
					}
					i = newCratePos;
					break;
				} else {
					return;
				}
			}
		}
		player = newPlayerPos;
	}
}

int LevelLogic::getCratesCount() const {
	return static_cast<int>(crates.size());
}

util::ivec2 LevelLogic::getCrate(int index) const {
	return crates[std::size_t(index)];
}

bool LevelLogic::checkWinCondition() {
	using namespace util;
	for (auto& crate : crates) {
		if (level[std::size_t(crate[X]) + std::size_t(crate[Y]) * std::size_t(widthA)] != TILE_TARGET) return false;
	}
	return true;
}

void LevelLogic::reset(const unsigned char* levelData, int width, int height) {
	if (levelData) {
		this->levelData = levelData;
		this->width = width;
		this->widthA = static_cast<int>(util::alignSize(4, static_cast<std::size_t>(width)));
		this->height = height;
		level.resize(std::size_t(width) * std::size_t(height));
	}
	auto index = 0U;
	auto iter = level.begin();
	crates.clear();
	for (int y = 0; y < this->height; ++y, iter += (this->widthA - this->width)) {
		for (int x = 0; x < this->width; ++x, ++index, ++iter) {
			switch (this->levelData[index]) {
			case TILE_PLAYER:
				player = util::ivec2{int(x), int(y)};
				*iter = TILE_NONE;
				break;
			case TILE_CRATE:
				crates.push_back(util::ivec2{int(x), int(y)});
				*iter = TILE_NONE;
				break;
			default:
				*iter = this->levelData[index];
			}
		}
	}
}

const unsigned char* LevelLogic::getLevelStaticView() const {
	return level.data();
}

int LevelLogic::getWidth() const {
	return width;
}

int LevelLogic::getHeight() const {
	return height;
}

util::ivec2 LevelLogic::getPlayer() const {
	return player;
}

} /* namespace sokoban */
