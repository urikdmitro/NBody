#ifndef NBODY_SRC_CORE_APPLICATION_H_
#define NBODY_SRC_CORE_APPLICATION_H_

#include "Core/imgui_layer.h"
#include "glad/glad.h"
#include "layer_stack.h"
#include "window.h"

#include "src/Program/openmp_simulation.h"
#include "src/Program/sequential_simulation.h"
#include "src/Program/simulation.h"

class Application {
private:
  static Application *instance_;
  Application();

  Simulation *simulation_ = nullptr;
  WindowI *window_;
  bool is_running_;
  void OnEvent(Event &event);
  LayerStack layer_stack_;
  ImGuiLayer *imgui_layer_;

  float last_frame_time_;

public:
  ~Application();
  Application(Application &) = delete;
  void operator=(const Application &) = delete;

  static Application &GetInstance();
  void Run();
  void Setup();

  void Test();
  void RealTime();

  WindowI &GetWindow();
  Simulation *GetSimulation() { return simulation_; }

  void PushLayer(Layer *layer);
  void PushOverlayer(Layer *layer);
};

#endif // NBODY_SRC_CORE_APPLICATION_H_
