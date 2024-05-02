#include "renderer.h"

void Renderer::Draw(const VertexArray &vertex_array,
                    const Shader &shader) const {
  shader.Bind();
  vertex_array.Bind();

  // FIXME : fresh piece of dog shit with cum
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::SetClearColor(const glm::vec4 &color) const {
  glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::Clear() const { glClear(GL_COLOR_BUFFER_BIT); }
