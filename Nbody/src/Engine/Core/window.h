#ifndef NBODY_SRC_CORE_WINDOW_H_
#define NBODY_SRC_CORE_WINDOW_H_

#include "Events/event.h"
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
  virtual void *GetNativeWindow() = 0;
  virtual void *GetProcAddress() = 0;
};

#endif // NBODY_SRC_CORE_WINDOW_H_
