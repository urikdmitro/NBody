#include "imgui_layer.h"
#include "Events/key_codes.h"
#include "GLFW/glfw3.h"
#include "application.h"

#include "Events/event_dispatcher.h"
#include "Events/key_events.h"
#include "Events/mouse_events.h"
#include "Events/window_events.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"
#include "imgui.h"
#include "vendor/imgui/backends/imgui_impl_glfw.h"
#include <iostream>
#include <ostream>

ImGuiLayer::ImGuiLayer() : time_step_(0.0f) {}
ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::OnAttach() {
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  io.BackendFlags |=
      ImGuiBackendFlags_HasMouseCursors | ImGuiBackendFlags_HasSetMousePos;

  ImGui::StyleColorsDark();

  float font_size = 18;
  ImFont *font_body = io.Fonts->AddFontFromFileTTF(
      "/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/assets/fonts/"
      "roboto/Roboto-Regular.ttf",
      18.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());

  io.FontDefault = font_body;

  auto &window = Application::GetInstance().GetWindow();
  ImGui_ImplGlfw_InitForOpenGL(
      static_cast<GLFWwindow *>(window.GetNativeWindow()), true);

  ImGui_ImplOpenGL3_Init();
}

void ImGuiLayer::OnDetach() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiLayer::Begin() {
  ImGuiIO &io = ImGui::GetIO();
  io.DeltaTime = time_step_;

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}
void ImGuiLayer::End() {
  ImGuiIO &io = ImGui::GetIO();

  io.DisplayFramebufferScale = ImVec2(1, 1);
  Application &application = Application::GetInstance();
  io.DisplaySize =
      ImVec2(static_cast<float>(application.GetWindow().GetWidth()) /
                 io.DisplayFramebufferScale.x,
             static_cast<float>(application.GetWindow().GetHeight()) /
                 io.DisplayFramebufferScale.y);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnUpdate(float ts) { time_step_ = ts; }

void ImGuiLayer::OnEvent(Event &event) {

  EventDispatcher dispatcher(event);

  dispatcher.Dispatch<MouseButtonReleasedEvent>(
      BIND_EVENT(OnMouseButtonReleasedEvent));

  dispatcher.Dispatch<MouseButtonPressedEvent>(
      BIND_EVENT(OnMouseButtonPressedEvent));

  dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT(OnMouseMovedEvent));
  dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT(OnMouseScrolledEvent));
  dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT(OnKeyPressedEvent));
  dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT(OnKeyReleasedEvent));
  dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT(OnKeyTypedEvent));
}

bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.MouseDown[event.GetMouseButtonCode()] = true;

  return false;
}

bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event) {

  ImGuiIO &io = ImGui::GetIO();
  io.MouseDown[event.GetMouseButtonCode()] = false;

  return false;
}

bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &event) {

  ImGuiIO &io = ImGui::GetIO();
  io.MousePos = ImVec2(event.GetX() / io.DisplayFramebufferScale.x,
                       event.GetY() / io.DisplayFramebufferScale.y);

  return false;
}

bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &event) {

  ImGuiIO &io = ImGui::GetIO();
  io.MouseWheelH = event.GetXOffset();
  io.MouseWheel = event.GetYOffset();

  return false;
}

bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.KeysDown[event.GetKeyCode()] = true;

  io.KeyCtrl = io.KeysDown[Key::LeftControl] || io.KeysDown[Key::RightControl];
  io.KeyAlt = io.KeysDown[Key::LeftAlt] || io.KeysDown[Key::RightAlt];
  io.KeySuper = io.KeysDown[Key::LeftSuper] || io.KeysDown[Key::RightSuper];
  io.KeyShift = io.KeysDown[Key::LeftShift] || io.KeysDown[Key::RightShift];

  return false;
}

bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.KeysDown[event.GetKeyCode()] = false;

  io.KeyCtrl = io.KeysDown[Key::LeftControl] || io.KeysDown[Key::RightControl];
  io.KeyAlt = io.KeysDown[Key::LeftAlt] || io.KeysDown[Key::RightAlt];
  io.KeySuper = io.KeysDown[Key::LeftSuper] || io.KeysDown[Key::RightSuper];
  io.KeyShift = io.KeysDown[Key::LeftShift] || io.KeysDown[Key::RightShift];
  return false;
}

bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.AddInputCharacter((unsigned int)event.GetKeyCode());

  return false;
}

bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.DisplaySize = io.DisplaySize = ImVec2(
      static_cast<float>(event.GetWidth()) / io.DisplayFramebufferScale.x,
      static_cast<float>(event.GetHeight()) / io.DisplayFramebufferScale.y);

  return false;
}
