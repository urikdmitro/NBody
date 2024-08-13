#ifndef NBODY_SRC_RENDERER_VERTEX_BUFFER_H_
#define NBODY_SRC_RENDERER_VERTEX_BUFFER_H_

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

enum class ShaderDataType {
  None = 0,
  Float,
  Float2,
  Float3,
  Float4,
  Mat3,
  Mat4,
  Int,
  Int2,
  Int3,
  Int4,
  Bool
};

static uint32_t ShaderDataTypeSize(ShaderDataType type);

//
//
//

struct BufferElement {
  std::string name;
  ShaderDataType type;
  uint32_t size;
  uint32_t offset;
  bool is_normalized;

  //
  BufferElement() = default;
  BufferElement(ShaderDataType type, const std::string &name,
                bool normalized = false);

  uint32_t GetComponentCount() const;
};

//
//
//

class BufferLayout {
public:
  BufferLayout();
  BufferLayout(std::initializer_list<BufferElement> elements);

  uint32_t GetStride() const;
  const std::vector<BufferElement> &GetElements() const;

  std::vector<BufferElement>::iterator begin();
  std::vector<BufferElement>::iterator end();
  std::vector<BufferElement>::const_iterator cbegin() const;
  std::vector<BufferElement>::const_iterator cend() const;

private:
  std::vector<BufferElement> elements_;
  uint32_t stride_ = 0;

  void CalculateOffsetsAndStride();
};

//
//
//

class VertexBuffer {
public:
  virtual ~VertexBuffer();

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual const BufferLayout &GetLayout() const = 0;
  virtual void SetLayout(const BufferLayout &layout) = 0;

  static VertexBuffer *Create(const void *data, size_t size);
};

#endif // NBODY_SRC_RENDERER_VERTEX_BUFFER_H_
