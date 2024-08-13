#include "simulation_test.h"
#include <utility>

SimulationTest::SimulationTest(Simulation *simulation, int iteration_count)
    : simulation_(simulation), is_running_(false), iteration_(0),
      time_elapsed_(0), iteration_count_(iteration_count) {}

void SimulationTest::Begin() { is_running_ = true; }
void SimulationTest::Stop() { is_running_ = false; }

void SimulationTest::OnUpdate(float) {
  if (!is_running_)
    return;
  if (iteration_ >= iteration_count_ || simulation_ == nullptr) {
    is_running_ = false;
    return;
  }

  auto start1 = std::chrono::high_resolution_clock::now();
  simulation_->OnUpdate(1.0);
  auto end1 = std::chrono::high_resolution_clock::now();

  time_elapsed_ += end1 - start1;
  iteration_++;
}

bool SimulationTest::IsDone() { return iteration_ >= iteration_count_; }

std::pair<int, int> SimulationTest::GetStatus() {
  return std::make_pair(iteration_, iteration_count_);
}

std::chrono::duration<double> SimulationTest::GetResult() {
  return time_elapsed_;
}
