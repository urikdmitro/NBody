#include "opengl_index_buffer.h"

OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int *indices, int count)
    : count_(count) {

  glCreateBuffers(1, &id_);

  glBindBuffer(GL_ARRAY_BUFFER, id_);
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), indices,
               GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers(1, &id_); }

int OpenGLIndexBuffer::GetCount() const { return count_; }

void OpenGLIndexBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void OpenGLIndexBuffer::Unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
