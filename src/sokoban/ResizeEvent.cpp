/*
 * ResizeEvent.cpp
 *
 *  Created on: Nov 11, 2018 г.
 *      Author: disba1ancer
 */

#include <sokoban/ResizeEvent.h>
#include <sokoban/Terminal.h>

namespace sokoban {

ResizeEvent::ResizeEvent(int newWidth, int newHeight) : width(newWidth), height(newHeight) {
}

long ResizeEvent::getEventID() const {
	return Terminal::EVENT_ON_RESIZE;
}

} /* namespace sokoban */
