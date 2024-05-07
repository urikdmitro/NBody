#ifndef BREAKOUT_SRC_CORE_APPLICATION_H_
#define BREAKOUT_SRC_CORE_APPLICATION_H_

#include "glad/glad.h"
#include "layer_stack.h"
#include "window.h"

class Application {
private:
  WindowI *window_;
  bool is_running_;
  void OnEvent(Event &event);
  LayerStack layer_stack_;

public:
  Application();
  ~Application();

  void Run();
};

#endif // BREAKOUT_SRC_CORE_APPLICATION_H_
