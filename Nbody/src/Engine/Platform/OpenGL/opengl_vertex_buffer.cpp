#include "opengl_vertex_buffer.h"

OpenGLVertexBuffer::OpenGLVertexBuffer(const void *data, size_t size) {
  glGenBuffers(1, &buffer_id_);

  glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &buffer_id_); }

void OpenGLVertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
}

void OpenGLVertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

const BufferLayout &OpenGLVertexBuffer::GetLayout() const { return layout_; };
void OpenGLVertexBuffer::SetLayout(const BufferLayout &layout) {
  layout_ = layout;
}
