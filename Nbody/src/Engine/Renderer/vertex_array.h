#ifndef NBODY_SRC_RENDERER_VERTEX_ARRAY_H_
#define NBODY_SRC_RENDERER_VERTEX_ARRAY_H_

#include "index_buffer.h"
#include "vertex_buffer.h"
#include <vector>

class VertexArray {
public:
  virtual ~VertexArray();

  virtual void AddVertexBuffer(VertexBuffer *vertex_buffer) = 0;
  virtual void SetIndexBuffer(IndexBuffer *indexBuffer) = 0;

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual std::vector<VertexBuffer *> GetVertexBuffers() = 0;
  virtual IndexBuffer *GetIndexBuffer() const = 0;

  static VertexArray *Create();
};

#endif // NBODY_SRC_RENDERER_VERTEX_ARRAY_H_
