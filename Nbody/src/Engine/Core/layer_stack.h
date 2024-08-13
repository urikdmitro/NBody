#ifndef NBODY_SRC_CORE_LAYER_STACK_
#define NBODY_SRC_CORE_LAYER_STACK_

#include "layer.h"
#include <vector>

class LayerStack {
public:
  LayerStack();
  ~LayerStack();

  void PushLayer(Layer *layer);
  void PushOverlayer(Layer *layer);
  void PopLayer(Layer *layer);
  void PopOverlayer(Layer *layer);

  std::vector<Layer *>::iterator begin();
  std::vector<Layer *>::iterator end();

  std::vector<Layer *>::reverse_iterator rbegin();
  std::vector<Layer *>::reverse_iterator rend();

private:
  std::vector<Layer *> layers_;
  int last_layer_stack_pointer_;
};

#endif // NBODY_SRC_CORE_LAYER_STACK_
