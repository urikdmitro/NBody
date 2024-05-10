#ifndef NBODY_SRC_RENDERER_RENDERER_H_
#define NBODY_SRC_RENDERER_RENDERER_H_

#include "src/Renderer/shader.h"
#include "src/Renderer/vertex_array.h"

class Renderer {
private:
public:
  void Clear() const;
  void SetClearColor(const glm::vec4 &color) const;
  void Draw(const VertexArray &vertex_array, const Shader &shader) const;
};

#endif // NBODY_SRC_RENDERER_RENDERER_H_
