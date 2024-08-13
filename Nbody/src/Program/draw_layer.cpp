#include "draw_layer.h"
#include "Core/application.h"
#include "Core/input.h"
#include "Events/key_codes.h"
#include "Program/OpenCLSimulation/opencl_particle.h"
#include "Program/OpenCLSimulation/opencl_simulation.h"
#include "Program/sequential_simulation.h"
#include "Program/simulation.h"
#include "Renderer/camera_controller.h"
#include "Renderer/shader.h"
#include "glm/glm.hpp"
#include "imgui.h"
#include "mesh.h"
#include "simulation_utils.h"

#include "src/Program/openmp_simulation.h"

#include "Renderer/renderer.h"
#include "Renderer/renderer_command.h"
#include <ctime>
#include <iostream>
#include <ostream>
#include <string>

DrawLayer::~DrawLayer() {}

DrawLayer::DrawLayer()
    : camera_controller_(
          90,
          static_cast<float>(
              Application::GetInstance().GetWindow().GetWidth()) /
              static_cast<float>(
                  Application::GetInstance().GetWindow().GetHeight()),
          0.1, 10000),
      sequential_test(nullptr, 0), open_mp_test(nullptr, 0),
      open_cl_test(nullptr, 0) {

  simulations_.push_back(new SequentialSimulation(GenParticles(0), 0));
  combo_simulation_items_str_.push_back("None");
  current_combo_simulation_item_ = 0;
  InitGuiFields_();

  simulation_type_str_.push_back("Послідовна");
  simulation_type_str_.push_back("Паралельна з OpenMP");
  simulation_type_str_.push_back("Паралельна з OpenCL");

  shader_ =
      Shader::Create("/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/"
                     "src/Program/Assets/Shaders/basic.glsl");

  va_ = SphereMesh().GetVertexArray();
}

void DrawLayer::OnEvent(Event &event) { camera_controller_.OnEvent(event); }
void DrawLayer::OnAttach() {}

void DrawLayer::PollInput(float ts) {
  if (Input::IsKeyPressed(Key::R) && GetActiveSimulation_()) {
    GetActiveSimulation_()->OnUpdate(ts);

    time_slices_list_.push_back({GetActiveSimulation_()->GetParticles(),
                                 GetActiveSimulation_()->GetLastTime()});
  }
  if (Input::IsKeyPressed(Key::J)) {
    camera_controller_.Enable();
    show_main_menu_ = false;
  }
  if (Input::IsKeyPressed(Key::K)) {
    camera_controller_.Disable();
    show_main_menu_ = true;
  }
}

Simulation *DrawLayer::GetActiveSimulation_() {
  return simulations_.at(current_combo_simulation_item_);
}

void DrawLayer::OnUpdate(float ts) {
  sequential_test.OnUpdate(ts);
  open_cl_test.OnUpdate(ts);
  open_mp_test.OnUpdate(ts);

  PollInput(ts);
  camera_controller_.OnUpdate(ts);

  RendererCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.2, 1.0));
  RendererCommand::SetClearColor(glm::vec4(0.0, 0.0, 0.0, 1.0));
  RendererCommand::Clear();
  Renderer::BeginScene(camera_controller_.GetCamera());

  if (GetActiveSimulation_()) {
    for (int i = 0; i < GetActiveSimulation_()->GetParticles().size(); i++) {

      shader_->SetMat4(
          "u_transform",
          glm::scale(
              glm::translate(
                  glm::mat4(1.0),
                  glm::vec3(
                      GetActiveSimulation_()->GetParticles()[i].position.x /
                          distance_scale_,
                      GetActiveSimulation_()->GetParticles()[i].position.y /
                          distance_scale_,
                      GetActiveSimulation_()->GetParticles()[i].position.z /
                          distance_scale_)),

              glm::vec3(object_scale_) *
                  (GetActiveSimulation_()->GetParticles()[i].radius)));

      Renderer::Submit(shader_, va_);
    }
  }

  Renderer::EndScene();
}

void DrawLayer::OnDetach() {}

const char *ComboGetter_(void *data, int index) {
  return static_cast<std::vector<std::string> *>(data)->at(index).c_str();
}

void DrawLayer::OnImGuiRender() {

  /*ImGui::Begin("Debug", &show_scale_);*/
  /*ImGui::InputFloat("Scale", &object_scale_, 0.0, 0.0, "%f");*/
  /*ImGui::InputFloat(" ", &distance_scale_, 0.0, 0.0, "%f");*/
  /*ImGui::End();*/

  if (show_main_menu_) {
    if (ImGui::CollapsingHeader("Дії")) {
      if (ImGui::Button("Створити імітаційну модель",
                        ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
        show_create_simulation_window = true;
        time_slices_list_.clear();
      }
      if (ImGui::Button("Тест швидкості",
                        ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
        show_tests_window = true;
      }
      if (ImGui::Button(paused ? "Відновити" : "Пауза",
                        ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
        paused = !paused;
      }
      if (ImGui::Button("Записати в файл",
                        ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
        writeToFile(
            "/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/result.data",
            time_slices_list_);
      }
      if (ImGui::Button("Дані за замовчуванням",
                        ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
        InitGuiFields_();
      }

      ImGui::Text("");

      ImGui::Text("Обрати активну імітаційну модель:");
      ImGui::Text("");

      ImGui::Combo("Вибір", &current_combo_simulation_item_, ComboGetter_,
                   static_cast<void *>(&combo_simulation_items_str_),
                   combo_simulation_items_str_.size());

      ImGui::Text("");
    }

    if (ImGui::CollapsingHeader("Інформація")) {
      ImGui::Text("");
      if (current_combo_simulation_item_ != 0)
        ImGui::Text("Кількість тіл: %i",
                    GetActiveSimulation_()->GetParticles().size());
      ImGui::Text("FPS: %.1f", fps);
      ImGui::Text("Час кадру: %.2f ms", frame_time);
      ImGui::Separator();
    }

    ImGui::End();

    // Показ додаткових вікон
    if (show_create_simulation_window) {
      CreateSimulation_();
    }
    if (show_tests_window) {
      RunTest_();

      if (show_tests_results_window) {
        TestResults_();
      }
    }
  }
}

void DrawLayer::CreateSimulation_() {
  ImGui::Begin("Створити імітаційну модель", &show_create_simulation_window);

  ImGui::Combo("Вибір імітаційної моделі", &curr_sim_type_, ComboGetter_,
               static_cast<void *>(&simulation_type_str_),
               simulation_type_str_.size());

  ImGui::InputInt("Кількість частинок", &num_particles_);
  ImGui::Text("");
  ImGui::InputFloat3("Границі (а.о.)", bounds_);
  ImGui::Text("");
  ImGui::InputFloat2("Маса (М.С.)", mass_);
  ImGui::InputFloat("Швидкість (км/с)", &acceleration_);
  ImGui::InputFloat2("Радіус (а.о.)", radius_);
  ImGui::InputDouble("Часовий крок", &time_step_);

  ImGui::Text("");
  ImGui::Text("");

  TimeSlice time_slice;

  if (ImGui::Button("Зчитати з файлу",
                    ImVec2(ImGui::GetContentRegionAvail().x, 0))) {

    time_slice = readFromFile(
        "/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/input.data");

    if (curr_sim_type_ == 0) {
      simulations_.push_back(
          new SequentialSimulation(time_slice.particles, time_slice.time));

    } else if (curr_sim_type_ == 1) {

      simulations_.push_back(
          new OpenMPSimulation(time_slice.particles, time_slice.time));

    } else if (curr_sim_type_ == 2) {
      simulations_.push_back(
          new OpenCLSimulation(time_slice.particles, time_slice.time));
    }

    combo_simulation_items_str_.push_back(
        std::string("Model") +
        std::to_string(combo_simulation_items_str_.size()));
    show_create_simulation_window = false;

    current_combo_simulation_item_ = combo_simulation_items_str_.size() - 1;
  }

  if (ImGui::Button("Створити", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
    time_slice.particles =
        GenParticles(num_particles_, {bounds_[0], bounds_[1], bounds_[2]},
                     mass_, acceleration_, radius_, time_step_);
    time_slice.time = time_step_;

    if (curr_sim_type_ == 0) {
      simulations_.push_back(
          new SequentialSimulation(time_slice.particles, time_slice.time));

    } else if (curr_sim_type_ == 1) {

      simulations_.push_back(
          new OpenMPSimulation(time_slice.particles, time_slice.time));

    } else if (curr_sim_type_ == 2) {
      simulations_.push_back(
          new OpenCLSimulation(time_slice.particles, time_slice.time));
    }

    combo_simulation_items_str_.push_back(
        std::string("Model") +
        std::to_string(combo_simulation_items_str_.size()));
    show_create_simulation_window = false;

    current_combo_simulation_item_ = combo_simulation_items_str_.size() - 1;
  }

  ImGui::End();
}

void DrawLayer::RunTest_() {
  ImGui::Begin("Тести", &show_tests_window);

  ImGui::InputInt("Кількість частинок", &num_particles_);
  ImGui::InputFloat3("Границі (а.о.)", bounds_);
  ImGui::InputFloat2("Маса (М.С.)", mass_);
  ImGui::InputFloat("Швидкість (км/с)", &acceleration_);
  ImGui::InputFloat2("Радіус (а.о.)", radius_);
  ImGui::InputDouble("Часовий крок", &time_step_);
  ImGui::InputInt("Кількість ітерацій", &num_iterations_);

  if (ImGui::Button("Почати тест",
                    ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
    show_tests_results_window = true;
    test_status_ = 1;

    auto particles =
        GenParticles(num_particles_, {bounds_[0], bounds_[1], bounds_[2]},
                     mass_, acceleration_, radius_, time_step_);

    sequential_test = SimulationTest(
        new SequentialSimulation(particles, time_step_), num_iterations_);
    open_mp_test = SimulationTest(new OpenMPSimulation(particles, time_step_),
                                  num_iterations_);
    open_cl_test = SimulationTest(new OpenCLSimulation(particles, time_step_),
                                  num_iterations_);

    sequential_test.Begin();
  }

  ImGui::End();
}

void DrawLayer::InitGuiFields_() {
  num_particles_ = 4000;
  bounds_[0] = 10.0f;
  bounds_[1] = 10.0f;
  bounds_[2] = 10.0f;
  mass_[0] = 0.001f;
  mass_[1] = 10.0f;
  acceleration_ = 1000.0f;
  radius_[0] = 0.005f;
  radius_[1] = 0.05f;
  time_step_ = 0.0001f;
  num_iterations_ = 100;
  block_program_ = false;
}

void DrawLayer::TestResults_() {
  ImGui::Begin("Результати тестів", &show_tests_results_window);

  switch (test_status_) {
  case 1:
    if (sequential_test.IsDone()) {
      ImGui::Text("Sequential test. Result: %f s",
                  sequential_test.GetResult().count());

      test_status_ = 2;
      open_mp_test.Begin();
    } else {
      auto status = sequential_test.GetStatus();

      ImGui::Text("Sequential test. In process: %i%%",
                  100 * status.first / status.second);
    }
    break;

  case 2:
    if (open_mp_test.IsDone()) {
      ImGui::Text("Sequential test. Result: %f s",
                  sequential_test.GetResult().count());
      ImGui::Text("OpenMP test. Result:     %f s",
                  open_mp_test.GetResult().count());

      test_status_ = 3;
      open_cl_test.Begin();
    } else {
      auto status = open_mp_test.GetStatus();

      ImGui::Text("Sequential test. Result: %f s",
                  sequential_test.GetResult().count());
      ImGui::Text("OpenMP test. In process: %i%%",
                  100 * status.first / status.second);
    }
    break;

  case 3:
    if (open_cl_test.IsDone()) {
      ImGui::Text("Sequential test. Result: %f s",
                  sequential_test.GetResult().count());
      ImGui::Text("OpenMP test. Result:     %f s",
                  open_mp_test.GetResult().count());
      ImGui::Text("OpenCL test. Result:     %f s",
                  open_cl_test.GetResult().count());

    } else {
      auto status = open_cl_test.GetStatus();

      ImGui::Text("Sequential test. Result: %f s",
                  sequential_test.GetResult().count());
      ImGui::Text("OpenMP test. Result:     %f s",
                  open_mp_test.GetResult().count());
      ImGui::Text("OpenCL test. In process: %i%%",
                  100 * status.first / status.second);
    }
    break;

  default:
    ImGui::Text("No active tests");
  }

  if (ImGui::Button("Закрити")) {
    show_tests_results_window = false;
    show_tests_window = false;
    test_status_ = 0;
  }

  ImGui::End();
}
