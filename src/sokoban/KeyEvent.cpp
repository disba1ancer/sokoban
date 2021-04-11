/*
 * KeyEvent.cpp
 *
 *  Created on: Jan 18, 2019
 *      Author: disba1ancer
 */

#include <sokoban/KeyEvent.h>
#include "Terminal.h"

namespace sokoban {

KeyEvent::KeyEvent(State state, unsigned long key)
: state(state), key(key) {}

long KeyEvent::getEventID() const {
	return Terminal::EVENT_ON_KEY_INPUT;
}

} /* namespace util */
