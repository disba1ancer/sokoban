/*
 * Object.h
 *
 *  Created on: Oct 2, 2018
 *      Author: disba1ancer
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

namespace util {

class Observer {
public:
	virtual ~Observer() = 0;
};

inline Observer::~Observer() {}

} /* namespace util */

#endif /* OBSERVER_H_ */
