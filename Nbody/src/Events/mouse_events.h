#ifndef NBODY_SRC_EVENTS_MOUSE_EVENTS_
#define NBODY_SRC_EVENTS_MOUSE_EVENTS_

#include "event.h"

class MouseMovedEvent : public Event {
private:
  float mouse_x_, mouse_y_;

public:
  MouseMovedEvent(const float x, const float y);

  float GetX() const;
  float GetY() const;

  std::string ToString() const override;
  EVENT_CLASS_TYPE(kMouseMoved)
};

//
//
//

class MouseScrolledEvent : public Event {
private:
  float offset_x_, offset_y_;

public:
  MouseScrolledEvent(const float offset_x, const float offset_y);

  float GetXOffset() const;
  float GetYOffset() const;

  std::string ToString() const override;

  EVENT_CLASS_TYPE(kMouseScrolled)
};

//
//
//

class MouseButtonEvent : public Event {
protected:
  MouseButtonEvent(const int button_code);
  int button_code_;

public:
  int GetMouseButtonCode() const;
};

//
//
//

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
  MouseButtonPressedEvent(const int button_code);

  std::string ToString() const override;
  EVENT_CLASS_TYPE(kMouseButtonPressed)
};

//
//
//

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
  MouseButtonReleasedEvent(const int button_code);

  std::string ToString() const override;
  EVENT_CLASS_TYPE(kMouseButtonReleased)
};

#endif // NBODY_SRC_EVENTS_MOUSE_EVENTS_
