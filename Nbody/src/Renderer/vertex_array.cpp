#include "vertex_array.h"
#include "glad/glad.h"
#include "vertex_buffer.h"

VertexArray::VertexArray() : vertex_attribute_index_pointer_{0} {
  glGenVertexArrays(1, &vertex_array_id_);
}
VertexArray::~VertexArray() { glDeleteVertexArrays(1, &vertex_array_id_); }

void VertexArray::Bind() const { glBindVertexArray(vertex_array_id_); }
void VertexArray::Unbind() const { glBindVertexArray(0); }

// FIXME : Remake all
void VertexArray::AddVertexBuffer(const void *data, unsigned int size,
                                  GLint components_number, GLsizei stride,
                                  const GLvoid *offset) {

  vertex_buffers.push_back(new VertexBuffer(data, size));
  vertex_buffers.at(vertex_attribute_index_pointer_)->Bind();

  glBindVertexArray(vertex_array_id_);
  glEnableVertexAttribArray(vertex_attribute_index_pointer_);
  glVertexAttribPointer(0, components_number, GL_FLOAT, GL_FALSE, stride,
                        offset);

  glBindVertexArray(0);
  vertex_buffers.at(vertex_attribute_index_pointer_)->Unbind();
}
