/*
 * CloseEvent.cpp
 *
 *  Created on: Oct 3, 2018
 *      Author: disba1ancer
 */

#include <sokoban/CloseEvent.h>
#include <sokoban/Terminal.h>

namespace sokoban {

/*CloseEvent::CloseEvent() {}

CloseEvent::~CloseEvent() {}*/

long CloseEvent::getEventID() const {
	return Terminal::EVENT_ON_CLOSE;
}

} /* namespace sokoban */
