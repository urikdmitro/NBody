#include "glad/glad.h"
//
#include "GLFW/glfw3.h"
#include "resources.h"

//
#include "src/Core/log.h"
#include "src/Renderer/renderer.h"
#include "src/Renderer/shader.h"
#include "src/Renderer/vertex_array.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  Log::Init();
  LOG_GLOBAL_INFO("Logger initialized");
  LOG_GLOBAL_WARN("Logger initialized");
  LOG_GLOBAL_ERROR("Logger initialized");
  LOG_GLOBAL_FATAL("Logger initialized");

  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Breakout", NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  Renderer renderer;
  Shader shader = Resources::LoadShaderFromFile(
      "./../assets/shaders/debug/triangle_vs.glsl",
      "./../assets/shaders/debug/triangle_fs.glsl");

  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

  VertexArray va;
  va.AddVertexBuffer(&vertices, sizeof(vertices), 3, 3 * sizeof(float));
  va.Bind();
  shader.Bind();

  renderer.SetClearColor({0.0, 1.0, 0.0, 1.0});

  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    renderer.Clear();

    renderer.Draw(va, shader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
