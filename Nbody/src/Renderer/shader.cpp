#include "shader.h"
#include "glm/gtc/type_ptr.hpp"
#include <cstring>

Shader::Shader(const std::string &vertex_source,
               const std::string &fragment_source,
               const std::string &geometry_source) {

  CompileProgram(vertex_source, fragment_source, geometry_source);
}

Shader::~Shader() { glDeleteProgram(program_id_); }

// FIXME: horrible piece of shit, need to fix dublication of the code
GLuint Shader::CompileProgram(const std::string &vertex_source,
                              const std::string &fragment_source,
                              const std::string &geometry_source) {

  this->program_id_ = glCreateProgram();
  GLuint compile_status;

  GLuint vertex_shader_id = CompileShader(vertex_source);
  compile_status = CheckShaderCompileStatus(vertex_shader_id);

  GLuint fragment_shader_id = CompileShader(fragment_source);
  compile_status = CheckShaderCompileStatus(fragment_shader_id);

  glAttachShader(this->program_id_, vertex_shader_id);
  glAttachShader(this->program_id_, fragment_shader_id);

  GLuint geometry_shader_id;
  if (!geometry_source.empty()) {
    geometry_shader_id = CompileShader(geometry_source);
    compile_status = CheckShaderCompileStatus(geometry_shader_id);

    glAttachShader(this->program_id_, geometry_shader_id);
  }

  // FIXME: at least 1 result of CheckShaderCompileErrors is ignored
  if (compile_status)
    glLinkProgram(this->program_id_);

  glDetachShader(program_id_, vertex_shader_id);
  glDeleteShader(vertex_shader_id);

  glDetachShader(program_id_, fragment_shader_id);
  glDeleteShader(fragment_shader_id);

  if (!geometry_source.empty()) {
    glDetachShader(program_id_, geometry_shader_id);
    glDeleteShader(geometry_shader_id);
  }

  return compile_status;
}

GLuint Shader::CompileShader(const std::string &shader_source) {

  char *shader_source_buffer = new char[shader_source.length()];
  std::strcpy(shader_source_buffer, shader_source.c_str());

  GLuint shader_id = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(shader_id, 1, &shader_source_buffer, NULL);
  glCompileShader(shader_id);

  return shader_id;
}

// TODO: methods CheckShaderCompileErrors and CheckShaderProgramCompileErrors
// have similar implementation, need to fix it
GLuint Shader::CheckShaderCompileStatus(unsigned int shader_id) {
  GLint success;
  char infoLog[1024];

  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader_id, 1024, NULL, infoLog);
    // FIXME: add log
    return 0;
  }

  return 1;
}

unsigned int Shader::CheckShaderProgramCompileStatus(unsigned int program_id) {
  GLint success;
  char infoLog[1024];

  glGetProgramiv(program_id, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program_id, 1024, NULL, infoLog);
    // FIXME: add log
    return 0;
  }

  return 1;
}

GLuint Shader::GetProgramId() const { return program_id_; }

const Shader &Shader::Bind() const {
  glUseProgram(program_id_);
  return *this;
}

const Shader &Shader::Unbind() const {
  glUseProgram(0);
  return *this;
}

void Shader::SetUniform(const std::string &uniform_name, GLfloat value) const {
  GLint location = glGetUniformLocation(program_id_, uniform_name.c_str());
  glUniform1f(location, value);
}

void Shader::SetUniform(const std::string &uniform_name, GLint value) const {
  GLint location = glGetUniformLocation(program_id_, uniform_name.c_str());
  glUniform1i(location, value);
}

void Shader::SetUniform(const std::string &uniform_name,
                        const glm::vec2 &value) const {
  GLint location = glGetUniformLocation(program_id_, uniform_name.c_str());
  glUniform2f(location, value.x, value.y);
}

void Shader::SetUniform(const std::string &uniform_name,
                        const glm::vec3 &value) const {
  GLint location = glGetUniformLocation(program_id_, uniform_name.c_str());
  glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetUniform(const std::string &uniform_name,
                        const glm::vec4 &value) const {
  GLint location = glGetUniformLocation(program_id_, uniform_name.c_str());
  glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetUniform(const std::string &uniform_name,
                        const glm::mat2 &value) const {
  GLint location = glGetUniformLocation(program_id_, uniform_name.c_str());
  glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string &uniform_name,
                        const glm::mat3 &value) const {
  GLint location = glGetUniformLocation(program_id_, uniform_name.c_str());
  glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string &uniform_name,
                        const glm::mat4 &value) const {
  GLint location = glGetUniformLocation(program_id_, uniform_name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
