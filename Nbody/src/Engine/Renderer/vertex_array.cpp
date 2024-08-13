#include "vertex_array.h"
#include "Core/log.h"
#include "Platform/OpenGL/opengl_vertex_array.h"
#include "renderer.h"
#include "renderer_api.h"

VertexArray::~VertexArray() {}

VertexArray *VertexArray::Create() {
  if (Renderer::GetAPI() == RendererAPI::API::None)
    return nullptr;

  if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
    return new OpenGLVertexArray();

  LOG_GLOBAL_FATAL("Unknown RendererAPI!");
  return nullptr;
}
