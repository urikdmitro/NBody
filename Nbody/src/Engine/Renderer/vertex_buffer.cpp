#include "vertex_buffer.h"
#include "Core/log.h"
#include "Platform/OpenGL/opengl_vertex_buffer.h"
#include "renderer.h"
#include "renderer_api.h"

VertexBuffer *VertexBuffer::Create(const void *data, size_t size) {

  if (Renderer::GetAPI() == RendererAPI::API::None)
    return nullptr;

  if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
    return new OpenGLVertexBuffer(data, size);

  LOG_GLOBAL_FATAL("Unknown RendererAPI!");
  return nullptr;
}

uint32_t ShaderDataTypeSize(ShaderDataType type) {
  switch (type) {
  case ShaderDataType::Float:
    return 4;
  case ShaderDataType::Float2:
    return 4 * 2;
  case ShaderDataType::Float3:
    return 4 * 3;
  case ShaderDataType::Float4:
    return 4 * 4;
  case ShaderDataType::Mat3:
    return 4 * 3 * 3;
  case ShaderDataType::Mat4:
    return 4 * 4 * 4;
  case ShaderDataType::Int:
    return 4;
  case ShaderDataType::Int2:
    return 4 * 2;
  case ShaderDataType::Int3:
    return 4 * 3;
  case ShaderDataType::Int4:
    return 4 * 4;
  case ShaderDataType::Bool:
    return 1;
  default:
    return 0;
  }
}

BufferElement::BufferElement(ShaderDataType type, const std::string &name,
                             bool is_normalized)
    : name(name), type(type), size(ShaderDataTypeSize(type)), offset(0),
      is_normalized(is_normalized) {}

uint32_t BufferElement::GetComponentCount() const {
  switch (type) {
  case ShaderDataType::Float:
    return 1;
  case ShaderDataType::Float2:
    return 2;
  case ShaderDataType::Float3:
    return 3;
  case ShaderDataType::Float4:
    return 4;
  case ShaderDataType::Mat3:
    return 3; // 3* float3
  case ShaderDataType::Mat4:
    return 4; // 4* float4
  case ShaderDataType::Int:
    return 1;
  case ShaderDataType::Int2:
    return 2;
  case ShaderDataType::Int3:
    return 3;
  case ShaderDataType::Int4:
    return 4;
  case ShaderDataType::Bool:
    return 1;
  default:
    return 0;
  }
}

BufferLayout::BufferLayout() {}

BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
    : elements_(elements) {
  CalculateOffsetsAndStride();
}

uint32_t BufferLayout::GetStride() const { return stride_; }

const std::vector<BufferElement> &BufferLayout::GetElements() const {
  return elements_;
}

std::vector<BufferElement>::iterator BufferLayout::begin() {
  return elements_.begin();
}
std::vector<BufferElement>::iterator BufferLayout::end() {
  return elements_.end();
}
std::vector<BufferElement>::const_iterator BufferLayout::cbegin() const {
  return elements_.begin();
}
std::vector<BufferElement>::const_iterator BufferLayout::cend() const {
  return elements_.end();
}

void BufferLayout::CalculateOffsetsAndStride() {
  uint32_t offset = 0;
  stride_ = 0;
  for (auto &element : elements_) {
    element.offset = offset;
    offset += element.size;
    stride_ += element.size;
  }
}
VertexBuffer::~VertexBuffer() {}
