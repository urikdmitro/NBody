#ifndef NBODY_SRC_RENDERER_SHADER_
#define NBODY_SRC_RENDERER_SHADER_

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include <string>
#include <unordered_map>

class Shader {
public:
  virtual ~Shader() = default;

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual void SetInt(const std::string &name, int value) = 0;
  virtual void SetFloat(const std::string &name, float value) = 0;
  virtual void SetFloat2(const std::string &name, const glm::vec2 &value) = 0;
  virtual void SetFloat3(const std::string &name, const glm::vec3 &value) = 0;
  virtual void SetFloat4(const std::string &name, const glm::vec4 &value) = 0;
  virtual void SetMat3(const std::string &name, const glm::mat3 &value) = 0;
  virtual void SetMat4(const std::string &name, const glm::mat4 &value) = 0;

  virtual const std::string &GetName() const = 0;
  static Shader *Create(const std::string &filepath);
  static Shader *Create(const std::string &name, const std::string &vertexSrc,
                        const std::string &fragmentSrc);
};

class ShaderLibrary {
public:
  void Add(const std::string &name, Shader *shader);
  void Add(Shader *shader);
  Shader *Load(const std::string &filepath);
  Shader *Load(const std::string &name, const std::string &filepath);

  Shader *Get(const std::string &name);

  bool Exists(const std::string &name) const;

private:
  std::unordered_map<std::string, Shader *> shaders_;
};
#endif // NBODY_SRC_RENDERER_SHADER_
