#ifndef INCLUDE_OPENCLSIMULATION_OPENCL_SIMULATION_H_
#define INCLUDE_OPENCLSIMULATION_OPENCL_SIMULATION_H_

#include "../simulation.h"
#include "src/Program/OpenCLSimulation/opencl_particle.h"
#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.h>
#include <CL/cl2.hpp>
#include <string>

class OpenCLSimulation : public Simulation {

private:
  std::vector<Particle> particles_;
  float force_constant_ = 0.0000000000667f;
  float time_step_;
  float last_time_ = 0;

  cl::Context context_;
  cl::CommandQueue queue_;
  cl::Program program_;
  cl::Kernel interaction_kernel_;
  cl::Kernel update_kernel_;
  cl::Kernel check_collision_kernel_;
  cl::Buffer particles_buffer_;
  cl::Buffer velocities_buffer_;
  cl::Buffer positions_buffer_;
  cl::Buffer masses_buffer_;
  cl::Buffer radiuses_buffer_;

  void InitOpenCL();

  float *velocities_;
  float *positions_;
  float *masses_;
  float *radiuses_;
  size_t size_;
  void ToCL();
  void FromCL();

public:
  OpenCLSimulation(const std::vector<Particle> &particles, float time_step);

  void OnUpdate(float ts) override;
  float GetLastTime() override { return last_time_; }

  const std::vector<Particle> &GetParticles() const override;
};

#endif
