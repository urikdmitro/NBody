#ifndef NBODY_SRC_RENDERER_INDEX_BUFFER_
#define NBODY_SRC_RENDERER_INDEX_BUFFER_

class IndexBuffer {
public:
  virtual ~IndexBuffer();

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual int GetCount() const = 0;

  static IndexBuffer *Create(unsigned int *indices, int count);
};

#endif // NBODY_SRC_RENDERER_INDEX_BUFFER_
