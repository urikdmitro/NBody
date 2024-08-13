#include "renderer.h"
#include "renderer_command.h"

Renderer::SceneData *Renderer::scene_data = new Renderer::SceneData();

void Renderer::Init() { RendererCommand::Init(); }

void Renderer::Shutdown() {}

void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
  RendererCommand::SetViewport(0, 0, width, height);
}

void Renderer::BeginScene(EditorCamera &camera) {
  scene_data->view_projection_matrix = camera.GetViewProjection();
}

void Renderer::EndScene() {}

void Renderer::Submit(Shader *shader, VertexArray *vertexArray,
                      const glm::mat4 &transform) {
  shader->Bind();
  shader->SetMat4("u_ViewProjection", scene_data->view_projection_matrix);
  shader->SetMat4("u_Transform", transform);

  vertexArray->Bind();
  if (vertexArray->GetIndexBuffer())
    RendererCommand::DrawIndexed(vertexArray);
  else
    RendererCommand::Draw(vertexArray);
}
