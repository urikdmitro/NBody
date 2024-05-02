#include "vertex_buffer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
  glGenBuffers(1, &buffer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &buffer_id_); }

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, buffer_id_); }

void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
