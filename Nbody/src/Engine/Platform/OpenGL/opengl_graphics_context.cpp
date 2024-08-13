#include "opengl_graphics_context.h"
#include "glad/glad.h"

OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow *glfw_window)
    : glfw_window_(glfw_window) {}

OpenGLGraphicsContext::~OpenGLGraphicsContext() {}

void OpenGLGraphicsContext::Init() {

  glfwMakeContextCurrent(glfw_window_);

  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void OpenGLGraphicsContext::SwapBuffers() { glfwSwapBuffers(glfw_window_); }
