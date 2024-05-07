#include "layer_stack.h"
#include <algorithm>

LayerStack::LayerStack() : last_layer_stack_pointer_(0) {}
LayerStack::~LayerStack() {
  for (auto i : layers_) {
    delete i;
  }
}

void LayerStack::PushLayer(Layer *layer) {
  layers_.insert(layers_.begin() + last_layer_stack_pointer_, layer);
  ++last_layer_stack_pointer_;
}

void LayerStack::PushOverlayer(Layer *layer) { layers_.push_back(layer); }

// TODO: Throw exeption or smt else when vector is empty
void LayerStack::PopLayer(Layer *layer) {
  auto it = std::find(layers_.begin(),
                      layers_.begin() + last_layer_stack_pointer_ + 1, layer);

  if (it != layers_.end()) {
    layers_.erase(it);
    --last_layer_stack_pointer_;
  }
}

void LayerStack::PopOverlayer(Layer *layer) {
  auto it = std::find(layers_.begin() + last_layer_stack_pointer_ + 1,
                      layers_.end(), layer);

  if (it != layers_.end())
    layers_.erase(it);
}

std::vector<Layer *>::iterator LayerStack::begin() { return layers_.begin(); }
std::vector<Layer *>::iterator LayerStack::end() { return layers_.end(); }

std::vector<Layer *>::reverse_iterator LayerStack::rbegin() {
  return layers_.rbegin();
}
std::vector<Layer *>::reverse_iterator LayerStack::rend() {
  return layers_.rend();
}
