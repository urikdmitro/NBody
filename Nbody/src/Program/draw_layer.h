#ifndef NBODY_SRC_PROGRAM_DRAW_LAYER_
#define NBODY_SRC_PROGRAM_DRAW_LAYER_

#include "Core/layer.h"
#include "OpenCLSimulation/opencl_particle.h"
#include "Program/simulation.h"
#include "Renderer/camera_controller.h"
#include "Renderer/shader.h"
#include "Renderer/vertex_array.h"
#include "simulation_test.h"
#include "simulation_utils.h"
#include <forward_list>
#include <utility>

class DrawLayer : public Layer {
public:
  ~DrawLayer();
  DrawLayer();

  void OnEvent(Event &event) override;
  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(float ts) override;
  void OnImGuiRender() override;

private:
  float object_scale_ = 1;
  float distance_scale_ = 1;
  bool show_scale_ = false;

  void PollInput(float ts);
  Simulation *GetActiveSimulation_();

  VertexArray *va_;
  Shader *shader_;
  CameraController camera_controller_;
  glm::vec3 cube_position_;

  unsigned int particles_amount_ = 2000;

  std::vector<Particle> particles_;

  std::vector<Simulation *> simulations_;
  std::vector<std::string> combo_simulation_items_str_;
  int current_combo_simulation_item_ = -1;

  bool show_main_menu_ = true;
  bool show_create_simulation_window = false;
  bool show_tests_window = false;
  bool show_tests_results_window = false;
  int test_status_ = 0;

  bool paused = false;
  float fps = 60.0f;
  float frame_time = 16.67f;
  float time = 0.0f;

  int num_particles_ = 4000;

  /*float bounds_[3] = {200.0f * 149E9, 200.0f * 149E9, 200.0f * 149E9};*/
  /*float mass_[2] = {0.001f, 10.0f};*/
  /*float acceleration_ = 1000.0f;*/
  /*float radius_[2] = {0.01f * 149E9, 1.0f * 149E9};*/
  float bounds_[3] = {10.0f, 10.0f, 10.0f};
  float mass_[2] = {0.001f, 10.0f};
  float acceleration_ = 1000.0f;
  float radius_[2] = {0.005f, 0.05f};
  double time_step_ = 0.0001f;
  int num_iterations_ = 100;
  bool block_program_ = false;

  std::vector<std::string> simulation_type_str_;
  int curr_sim_type_ = 0;

  SimulationTest sequential_test;
  SimulationTest open_mp_test;
  SimulationTest open_cl_test;

  void CreateSimulation_();
  void RunTest_();
  void TestResults_();

  void InitGuiFields_();

  std::vector<TimeSlice> time_slices_list_;

  bool write_to_file_ = 0;
};

#endif // NBODY_SRC_PROGRAM_DRAW_LAYER_
