#ifndef BREAKOUT_SRC_EVENTS_EVENT_DISPATCHER_
#define BREAKOUT_SRC_EVENTS_EVENT_DISPATCHER_

#include "event.h"
#include <functional>

class EventDispatcher {
private:
  Event &event_;
  template <typename T> using EventFn = std::function<bool(T &)>;

public:
  EventDispatcher(Event &event) : event_(event) {}

  template <typename T> bool Dispatch(EventFn<T> func) {
    if (event_.GetEventType() == T::GetStaticType()) {
      event_.Handled = func(*(T *)&event_);
      return true;
    }
    return false;
  }
};

#endif // BREAKOUT_SRC_EVENTS_EVENT_DISPATCHER_
