#ifndef NBODY_SRC_EVENTS_WINDOW_EVENTS_
#define NBODY_SRC_EVENTS_WINDOW_EVENTS_

#include "event.h"

class WindowResizeEvent : public Event {
private:
  unsigned int width_;
  unsigned int height_;

public:
  WindowResizeEvent(unsigned int width, unsigned int height);

  unsigned int GetWidth() const;
  unsigned int GetHeight() const;

  std::string ToString() const override;

  EVENT_CLASS_TYPE(kWindowResized)
};

//
//
//

class WindowCloseEvent : public Event {
public:
  WindowCloseEvent();

  EVENT_CLASS_TYPE(kWindowClosed)
};

#endif // NBODY_SRC_EVENTS_WINDOW_EVENTS_
