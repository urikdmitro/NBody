#ifndef NBODY_SRC_RENDERER_OPENGL_VERTEX_BUFFER_H_
#define NBODY_SRC_RENDERER_OPENGL_VERTEX_BUFFER_H_

#include "Renderer/vertex_buffer.h"
#include "glad/glad.h"

class OpenGLVertexBuffer : public VertexBuffer {
private:
  GLuint buffer_id_;
  BufferLayout layout_;

public:
  OpenGLVertexBuffer(const void *data, size_t size);
  ~OpenGLVertexBuffer();

  void Bind() const override;
  void Unbind() const override;

  const BufferLayout &GetLayout() const override;
  void SetLayout(const BufferLayout &layout) override;
};

#endif // NBODY_SRC_RENDERER_OPENGL_VERTEX_BUFFER_H_
