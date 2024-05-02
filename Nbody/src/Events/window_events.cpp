#include "window_events.h"
#include <sstream>

WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height)
    : width_(width), height_(height) {}

unsigned int WindowResizeEvent::GetWidth() const { return width_; }

unsigned int WindowResizeEvent::GetHeight() const { return height_; }

std::string WindowResizeEvent::ToString() const {
  std::stringstream ss;
  ss << "WindowResizeEvent: " << width_ << ", " << height_;
  return ss.str();
}

//
//
//

WindowCloseEvent::WindowCloseEvent() {}
