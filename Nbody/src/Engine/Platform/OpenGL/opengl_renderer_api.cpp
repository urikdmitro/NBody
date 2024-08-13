#include "opengl_renderer_api.h"
#include "Core/log.h"
#include <glad/glad.h>

void OpenGLMessageCallback(unsigned source, unsigned type, unsigned id,
                           unsigned severity, int length, const char *message,
                           const void *user_param) {
  switch (severity) {
  case GL_DEBUG_SEVERITY_HIGH:
    LOG_GLOBAL_FATAL(message);
    return;
  case GL_DEBUG_SEVERITY_MEDIUM:
    LOG_GLOBAL_ERROR(message);
    return;
  case GL_DEBUG_SEVERITY_LOW:
    LOG_GLOBAL_WARN(message);
    return;
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    LOG_GLOBAL_TRACE(message);
    return;
  }
}

void OpenGLRendererAPI::Init() {

#ifdef DEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(OpenGLMessageCallback, nullptr);

  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
                        GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
}

void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width,
                                    uint32_t height) {
  glViewport(x, y, width, height);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) {
  glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(VertexArray *vertex_array,
                                    uint32_t index_count) {
  vertex_array->Bind();
  vertex_array->GetIndexBuffer()->Bind();
  uint32_t count =
      index_count ? index_count : vertex_array->GetIndexBuffer()->GetCount();
  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::DrawLines(VertexArray *vertex_array,
                                  uint32_t vertex_count) {
  vertex_array->Bind();
  glDrawArrays(GL_LINES, 0, vertex_count);
}

// FIXME
void OpenGLRendererAPI::Draw(VertexArray *vertex_array) {
  vertex_array->Bind();
  glDrawArrays(GL_LINES, 0, 0);
}

void OpenGLRendererAPI::SetLineWidth(float width) { glLineWidth(width); }
