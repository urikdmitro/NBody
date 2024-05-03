#ifndef BREAKOUT_SRC_CORE_WINDOW_H_
#define BREAKOUT_SRC_CORE_WINDOW_H_

#include "src/Events/event.h"
#include <functional>
#include <string>

struct WindowProperties {
  int width;
  int height;
  std::string title;
};

class WindowI {
private:
public:
  using EventCallback = std::function<void(Event &)>;

  virtual ~WindowI() = default;
  virtual int GetWidth() = 0;
  virtual int GetHeight() = 0;
  virtual void Update() = 0;
  virtual void SetEventCallback(const EventCallback &event_callback) = 0;
};

#endif // BREAKOUT_SRC_CORE_WINDOW_H_
