#ifndef NBODY_SRC_PLATFORM_OPENGL_OPENGL_RENDERER_API_
#define NBODY_SRC_PLATFORM_OPENGL_OPENGL_RENDERER_API_

#include "Renderer/renderer_api.h"

class OpenGLRendererAPI : public RendererAPI {
public:
  void Init() override;
  void SetViewport(uint32_t x, uint32_t y, uint32_t width,
                   uint32_t height) override;

  void SetClearColor(const glm::vec4 &color) override;
  void Clear() override;

  void DrawIndexed(VertexArray *vertex_array,
                   uint32_t index_count = 0) override;
  void DrawLines(VertexArray *vertex_array, uint32_t vertex_count) override;
  void Draw(VertexArray *vertex_array) override;

  void SetLineWidth(float width) override;
};

#endif // !NBODY_SRC_PLATFORM_OPENGL_OPENGL_RENDERER_API_
