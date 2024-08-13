#ifndef NBODY_SRC_RENDERER_RENDERER_COMMAND_
#define NBODY_SRC_RENDERER_RENDERER_COMMAND_

#include "renderer_api.h"

class RendererCommand {
private:
  static RendererAPI *renderer_api_;

public:
  static void Init();

  static void SetViewport(uint32_t x, uint32_t y, uint32_t width,
                          uint32_t height);

  static void SetClearColor(const glm::vec4 &color);

  static void Clear();

  static void DrawIndexed(VertexArray *vertexArray, uint32_t indexCount = 0);
  static void Draw(VertexArray *vertexArray);

  static void DrawLines(VertexArray *vertexArray, uint32_t vertexCount);

  static void SetLineWidth(float width);
};

#endif // NBODY_SRC_RENDERER_RENDERER_COMMAND_
