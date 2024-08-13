#include "application.h"
#include "Core/imgui_layer.h"
#include "Events/event.h"
#include "Events/window_events.h"
#include "GLFW/glfw3.h"
#include "Platform/Linux/GLFW/window_glfw.h"
#include "Program/OpenCLSimulation/opencl_simulation.h"
#include "Program/openmp_simulation.h"
#include "Program/sequential_simulation.h"
#include "Program/simulation.h"
#include "Renderer/renderer.h"
#include "Renderer/renderer_command.h"
#include "layer_stack.h"
#include "log.h"
#include <iostream>
#include <ostream>

#include "src/Program/simulation_utils.h"

Application *Application::instance_ = nullptr;

Application::Application() : is_running_(true) {
  instance_ = this;
  /* Setup(); */
  simulation_ = new OpenMPSimulation(GenParticles(1000), 1E-5);

  Log::Init();

  window_ = new WindowGLFW({800, 600, std::string("N body problem")});
  window_->SetEventCallback(
      std::bind(&Application::OnEvent, this, std::placeholders::_1));

  Renderer::Init();
  imgui_layer_ = new ImGuiLayer();
  PushOverlayer(imgui_layer_);

  LOG_GLOBAL_INFO("Application created");
}

Application::~Application() {
  Renderer::Shutdown();
  delete window_;

  LOG_GLOBAL_INFO("Application destroyed");
}

Application &Application::GetInstance() {
  if (instance_)
    return *instance_;
  else {
    instance_ = new Application();
    return *instance_;
  }
}

void Application::RealTime() {

  std::cout << "Choose nbody method:" << std::endl;
  std::cout << "  1. Sequential" << std::endl;
  std::cout << "  2. OpenMP" << std::endl;
  std::cout << "  3. OpenCL" << std::endl;

  int selection;
  std::cin >> selection;

  int body_amount;
  std::cout << "\nEnter bodies amount: ";
  std::cin >> body_amount;

  if (selection == 1) {
    simulation_ = new SequentialSimulation(GenParticles(body_amount), 1E-5);
  } else if (selection == 2) {
    simulation_ = new OpenMPSimulation(GenParticles(body_amount), 1E-5);
  } else if (selection == 3) {
    simulation_ = new OpenCLSimulation(GenParticles(body_amount), 1E-5);
  } else {
    std::cout << "Incorrect option!" << std::endl;
    exit(1);
  }
}

void Application::Test() {
  int body_amount;
  int iterations;

  std::cout << "Enter bodies amount: ";
  std::cin >> body_amount;

  std::cout << std::endl << "Enter iterations: ";
  std::cin >> iterations;

  auto bodies_seq = GenParticles(body_amount);
  auto bodies_mp = bodies_seq;
  auto bodies_cl = bodies_seq;

  float time = 0;
  float time_step = 1E-6;

  this->simulation_ = new SequentialSimulation(bodies_seq, 1E-6);

  std::cout << "Run Sequential test" << std::endl;
  auto start1 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; i++) {
    simulation_->OnUpdate(1.0);
  }
  auto end1 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration1 = end1 - start1;

  this->simulation_ = new OpenMPSimulation(bodies_mp, 1E-6);
  // Measure execution time for function 2
  std::cout << "Run OpenMP test" << std::endl;
  auto start2 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; i++) {
    simulation_->OnUpdate(1.0);
  }
  auto end2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration2 = end2 - start2;

  // Measure execution time for function 3
  this->simulation_ = new OpenCLSimulation(bodies_cl, 1E-6);
  std::cout << "Run OpenCL test" << std::endl;
  auto start3 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; i++) {
    simulation_->OnUpdate(1.0);
  }
  auto end3 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration3 = end3 - start3;

  std::cout << std::endl;
  std::cout << "Sequential " << duration1.count() << " seconds.\n";
  std::cout << "OpenMP     " << duration2.count() << " seconds.\n";
  std::cout << "OpenCL     " << duration3.count() << " seconds.\n";
  exit(0);
}

void Application::Setup() {

  std::cout << "Select option" << std::endl;
  std::cout << "  1. Run real time simulation" << std::endl;
  std::cout << "  2. Run tests" << std::endl;

  int selection;
  std::cin >> selection;

  if (selection == 1) {
    RealTime();
  } else if (selection == 2) {
    Test();
  } else {
    std::cout << "Incorrect option!" << std::endl;
    exit(1);
  }
}

void Application::Run() {

  while (is_running_) {
    float time = glfwGetTime();
    float timestep = time - last_frame_time_;
    last_frame_time_ = time;

    for (auto i = layer_stack_.begin(); i != layer_stack_.end(); ++i) {
      (*i)->OnUpdate(timestep);
    }

    imgui_layer_->Begin();
    for (auto i = layer_stack_.begin(); i != layer_stack_.end(); ++i) {
      (*i)->OnImGuiRender();
    }
    imgui_layer_->End();

    window_->Update();

    double sleep_time = 1.0 / 60.0 - timestep;

    // If the time to sleep is positive, sleep for that duration
    if (sleep_time > 0) {
      std::this_thread::sleep_for(std::chrono::duration<double>(sleep_time));
    }
  }
}

WindowI &Application::GetWindow() { return *window_; }

void Application::OnEvent(Event &event) {
  /* LOG_GLOBAL_TRACE("{0}", event.ToString()); */
  if (event.GetEventType() == EventType::kWindowClosed) {
    is_running_ = false;
  }

  if (event.GetEventType() == EventType::kWindowResized) {
    auto window_resize_event = static_cast<WindowResizeEvent &>(event);
    RendererCommand::SetViewport(0, 0, window_resize_event.GetWidth(),
                                 window_resize_event.GetHeight());
  }

  for (auto i = layer_stack_.rbegin(); i != layer_stack_.rend(); ++i) {
    (*i)->OnEvent(event);

    if (event.Handled)
      break;
  }
}

void Application::PushLayer(Layer *layer) {
  layer_stack_.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverlayer(Layer *layer) {
  layer_stack_.PushOverlayer(layer);
  layer->OnAttach();
}
