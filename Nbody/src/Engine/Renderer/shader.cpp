#include "shader.h"
#include "Core/log.h"
#include "Platform/OpenGL/opengl_shader.h"
#include "renderer.h"
#include "renderer_api.h"
#include <cstring>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

Shader *Shader::Create(const std::string &filepath) {
  if (Renderer::GetAPI() == RendererAPI::API::None)
    return nullptr;

  if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
    return new OpenGLShader(filepath);

  LOG_GLOBAL_FATAL("Unknown RendererAPI!");
  return nullptr;
}

Shader *Shader::Create(const std::string &name, const std::string &vertexSrc,
                       const std::string &fragmentSrc) {
  if (Renderer::GetAPI() == RendererAPI::API::None)
    return nullptr;

  if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
    return new OpenGLShader(name, vertexSrc, fragmentSrc);

  LOG_GLOBAL_FATAL("Unknown RendererAPI!");
  return nullptr;
}

void ShaderLibrary::Add(const std::string &name, Shader *shader) {
  shaders_[name] = shader;
}

void ShaderLibrary::Add(Shader *shader) {
  auto &name = shader->GetName();
  Add(name, shader);
}

Shader *ShaderLibrary::Load(const std::string &filepath) {
  auto shader = Shader::Create(filepath);
  Add(shader);
  return shader;
}

Shader *ShaderLibrary::Load(const std::string &name,
                            const std::string &filepath) {
  auto shader = Shader::Create(filepath);
  Add(name, shader);
  return shader;
}

Shader *ShaderLibrary::Get(const std::string &name) { return shaders_[name]; }

bool ShaderLibrary::Exists(const std::string &name) const {
  return shaders_.find(name) != shaders_.end();
}
