#ifndef PROGRAM_SIMULATION_H_
#define PROGRAM_SIMULATION_H_

#include "Program/OpenCLSimulation/opencl_particle.h"
#include <vector>

class Simulation {
public:
  virtual const std::vector<Particle> &GetParticles() const = 0;
  virtual void OnUpdate(float ts) = 0;
  virtual float GetLastTime() = 0;
};

#endif // PROGRAM_SIMULATION_H_
