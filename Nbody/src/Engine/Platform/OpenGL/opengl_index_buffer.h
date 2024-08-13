#ifndef NBODY_SRC_PLATFORM_OPENGL_OPENGL_INDEX_BUFFER_
#define NBODY_SRC_PLATFORM_OPENGL_OPENGL_INDEX_BUFFER_

#include "Renderer/index_buffer.h"
#include "glad/glad.h"

class OpenGLIndexBuffer : public IndexBuffer {
public:
  OpenGLIndexBuffer(unsigned int *indices, int count);
  ~OpenGLIndexBuffer();

  void Bind() const override;
  void Unbind() const override;

  int GetCount() const override;

private:
  GLuint id_;
  GLuint count_;
};

#endif // NBODY_SRC_PLATFORM_OPENGL_OPENGL_INDEX_BUFFER_
