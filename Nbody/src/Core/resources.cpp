#include "resources.h"
#include "stb/stb_image.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::string Resources::ReadShaderSource(std::string shader_source) {
  std::ifstream shader_source_stream(shader_source);
  std::stringstream shader_source_string_stream;

  shader_source_string_stream << shader_source_stream.rdbuf();
  shader_source_stream.close();

  return shader_source_string_stream.str();
}

Shader Resources::LoadShaderFromFile(std::string vertex_source_path,
                                     std::string fragment_source_path,
                                     std::string geometry_source_path) {

  std::string vertex_source = ReadShaderSource(vertex_source_path);
  std::string fragment_source = ReadShaderSource(fragment_source_path);

  std::string geometry_source;
  if (geometry_source_path.length() != 0) {
    geometry_source = ReadShaderSource(vertex_source_path);
  }

  return Shader(vertex_source, fragment_source, geometry_source);
}

Texture2D Resources::LoadTextureFromFile(std::string texture_path) {

  int width, height;
  unsigned char *pixel_data =
      stbi_load(texture_path.c_str(), &width, &height, nullptr, 0);

  Texture2D texture(width, height);
  texture.LoadImage(pixel_data);

  stbi_image_free(pixel_data);

  return texture;
}
