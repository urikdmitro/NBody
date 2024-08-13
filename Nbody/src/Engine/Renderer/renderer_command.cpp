#include "renderer_command.h"
#include "Platform/OpenGL/opengl_renderer_api.h"
#include "renderer_api.h"

RendererAPI *RendererCommand::renderer_api_ = RendererAPI::Create();

void RendererCommand::Init() { renderer_api_->Init(); }

void RendererCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width,
                                  uint32_t height) {
  renderer_api_->SetViewport(x, y, width, height);
}

void RendererCommand::SetClearColor(const glm::vec4 &color) {
  renderer_api_->SetClearColor(color);
}

void RendererCommand::Clear() { renderer_api_->Clear(); }

void RendererCommand::DrawIndexed(VertexArray *vertexArray,
                                  uint32_t indexCount) {
  renderer_api_->DrawIndexed(vertexArray, indexCount);
}

void RendererCommand::Draw(VertexArray *vertexArray) {
  renderer_api_->Draw(vertexArray);
}

void RendererCommand::DrawLines(VertexArray *vertexArray,
                                uint32_t vertexCount) {
  renderer_api_->DrawLines(vertexArray, vertexCount);
}

void RendererCommand::SetLineWidth(float width) {
  renderer_api_->SetLineWidth(width);
}
