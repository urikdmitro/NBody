#include "window_glfw.h"
//
#include "Events/key_events.h"
#include "Events/mouse_events.h"
#include "Events/window_events.h"
#include "GLFW/glfw3.h"
#include "Platform/OpenGL/opengl_graphics_context.h"

//
//
//

WindowGLFW::WindowGLFW(const WindowProperties &window_properties) {
  data_.properties = window_properties;
  data_.glfw_window_ = nullptr;
  data_.event_callback_ = nullptr;

  glfwInit();

  data_.glfw_window_ =
      glfwCreateWindow(data_.properties.width, data_.properties.height,
                       data_.properties.title.c_str(), nullptr, nullptr);

  glfwSetWindowUserPointer(data_.glfw_window_, &data_);

  opengl_graphics_context_ = new OpenGLGraphicsContext(data_.glfw_window_);
  opengl_graphics_context_->Init();

  glfwSetWindowSizeCallback(data_.glfw_window_, WindowSizeCallback);
  glfwSetWindowCloseCallback(data_.glfw_window_, WindowCloseCallback);
  glfwSetKeyCallback(data_.glfw_window_, KeyCallback);
  glfwSetMouseButtonCallback(data_.glfw_window_, MouseButtonCallback);
  glfwSetScrollCallback(data_.glfw_window_, MouseScrollCallback);
  glfwSetCursorPosCallback(data_.glfw_window_, CursorPosCallback);

  /* glfwSetCharCallback( */
  /*     data_.glfw_window_, [](GLFWwindow *window, unsigned int keycode) { */
  /*       WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
   */
  /**/
  /*       KeyTypedEvent event(keycode); */
  /*       data.event_callback_(event); */
  /*     }); */

  glfwSetFramebufferSizeCallback(data_.glfw_window_, nullptr);
}

//
//
//

WindowGLFW::~WindowGLFW() {
  delete opengl_graphics_context_;
  glfwDestroyWindow(data_.glfw_window_);
  glfwTerminate();
}

//
//
//

int WindowGLFW::GetWidth() { return data_.properties.width; }

//
//
//

int WindowGLFW::GetHeight() { return data_.properties.height; }

//
//
//

void WindowGLFW::Update() {
  opengl_graphics_context_->SwapBuffers();
  glfwPollEvents();
}

//
//
//

void WindowGLFW::SetEventCallback(const EventCallback &event_callback) {
  data_.event_callback_ = event_callback;
}

//
//
//

void WindowGLFW::WindowSizeCallback(GLFWwindow *glfw_window, int width,
                                    int height) {
  WindowData &window_data =
      *static_cast<WindowData *>(glfwGetWindowUserPointer(glfw_window));

  window_data.properties.width = width;
  window_data.properties.height = height;

  WindowResizeEvent event(width, height);

  window_data.event_callback_(event);
}

//
//
//

void WindowGLFW::WindowCloseCallback(GLFWwindow *glfw_window) {
  WindowData &window_data =
      *static_cast<WindowData *>(glfwGetWindowUserPointer(glfw_window));

  WindowCloseEvent event;
  window_data.event_callback_(event);
}

//
//
//

void WindowGLFW::KeyCallback(GLFWwindow *glfw_window, int key, int scancode,
                             int action, int mods) {
  WindowData &window_data =
      *static_cast<WindowData *>(glfwGetWindowUserPointer(glfw_window));

  switch (action) {
  case GLFW_PRESS: {
    KeyPressedEvent event(key, 0);
    window_data.event_callback_(event);
    break;
  }
  case GLFW_RELEASE: {
    KeyReleasedEvent event(key);
    window_data.event_callback_(event);

    break;
  }
  case GLFW_REPEAT: {
    KeyPressedEvent event(key, 1);
    window_data.event_callback_(event);
    break;
  }
  }
}

//
//
//

//
//
//

void WindowGLFW::MouseButtonCallback(GLFWwindow *glfw_window, int button,
                                     int action, int mods) {
  WindowData &window_data =
      *static_cast<WindowData *>(glfwGetWindowUserPointer(glfw_window));

  switch (action) {
  case GLFW_PRESS: {
    MouseButtonPressedEvent event(button);
    window_data.event_callback_(event);
    break;
  }
  case GLFW_RELEASE: {
    MouseButtonReleasedEvent event(button);
    window_data.event_callback_(event);

    break;
  }
  }
}

//
//
//

void WindowGLFW::MouseScrollCallback(GLFWwindow *glfw_window, double x_offset,
                                     double y_offset) {
  WindowData &window_data =
      *static_cast<WindowData *>(glfwGetWindowUserPointer(glfw_window));

  MouseScrolledEvent event(x_offset, y_offset);
  window_data.event_callback_(event);
}

//
//
//

void WindowGLFW::CursorPosCallback(GLFWwindow *glfw_window, double x,
                                   double y) {
  WindowData &window_data =
      *static_cast<WindowData *>(glfwGetWindowUserPointer(glfw_window));

  MouseMovedEvent event(x, y);
  window_data.event_callback_(event);
}

void *WindowGLFW::GetProcAddress() {
  return reinterpret_cast<void *>(&glfwGetProcAddress);
}

void *WindowGLFW::GetNativeWindow() {
  return static_cast<void *>(data_.glfw_window_);
}
