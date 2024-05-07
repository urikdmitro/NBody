#include "application.h"
#include "layer_stack.h"
#include "log.h"
#include "src/Platform/Linux/GLFW/window_glfw.h"

Application::Application() : is_running_(true) {
  Log::Init();

  window_ = new WindowGLFW({800, 600, std::string("Breakout")});
  window_->SetEventCallback(
      std::bind(&Application::OnEvent, this, std::placeholders::_1));

  // temporary
  if (!gladLoadGLLoader((GLADloadproc)window_->GetProcAddress())) {
    LOG_GLOBAL_FATAL("Failed to initialize GLAD");
  }

  LOG_GLOBAL_INFO("Application created");
}

Application::~Application() {
  delete window_;
  LOG_GLOBAL_INFO("Application destroyed");
}

void Application::Run() {
  while (is_running_) {
    glClearColor(1, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto i = layer_stack_.begin(); i != layer_stack_.end(); ++i) {
      (*i)->OnUpdate();
    }

    window_->Update();
  }
}

void Application::OnEvent(Event &event) {
  /* LOG_GLOBAL_TRACE("{0}", event.ToString()); */

  for (auto i = layer_stack_.rbegin(); i != layer_stack_.rend(); ++i) {
    (*i)->OnEvent(event);

    if (event.Handled)
      break;
  }
}
