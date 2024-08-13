#ifndef NBODY_SRC_PLATFORM_LINUX_GLFW_WINDOW_H_
#define NBODY_SRC_PLATFORM_LINUX_GLFW_WINDOW_H_

// #include "GLFW/glfw3.h"
#include "Core/window.h"
#include "Renderer/graphics_context.h"

struct GLFWwindow;

class WindowGLFW : public WindowI {
private:
  struct WindowData {
    WindowProperties properties;
    GLFWwindow *glfw_window_;
    EventCallback event_callback_;
  };

  WindowData data_;
  GraphicsContext *opengl_graphics_context_;

  static void WindowCloseCallback(GLFWwindow *glfw_window);
  static void WindowSizeCallback(GLFWwindow *glfw_window, int width,
                                 int height);
  static void KeyCallback(GLFWwindow *glfw_window, int key, int scancode,
                          int action, int mods);
  static void MouseButtonCallback(GLFWwindow *glfw_window, int button,
                                  int action, int mods);
  static void MouseScrollCallback(GLFWwindow *glfw_window, double x_offset,
                                  double y_offset);
  static void CursorPosCallback(GLFWwindow *glfw_window, double x, double y);

public:
  WindowGLFW(const WindowProperties &window_properties);
  ~WindowGLFW();
  int GetWidth() override;
  int GetHeight() override;
  void Update() override;
  void SetEventCallback(const EventCallback &event_callback) override;
  void *GetProcAddress() override;
  void *GetNativeWindow() override;
};

#endif // NBODY_SRC_PLATFORM_LINUX_GLFW_WINDOW_H_
