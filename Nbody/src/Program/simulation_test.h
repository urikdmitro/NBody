#ifndef INCLUDE_PROGRAM_SIMULATION_TEST_H_
#define INCLUDE_PROGRAM_SIMULATION_TEST_H_

#include "Program/simulation.h"
#include <chrono>

class SimulationTest {

public:
  SimulationTest(Simulation *simulation, int iteration_count);

  void Begin();
  void Stop();

  void OnUpdate(float);
  bool IsDone();

  std::pair<int, int> GetStatus();
  std::chrono::duration<double> GetResult();

private:
  int iteration_;
  int iteration_count_;
  std::chrono::duration<double> time_elapsed_;
  bool is_running_;
  Simulation *simulation_;
};

#endif // INCLUDE_PROGRAM_SIMULATION_TEST_H_
