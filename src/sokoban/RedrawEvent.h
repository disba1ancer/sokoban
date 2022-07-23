#ifndef SOKOBAN_REDRAWEVENT_H
#define SOKOBAN_REDRAWEVENT_H

#include <util/Event.h>

namespace sokoban {

struct RedrawEvent : public util::Event {
public:
	RedrawEvent();
	long getEventID() const override;
};

} // namespace sokoban

#endif // SOKOBAN_REDRAWEVENT_H
