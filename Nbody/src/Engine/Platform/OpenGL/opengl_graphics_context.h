#ifndef NBODY_SRC_PLATFORM_OPENGL_GRAPHICS_CONTEXT_
#define NBODY_SRC_PLATFORM_OPENGL_GRAPHICS_CONTEXT_

#include "GLFW/glfw3.h"
#include "Renderer/graphics_context.h"

class OpenGLGraphicsContext : public GraphicsContext {
public:
  ~OpenGLGraphicsContext() override;
  OpenGLGraphicsContext(GLFWwindow *glfw_window);

  void Init() override;
  void SwapBuffers() override;

private:
  GLFWwindow *glfw_window_;
};

#endif // NBODY_SRC_PLATFORM_OPENGL_GRAPHICS_CONTEXT_
