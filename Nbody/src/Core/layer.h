#ifndef NBODY_SRC_CORE_LAYER_
#define NBODY_SRC_CORE_LAYER_

#include "src/Events/event.h"

class Layer {

public:
  virtual void OnEvent(Event &event);
  virtual void OnAttach();
  virtual void OnDetach();
  virtual void OnUpdate();

  virtual ~Layer();
};

#endif // NBODY_SRC_CORE_LAYER_
