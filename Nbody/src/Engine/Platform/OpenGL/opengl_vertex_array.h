#ifndef NBODY_SRC_RENDERER_OPENGL_VERTEX_ARRAY_H_
#define NBODY_SRC_RENDERER_OPENGL_VERTEX_ARRAY_H_

#include "Renderer/vertex_array.h"
#include "Renderer/vertex_buffer.h"
#include "glad/glad.h"
#include <vector>

class OpenGLVertexArray : public VertexArray {
private:
  GLuint id_;
  GLuint
      vertex_attribute_index_pointer_; // points to last active attribute index

  std::vector<VertexBuffer *> vertex_buffers_;
  IndexBuffer *index_buffer_ = nullptr;

  void AddFloatVertexBuffer_(const BufferLayout &layout,
                             const BufferElement &element);
  void AddIntVertexBuffer_(const BufferLayout &layout,
                           const BufferElement &element);
  void AddMatVertexBuffer_(const BufferLayout &layout,
                           const BufferElement &element);

public:
  OpenGLVertexArray();
  ~OpenGLVertexArray() override;

  void AddVertexBuffer(VertexBuffer *vertex_buffer) override;
  void SetIndexBuffer(IndexBuffer *index_buffer) override;

  void Bind() const override;
  void Unbind() const override;

  std::vector<VertexBuffer *> GetVertexBuffers() override;
  IndexBuffer *GetIndexBuffer() const override;
};

#endif // NBODY_SRC_RENDERER_OPENGL_VERTEX_ARRAY_H_
