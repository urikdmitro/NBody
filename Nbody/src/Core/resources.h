#ifndef NBODY_SRC_CORE_RESOURCES_H_
#define NBODY_SRC_CORE_RESOURCES_H_

#include <glad/glad.h>

#include "shader.h"
#include "texture.h"
#include <string>

class Resources {
public:
  static Shader
  LoadShaderFromFile(std::string vertex_source_path,
                     std::string fragment_source_path,
                     std::string geometry_source_path = std::string());

  static Texture2D LoadTextureFromFile(std::string texture_path);

private:
  Resources() {}
  static std::string ReadShaderSource(std::string shader_source);
};

#endif // NBODY_SRC_CORE_RESOURCES_H_
