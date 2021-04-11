/*
 * Event.h
 *
 *  Created on: Oct 1, 2018
 *      Author: disba1ancer
 */

#ifndef EVENT_H_
#define EVENT_H_

namespace util {

struct Event {
	virtual long getEventID() const = 0;
	virtual ~Event() = 0;
};

inline Event::~Event() {}

} /* namespace util */

#endif /* EVENT_H_ */
