/*
 * Terminal.h
 *
 *  Created on: Aug 23, 2017
 *      Author: disba1ancer
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <util/observer1.h>
#include <util/Event.h>
#include <util/util.h>

namespace sokoban {

class Terminal {
public:
        enum EventType {
                EVENT_ON_CLOSE,
                EVENT_ON_RESIZE,
                EVENT_ON_KEY_INPUT,
                EVENT_ON_REDRAW,
                EVENT_COUNT
        };

        enum ShowCommand {
                HIDE,
                SHOW,
                SHOW_MINIMIZED,
                SHOW_RESTORED,
                SHOW_MAXIMIZED,
                SHOW_FULL_SCREEN
        };

        Terminal();
        Terminal(const Terminal& orig) = delete;
        Terminal(Terminal&& orig) = delete;
        Terminal& operator =(const Terminal& orig) = delete;
        Terminal& operator =(Terminal&& orig) = delete;
        ~Terminal();
        const void* getSysDepId() const;
        bool isVisible() const;
        void show(ShowCommand command = SHOW);
        int getHeight() const;
        int getWidth() const;
        void resize(int width, int height);
        bool isSizable() const;
        void makeSizable(bool sizable = true);
        void attach(EventType eventType, util::IConnection<void(util::Event&)>& connection);
        /*template <typename Recv, typename Evt>
        Connection<void> attach(EventType eventType, Recv* recv, void (Recv::*method)(Evt&));*/
        void close();
        void forceRedraw();

private:
        //unsigned char storage[256 - sizeof(void*)];
        void* priv;
};

/*template <typename Recv, typename Evt>
Connection<void> Terminal::attach(EventType eventType, Recv* recv, void (Recv::*method)(Evt&)) {
        void (*wrapped)(Recv*, Evt*);
        wrapped = (&::dse::util::typename wrap_method<decltype(method)>::template wrapper<method>);
        static_cast<void>(wrapped);
        return Connection<void>(nullptr, nullptr);//attach(eventType, recv, &::dse::util::wrap_static<decltype(wrapped)>::template wrapper<wrapped, void, void*, Event*>);//DSE_WRAP_STATIC(DSE_WRAP_METHOD(method), void, void*, Event*)
}*/

} /* namespace sokoban */

#endif /* TERMINAL_H_ */
