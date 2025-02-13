#ifndef NBODY_SRC_RENDERER_RENDERER_API_
#define NBODY_SRC_RENDERER_RENDERER_API_

#include "vertex_array.h"
#include <glm/glm.hpp>

class RendererAPI {
public:
  enum class API { None = 0, OpenGL = 1 };

public:
  virtual ~RendererAPI() = default;

  virtual void Init() = 0;
  virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width,
                           uint32_t height) = 0;
  virtual void SetClearColor(const glm::vec4 &color) = 0;
  virtual void Clear() = 0;

  virtual void DrawIndexed(VertexArray *vertexArray,
                           uint32_t indexCount = 0) = 0;
  virtual void DrawLines(VertexArray *vertexArray, uint32_t vertexCount) = 0;
  virtual void Draw(VertexArray *vertexArray) = 0;

  virtual void SetLineWidth(float width) = 0;

  static API GetAPI() { return api_; }
  static RendererAPI *Create();

private:
  static API api_;
};

#endif // NBODY_SRC_RENDERER_RENDERER_API_
