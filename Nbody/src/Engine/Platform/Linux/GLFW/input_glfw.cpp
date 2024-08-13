#include "Core/input.h"

#include "Core/application.h"
#include "GLFW/glfw3.h"

#define GET_GLFW_WINDOW                                                        \
  (static_cast<GLFWwindow *>(                                                  \
      Application::GetInstance().GetWindow().GetNativeWindow()))

bool Input::IsKeyPressed(KeyCode key) {
  return glfwGetKey(GET_GLFW_WINDOW, key) == GLFW_PRESS;
}

bool Input::IsKeyReleased(KeyCode key) {
  return glfwGetKey(GET_GLFW_WINDOW, key) == GLFW_RELEASE;
}

bool Input::IsMouseButtonPressed(MouseCode button) {
  auto *window = static_cast<GLFWwindow *>(
      Application::GetInstance().GetWindow().GetNativeWindow());

  return glfwGetMouseButton(GET_GLFW_WINDOW, button) == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition() {
  double x_pos, y_pos;
  glfwGetCursorPos(GET_GLFW_WINDOW, &x_pos, &y_pos);

  return {static_cast<float>(x_pos), static_cast<float>(y_pos)};
}

float Input::GetMouseX() { return GetMousePosition().x; }

float Input::GetMouseY() { return GetMousePosition().y; }

void Input::TogleMouseCursor(bool enabled) {
  if (enabled)
    glfwSetInputMode(GET_GLFW_WINDOW, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  else
    glfwSetInputMode(GET_GLFW_WINDOW, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Input::SetMousePosition(float x, float y) {
  glfwSetCursorPos(GET_GLFW_WINDOW, x, y);
}
