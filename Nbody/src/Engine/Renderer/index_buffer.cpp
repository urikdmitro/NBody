#include "index_buffer.h"
#include "Core/log.h"
#include "Platform/OpenGL/opengl_index_buffer.h"
#include "renderer.h"
#include "renderer_api.h"

IndexBuffer::~IndexBuffer() {}

IndexBuffer *IndexBuffer::Create(unsigned int *indices, int count) {
  if (Renderer::GetAPI() == RendererAPI::API::None)
    return nullptr;

  if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
    return new OpenGLIndexBuffer(indices, count);

  LOG_GLOBAL_FATAL("Unknown RendererAPI!");
  return nullptr;
}
