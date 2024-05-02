#include "mouse_events.h"
#include <sstream>

MouseMovedEvent::MouseMovedEvent(const float x, const float y)
    : mouse_x_(x), mouse_y_(y) {}

float MouseMovedEvent::GetX() const { return mouse_x_; }

float MouseMovedEvent::GetY() const { return mouse_y_; }

std::string MouseMovedEvent::ToString() const {
  std::stringstream ss;
  ss << "MouseMovedEvent: " << mouse_x_ << ", " << mouse_y_;
  return ss.str();
}

//
//
//

MouseScrolledEvent::MouseScrolledEvent(const float offset_x,
                                       const float offset_y)
    : offset_x_(offset_x), offset_y_(offset_y) {}

float MouseScrolledEvent::GetXOffset() const { return offset_x_; }

float MouseScrolledEvent::GetYOffset() const { return offset_y_; }

std::string MouseScrolledEvent::ToString() const {
  std::stringstream ss;
  ss << "MouseScrolledEvent: " << offset_x_ << ", " << offset_y_;
  return ss.str();
}

//
//
//

MouseButtonEvent::MouseButtonEvent(const int button_code)
    : button_code_(button_code) {}

int MouseButtonEvent::GetMouseButtonCode() const { return button_code_; }

//
//
//

MouseButtonPressedEvent::MouseButtonPressedEvent(const int button_code)
    : MouseButtonEvent(button_code) {}

std::string MouseButtonPressedEvent::ToString() const {
  std::stringstream ss;
  ss << "MouseButtonPressedEvent: " << button_code_;
  return ss.str();
}

//
//
//

MouseButtonReleasedEvent::MouseButtonReleasedEvent(const int button_code)
    : MouseButtonEvent(button_code) {}

std::string MouseButtonReleasedEvent::ToString() const {
  std::stringstream ss;
  ss << "MouseButtonReleasedEvent: " << button_code_;
  return ss.str();
}
