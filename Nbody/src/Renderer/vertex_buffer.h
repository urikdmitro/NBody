#ifndef NBODY_SRC_RENDERER_VERTEX_BUFFER_H_
#define NBODY_SRC_RENDERER_VERTEX_BUFFER_H_

#include "glad/glad.h"

class VertexBuffer {
private:
  GLuint buffer_id_;

public:
  VertexBuffer(const void *data, unsigned int size);
  ~VertexBuffer();

  void Bind() const;
  void Unbind() const;
};

#endif // NBODY_SRC_RENDERER_VERTEX_BUFFER_H_
