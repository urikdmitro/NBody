#ifndef NBODY_SRC_RENDERER_OPENGL_SHADER_
#define NBODY_SRC_RENDERER_OPENGL_SHADER_

#include "Renderer/shader.h"
#include "glad/glad.h"
#include <string>

class OpenGLShader : public Shader {
public:
  OpenGLShader(const std::string &filepath);
  OpenGLShader(const std::string &name, const std::string &vertexSrc,
               const std::string &fragmentSrc);

  ~OpenGLShader();

  void Bind() const override;
  void Unbind() const override;

  const std::string &GetName() const override;

  void SetInt(const std::string &name, int value) override;

  void SetFloat(const std::string &name, float value) override;
  void SetFloat2(const std::string &name, const glm::vec2 &value) override;
  void SetFloat3(const std::string &name, const glm::vec3 &value) override;
  void SetFloat4(const std::string &name, const glm::vec4 &value) override;

  void SetMat3(const std::string &name, const glm::mat3 &matrix) override;
  void SetMat4(const std::string &name, const glm::mat4 &matrix) override;

private:
  std::string ReadFile(const std::string &filepath);
  std::unordered_map<GLenum, std::string> PreProcess(const std::string &source);
  void Compile(const std::unordered_map<GLenum, std::string> &shaderSources);

  uint32_t shader_id_;
  std::string name_;
};

#endif // NBODY_SRC_RENDERER_OPENGL_SHADER_
