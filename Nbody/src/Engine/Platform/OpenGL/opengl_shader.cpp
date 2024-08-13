#include "opengl_shader.h"
#include "Core/log.h"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <ios>

static GLenum ShaderTypeFromString(const std::string &type) {
  if (type == "vertex")
    return GL_VERTEX_SHADER;
  if (type == "fragment" || type == "pixel")
    return GL_FRAGMENT_SHADER;

  return 0;
}

OpenGLShader::OpenGLShader(const std::string &filepath) {
  std::string source = ReadFile(filepath);
  auto shader_sources = PreProcess(source);
  Compile(shader_sources);

  auto last_slash = filepath.find_last_of("/\\");
  last_slash = last_slash == std::string::npos ? 0 : last_slash + 1;

  auto last_dot = filepath.rfind('.');
  auto count = last_dot == std::string::npos ? filepath.size() - last_slash
                                             : last_dot - last_slash;

  name_ = filepath.substr(last_slash, count);
}

OpenGLShader::OpenGLShader(const std::string &name,
                           const std::string &vertex_source,
                           const std::string &fragment_source)
    : name_(name) {

  std::unordered_map<GLenum, std::string> sources;

  sources[GL_VERTEX_SHADER] = vertex_source;
  sources[GL_FRAGMENT_SHADER] = fragment_source;

  Compile(sources);
}

OpenGLShader::~OpenGLShader() { glDeleteProgram(shader_id_); }

const std::string &OpenGLShader::GetName() const { return name_; }

std::string OpenGLShader::ReadFile(const std::string &path) {
  std::string result;
  std::ifstream in(path, std::ios::in | std::ios::binary);

  if (in) {
    in.seekg(0, std::ios::end);
    size_t size = in.tellg();

    if (size != -1) {
      result.resize(size);
      in.seekg(0, std::ios::beg);
      in.read(&result[0], size);
      in.close();

    } else {
      LOG_GLOBAL_ERROR("Could not read from file '{0}'", path);
    }

  } else {
    LOG_GLOBAL_ERROR("Could not open file '{0}'", path);
  }

  return result;
}

std::unordered_map<GLenum, std::string>
OpenGLShader::PreProcess(const std::string &source) {

  std::unordered_map<GLenum, std::string> shader_sources;

  const char *type_token = "#type";
  size_t type_token_length = strlen(type_token);

  size_t position = source.find(type_token, 0);

  while (position != std::string::npos) {
    // End of shader type declaration line
    size_t eol = source.find_first_of("\r\n", position);

    // Start of shader type name (after "#type " keyword)
    size_t begin = position + type_token_length + 1;

    std::string type = source.substr(begin, eol - begin);

    // Start of shader code after shader type declaration line
    size_t next_line_position = source.find_first_not_of("\r\n", eol);

    // Start of next shader type declaration line
    position = source.find(type_token, next_line_position);

    shader_sources[ShaderTypeFromString(type)] =
        (position == std::string::npos)
            ? source.substr(next_line_position)
            : source.substr(next_line_position, position - next_line_position);
  }

  return shader_sources;
}

void OpenGLShader::Compile(
    const std::unordered_map<GLenum, std::string> &shader_sources) {

  GLuint program = glCreateProgram();
  std::array<GLenum, 2> gl_shader_ids;
  int gl_shader_id_index = 0;

  for (auto &i : shader_sources) {
    GLenum type = i.first;
    const std::string &source = i.second;

    GLuint shader = glCreateShader(type);

    const GLchar *source_c_str = source.c_str();
    glShaderSource(shader, 1, &source_c_str, 0);

    glCompileShader(shader);

    GLint is_compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);

    if (is_compiled == GL_FALSE) {
      GLint max_length = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

      std::vector<GLchar> info_log(max_length);
      glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]);

      glDeleteShader(shader);

      LOG_GLOBAL_ERROR("{0}", info_log.data());
      break;
    }

    glAttachShader(program, shader);
    gl_shader_ids[gl_shader_id_index++] = shader;
  }

  shader_id_ = program;
  glLinkProgram(program);

  GLint is_linked = 0;

  glGetProgramiv(program, GL_LINK_STATUS, (int *)&is_linked);
  if (is_linked == GL_FALSE) {
    GLint max_length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<GLchar> info_log(max_length);
    glGetProgramInfoLog(program, max_length, &max_length, &info_log[0]);

    glDeleteProgram(program);

    for (auto id : gl_shader_ids)
      glDeleteShader(id);

    LOG_GLOBAL_ERROR("{0}", info_log.data());
    return;
  }

  for (auto i : gl_shader_ids) {
    glDetachShader(program, i);
    glDeleteShader(i);
  }
}

void OpenGLShader::Bind() const { glUseProgram(shader_id_); }

void OpenGLShader::Unbind() const { glUseProgram(0); }

void OpenGLShader::SetInt(const std::string &name, int value) {
  GLint location = glGetUniformLocation(shader_id_, name.c_str());
  glUniform1i(location, value);
}

void OpenGLShader::SetFloat(const std::string &name, float value) {
  GLint location = glGetUniformLocation(shader_id_, name.c_str());
  glUniform1f(location, value);
}

void OpenGLShader::SetFloat2(const std::string &name, const glm::vec2 &value) {
  GLint location = glGetUniformLocation(shader_id_, name.c_str());
  glUniform2f(location, value.x, value.y);
}

void OpenGLShader::SetFloat3(const std::string &name, const glm::vec3 &value) {
  GLint location = glGetUniformLocation(shader_id_, name.c_str());
  glUniform3f(location, value.x, value.y, value.z);
}

void OpenGLShader::SetFloat4(const std::string &name, const glm::vec4 &value) {
  GLint location = glGetUniformLocation(shader_id_, name.c_str());
  glUniform4f(location, value.x, value.y, value.z, value.w);
}

void OpenGLShader::SetMat3(const std::string &name, const glm::mat3 &matrix) {
  GLint location = glGetUniformLocation(shader_id_, name.c_str());
  glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &matrix) {
  GLint location = glGetUniformLocation(shader_id_, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
