#include "key_events.h"
#include <sstream>

KeyEvent::KeyEvent(int key_code) : key_code_(key_code) {}

int KeyEvent::GetKeyCode() const { return key_code_; }

//
//
//

KeyPressedEvent::KeyPressedEvent(int key_code, int repeat_count)
    : KeyEvent(key_code), repeat_count_(repeat_count) {}

int KeyPressedEvent::GetRepeatCount() const { return repeat_count_; }

std::string KeyPressedEvent::ToString() const {
  std::stringstream ss;
  ss << "KeyPressedEvent: " << key_code_ << " (" << repeat_count_
     << " repeats)";
  return ss.str();
}

//
//
//

KeyReleasedEvent::KeyReleasedEvent(int key_code) : KeyEvent(key_code) {}

std::string KeyReleasedEvent::ToString() const {
  std::stringstream ss;
  ss << "KeyReleasedEvent: " << key_code_;
  return ss.str();
}
