/*
 * LevelLogic.h
 *
 *  Created on: Oct 6, 2018
 *      Author: disba1ancer
 */

#include <util/vec.h>
#include <vector>

#ifndef LEVELLOGIC_H_
#define LEVELLOGIC_H_

namespace sokoban {

class LevelLogic {
public:
	enum Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};

	LevelLogic(const unsigned char* leveldata = nullptr, int width = 0, int height = 0);
	virtual ~LevelLogic();
	void movePlayer(Direction direction);
	int getCratesCount() const;
	util::ivec2 getCrate(int index) const;
	bool checkWinCondition();
	void reset(const unsigned char* leveldata = nullptr, int width = 0, int height = 0);
	const unsigned char* getLevelStaticView() const;
	int getWidth() const;
	int getHeight() const;
	util::ivec2 getPlayer() const;
private:
	const unsigned char* levelData;
	int width, widthA, height;
	std::vector<unsigned char> level;
	std::vector<util::ivec2> crates;
	util::ivec2 player;
};

} /* namespace sokoban */

#endif /* LEVELLOGIC_H_ */
