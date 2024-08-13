#include "texture.h"
#include "Core/log.h"
#include "Platform/OpenGL/opengl_texture.h"
#include "renderer.h"
#include "renderer_api.h"

Texture::~Texture() {}

Texture *Texture::Create(const TextureSpecification &specification) {
  if (Renderer::GetAPI() == RendererAPI::API::None)
    return nullptr;

  if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
    return new OpenGLTexture(specification);

  LOG_GLOBAL_FATAL("Unknown RendererAPI!");
  return nullptr;
}

Texture *Texture::Create(const std::string &path) {
  if (Renderer::GetAPI() == RendererAPI::API::None)
    return nullptr;

  if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
    return new OpenGLTexture(path);

  LOG_GLOBAL_FATAL("Unknown RendererAPI!");
  return nullptr;
}
