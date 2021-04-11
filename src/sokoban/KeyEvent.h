/*
 * KeyEvent.h
 *
 *  Created on: Jan 18, 2019
 *      Author: disba1ancer
 */

#ifndef KEYEVENT_H_
#define KEYEVENT_H_

#include <util/Event.h>

namespace sokoban {

class KeyEvent: public util::Event {
public:
	enum State {
		UP,
		DOWN,
		PRESSED
	};

	KeyEvent(State state, unsigned long key);
	long getEventID() const override;

	const State state;
	const unsigned long key;
};

} /* namespace util */

#endif /* KEYEVENT_H_ */
