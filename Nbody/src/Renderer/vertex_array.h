#ifndef NBODY_SRC_RENDERER_VERTEX_ARRAY_H_
#define NBODY_SRC_RENDERER_VERTEX_ARRAY_H_

#include "glad/glad.h"
#include "vertex_buffer.h"
#include <vector>

class VertexArray {
private:
  GLuint vertex_array_id_;
  GLuint
      vertex_attribute_index_pointer_; // points to last active attribute index

  std::vector<VertexBuffer *> vertex_buffers;

public:
  VertexArray();
  ~VertexArray();

  void AddVertexBuffer(const void *data, unsigned int size,
                       GLint components_number, GLsizei stride,
                       const GLvoid *offset = (void *)0);

  void Bind() const;
  void Unbind() const;
};

#endif // NBODY_SRC_RENDERER_VERTEX_ARRAY_H_
