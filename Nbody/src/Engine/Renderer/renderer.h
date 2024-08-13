#ifndef NBODY_SRC_RENDERER_RENDERER_H_
#define NBODY_SRC_RENDERER_RENDERER_H_

#include "camera.h"
#include "renderer_api.h"
#include "shader.h"

class Renderer {
public:
  static void Init();
  static void Shutdown();

  static void OnWindowResize(uint32_t width, uint32_t height);

  static void BeginScene(EditorCamera &camera);
  static void EndScene();

  static void Submit(Shader *shader, VertexArray *vertexArray,
                     const glm::mat4 &transform = glm::mat4(1.0f));

  static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

private:
  struct SceneData {
    glm::mat4 view_projection_matrix;
  };

  static SceneData *scene_data;
};
#endif // NBODY_SRC_RENDERER_RENDERER_H_
