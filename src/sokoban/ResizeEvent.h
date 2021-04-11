/*
 * ResizeEvent.h
 *
 *  Created on: Nov 11, 2018
 *      Author: disba1ancer
 */

#ifndef RESIZEEVENT_H_
#define RESIZEEVENT_H_

#include <util/Event.h>

namespace sokoban {

struct ResizeEvent: util::Event {
	ResizeEvent(int newWidth, int newHeight);
	long getEventID() const override;

	const int width, height;
};

} /* namespace sokoban */

#endif /* RESIZEEVENT_H_ */
