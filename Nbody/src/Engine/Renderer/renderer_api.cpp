#include "renderer_api.h"
#include "Core/log.h"
#include "Platform/OpenGL/opengl_renderer_api.h"
#include "renderer_api.h"

RendererAPI::API RendererAPI::api_ = RendererAPI::API::OpenGL;

RendererAPI *RendererAPI::Create() {
  if (api_ == RendererAPI::API::None)
    return nullptr;

  if (api_ == RendererAPI::API::OpenGL)
    return new OpenGLRendererAPI();

  LOG_GLOBAL_FATAL("Unknown RendererAPI!");
  return nullptr;
}
