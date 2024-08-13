#ifndef NBODY_SRC_CORE_IMGUI_LAYER_
#define NBODY_SRC_CORE_IMGUI_LAYER_

#include "Events/event.h"
#include "Events/key_events.h"
#include "Events/mouse_events.h"
#include "Events/window_events.h"
#include "imgui.h"
#include "layer.h"

class ImGuiLayer : public Layer {
private:
  float time_step_;

public:
  ImGuiLayer();
  ~ImGuiLayer() override;

  void OnEvent(Event &event) override;
  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(float ts) override;

  void Begin();
  void End();

  bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &event);
  bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event);
  bool OnMouseMovedEvent(MouseMovedEvent &event);
  bool OnMouseScrolledEvent(MouseScrolledEvent &event);
  bool OnKeyPressedEvent(KeyPressedEvent &event);
  bool OnKeyReleasedEvent(KeyReleasedEvent &event);
  bool OnKeyTypedEvent(KeyTypedEvent &event);
  bool OnWindowResizedEvent(WindowResizeEvent &event);

private:
};

#endif // NBODY_SRC_CORE_IMGUI_LAYER_
