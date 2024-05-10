#ifndef NBODY_SRC_EVENTS_KEY_EVENTS_
#define NBODY_SRC_EVENTS_KEY_EVENTS_

#include "event.h"

class KeyEvent : public Event {
protected:
  KeyEvent(int key_code);
  int key_code_;

public:
  int GetKeyCode() const;
};

//
//
//

class KeyPressedEvent : public KeyEvent {
private:
  int repeat_count_;

public:
  KeyPressedEvent(int key_code, int repeat_count);

  int GetRepeatCount() const;
  std::string ToString() const override;

  EVENT_CLASS_TYPE(kKeyPressed)
};

//
//
//

class KeyReleasedEvent : public KeyEvent {
public:
  KeyReleasedEvent(int key_code);

  std::string ToString() const override;

  EVENT_CLASS_TYPE(kKeyReleased)
};

#endif // NBODY_SRC_EVENTS_KEY_EVENTS_
