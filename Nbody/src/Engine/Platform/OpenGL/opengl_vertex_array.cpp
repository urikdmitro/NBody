#include "opengl_vertex_array.h"
#include "Renderer/vertex_buffer.h"
#include "glad/glad.h"
#include <iostream>
#include <ostream>

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
  switch (type) {
  case ShaderDataType::Float:
    return GL_FLOAT;
  case ShaderDataType::Float2:
    return GL_FLOAT;
  case ShaderDataType::Float3:
    return GL_FLOAT;
  case ShaderDataType::Float4:
    return GL_FLOAT;
  case ShaderDataType::Mat3:
    return GL_FLOAT;
  case ShaderDataType::Mat4:
    return GL_FLOAT;
  case ShaderDataType::Int:
    return GL_INT;
  case ShaderDataType::Int2:
    return GL_INT;
  case ShaderDataType::Int3:
    return GL_INT;
  case ShaderDataType::Int4:
    return GL_INT;
  case ShaderDataType::Bool:
    return GL_BOOL;
  default:
    return GL_NONE;
  }

  return 0;
}

OpenGLVertexArray::OpenGLVertexArray() { glGenVertexArrays(1, &id_); }

OpenGLVertexArray::~OpenGLVertexArray() { glDeleteVertexArrays(1, &id_); }

void OpenGLVertexArray::Bind() const { glBindVertexArray(id_); }

void OpenGLVertexArray::Unbind() const { glBindVertexArray(0); }

void OpenGLVertexArray::AddVertexBuffer(VertexBuffer *vertex_buffer) {
  glBindVertexArray(id_);
  vertex_buffer->Bind();

  const auto &layout = vertex_buffer->GetLayout();

  for (auto it = layout.cbegin(); it != layout.cend(); ++it) {
    switch (it->type) {

    case ShaderDataType::Float:
    case ShaderDataType::Float2:
    case ShaderDataType::Float3:
    case ShaderDataType::Float4: {
      glEnableVertexAttribArray(vertex_attribute_index_pointer_);

      glVertexAttribPointer(vertex_attribute_index_pointer_,
                            it->GetComponentCount(),
                            ShaderDataTypeToOpenGLBaseType(it->type),
                            it->is_normalized ? GL_TRUE : GL_FALSE,
                            layout.GetStride(), //
                            reinterpret_cast<const void *>(it->offset));

      ++vertex_attribute_index_pointer_;
      break;
    }
    case ShaderDataType::Int:
    case ShaderDataType::Int2:
    case ShaderDataType::Int3:
    case ShaderDataType::Int4:
    case ShaderDataType::Bool: {
      AddIntVertexBuffer_(layout, *it);
      break;
    }
    case ShaderDataType::Mat3:
    case ShaderDataType::Mat4: {
      AddMatVertexBuffer_(layout, *it);
      break;
    }
    default:
      break;
    }
  }

  vertex_buffers_.push_back(vertex_buffer);
}

void OpenGLVertexArray::AddFloatVertexBuffer_(const BufferLayout &layout,
                                              const BufferElement &element) {
  glEnableVertexAttribArray(vertex_attribute_index_pointer_);

  glVertexAttribPointer(vertex_attribute_index_pointer_,
                        element.GetComponentCount(),
                        ShaderDataTypeToOpenGLBaseType(element.type),
                        element.is_normalized ? GL_TRUE : GL_FALSE,
                        layout.GetStride(), //
                        reinterpret_cast<const void *>(element.offset));

  ++vertex_attribute_index_pointer_;
}

void OpenGLVertexArray::AddIntVertexBuffer_(const BufferLayout &layout,
                                            const BufferElement &element) {
  glEnableVertexAttribArray(vertex_attribute_index_pointer_);

  glVertexAttribIPointer(vertex_attribute_index_pointer_,
                         element.GetComponentCount(),
                         ShaderDataTypeToOpenGLBaseType(element.type),
                         layout.GetStride(), //
                         reinterpret_cast<const void *>(element.offset));

  ++vertex_attribute_index_pointer_;
}

void OpenGLVertexArray::AddMatVertexBuffer_(const BufferLayout &layout,
                                            const BufferElement &element) {
  int count = element.GetComponentCount();

  for (int i = 0; i < count; i++) {
    glEnableVertexAttribArray(vertex_attribute_index_pointer_);

    glVertexAttribPointer(vertex_attribute_index_pointer_,              //
                          count,                                        //
                          ShaderDataTypeToOpenGLBaseType(element.type), //
                          element.is_normalized ? GL_TRUE : GL_FALSE,   //
                          layout.GetStride(),                           //
                          reinterpret_cast<const void *>(
                              element.offset + sizeof(float) * count * i));

    glVertexAttribDivisor(vertex_attribute_index_pointer_, 1);
    ++vertex_attribute_index_pointer_;
  }
}

std::vector<VertexBuffer *> OpenGLVertexArray::GetVertexBuffers() {
  return vertex_buffers_;
}

IndexBuffer *OpenGLVertexArray::GetIndexBuffer() const { return index_buffer_; }

void OpenGLVertexArray::SetIndexBuffer(IndexBuffer *index_buffer) {
  glBindVertexArray(id_);
  index_buffer->Bind();

  index_buffer_ = index_buffer;
}
