/*
 * CloseEvent.h
 *
 *  Created on: Oct 3, 2018
 *      Author: disba1ancer
 */

#ifndef CLOSEEVENT_H_
#define CLOSEEVENT_H_

#include <util/Event.h>

namespace sokoban {

class CloseEvent: public util::Event {
public:
	//CloseEvent();
	//~CloseEvent() override;
	long getEventID() const override;
};

} /* namespace sokoban */

#endif /* CLOSEEVENT_H_ */
