#include "RedrawEvent.h"
#include "Terminal.h"

namespace sokoban {

RedrawEvent::RedrawEvent()
{

}

long RedrawEvent::getEventID() const
{
    return Terminal::EVENT_ON_REDRAW;
}

} // namespace sokoban
