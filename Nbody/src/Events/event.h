#ifndef BREAKOUT_SRC_EVENTS_EVENT_
#define BREAKOUT_SRC_EVENTS_EVENT_

#include <string>

enum class EventType {
  kNone = 0,
  kWindowClosed,
  kWindowResized,
  kWindowFocused,
  kWindowLostFocus,
  kWindowMoved,
  kKeyPressed,
  kKeyReleased,
  kKeyTyped,
  kMouseButtonPressed,
  kMouseButtonReleased,
  kMouseMoved,
  kMouseScrolled
};

#define EVENT_CLASS_TYPE(type)                                                 \
  static EventType GetStaticType() { return EventType::type; }                 \
  virtual EventType GetEventType() const override { return GetStaticType(); }  \
  virtual const char *GetName() const override { return #type; }

class Event {
public:
  virtual ~Event() = default;

  bool Handled = false;

  virtual EventType GetEventType() const = 0;
  virtual const char *GetName() const = 0;
  virtual std::string ToString() const;
};

#endif // BREAKOUT_SRC_EVENTS_EVENT_
