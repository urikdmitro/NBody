#ifndef NBODY_SRC_CORE_APPLICATION_H_
#define NBODY_SRC_CORE_APPLICATION_H_

#include "glad/glad.h"
#include "layer_stack.h"
#include "window.h"

class Application {
private:
  static Application *instance_;
  Application();

  WindowI *window_;
  bool is_running_;
  void OnEvent(Event &event);
  LayerStack layer_stack_;

public:
  ~Application();
  Application(Application &) = delete;
  void operator=(const Application &) = delete;

  static Application &GetInstance();
  void Run();
  WindowI &GetWindow();

  void PushLayer(Layer *layer);
  void PushOverlayer(Layer *layer);
};

#endif // NBODY_SRC_CORE_APPLICATION_H_
