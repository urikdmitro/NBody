#ifndef NBODY_SRC_CORE_LAYER_
#define NBODY_SRC_CORE_LAYER_

#include <Events/event.h>

class Layer {

public:
  virtual void OnEvent(Event &event);
  virtual void OnAttach();
  virtual void OnDetach();
  virtual void OnUpdate(float ts);
  virtual void OnImGuiRender();

  virtual ~Layer();
};

#endif // NBODY_SRC_CORE_LAYER_
