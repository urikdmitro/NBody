#include "./opencl_simulation.h"
#include "Core/log.h"
#include "src/Program/OpenCLSimulation/opencl_particle.h"
#include <CL/cl.h>
#include <CL/cl2.hpp>
#include <cstdio>
#include <execution>
#include <fstream>

#include "opencl_simulation.h"
#include <fstream>
#include <iostream>
#include <sstream>

OpenCLSimulation::OpenCLSimulation(const std::vector<Particle> &particles,
                                   float time_step)
    : particles_(particles), time_step_(time_step) {
  size_ = particles_.size();
  velocities_ = new float[particles_.size() * 3];
  positions_ = new float[particles_.size() * 3];
  masses_ = new float[particles_.size()];
  radiuses_ = new float[particles_.size()];

  InitOpenCL();
}

void OpenCLSimulation::ToCL() {
  for (int i = 0; i < size_; ++i) {
    velocities_[3 * i] = particles_[i].velocity.x;
    velocities_[3 * i + 1] = particles_[i].velocity.y;
    velocities_[3 * i + 2] = particles_[i].velocity.z;

    positions_[3 * i] = particles_[i].position.x;
    positions_[3 * i + 1] = particles_[i].position.y;
    positions_[3 * i + 2] = particles_[i].position.z;
  }

  for (int i = 0; i < size_; ++i) {
    masses_[i] = particles_[i].mass;
    radiuses_[i] = particles_[i].radius;
  }
}

void OpenCLSimulation::FromCL() {
  for (int i = 0; i < size_; ++i) {
    particles_[i].velocity.x = velocities_[3 * i];
    particles_[i].velocity.y = velocities_[3 * i + 1];
    particles_[i].velocity.z = velocities_[3 * i + 2];

    particles_[i].position.x = positions_[3 * i];
    particles_[i].position.y = positions_[3 * i + 1];
    particles_[i].position.z = positions_[3 * i + 2];
  }

  for (int i = 0; i < size_; ++i) {
    particles_[i].mass = masses_[i];
    particles_[i].radius = radiuses_[i];
  }
}

const std::vector<Particle> &OpenCLSimulation::GetParticles() const {
  return particles_;
}

void OpenCLSimulation::InitOpenCL() {
  try {
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    context_ = cl::Context(CL_DEVICE_TYPE_GPU);
    queue_ = cl::CommandQueue(context_, CL_QUEUE_PROFILING_ENABLE);

    std::ifstream sourceFile("/home/dmitro/Documents/Projects/C/NBodyProject/"
                             "Nbody/src/Program/OpenCLSimulation/kernel.cl");
    std::string sourceCode((std::istreambuf_iterator<char>(sourceFile)),
                           std::istreambuf_iterator<char>());
    cl::Program::Sources sources;
    sources.push_back({sourceCode.c_str(), sourceCode.length()});

    program_ = cl::Program(context_, sources);
    program_.build();

    interaction_kernel_ = cl::Kernel(program_, "nbody_force_calculation");
    update_kernel_ = cl::Kernel(program_, "nbody_update");
    check_collision_kernel_ = cl::Kernel(program_, "check_collision");

    velocities_buffer_ =
        cl::Buffer(context_, CL_MEM_READ_WRITE, sizeof(float) * 3 * size_);
    positions_buffer_ =
        cl::Buffer(context_, CL_MEM_READ_WRITE, sizeof(float) * 3 * size_);
    masses_buffer_ =
        cl::Buffer(context_, CL_MEM_READ_WRITE, sizeof(float) * size_);
    radiuses_buffer_ =
        cl::Buffer(context_, CL_MEM_READ_ONLY, sizeof(float) * size_);

  } catch (cl::Error &err) {
    LOG_GLOBAL_ERROR("OpenCL Error: {0} ({1})", err.what(), err.err());
  } catch (std::exception &e) {
    LOG_GLOBAL_ERROR("Global Error: {0}", e.what());
  } catch (...) {
    LOG_GLOBAL_ERROR("Unknown Error");
  }
}

void OpenCLSimulation::OnUpdate(float time_step) {
  last_time_ += time_step * time_step_;
  float time = time_step_ * time_step;

  try {
    ToCL();

    queue_.enqueueWriteBuffer(positions_buffer_, CL_TRUE, 0,
                              sizeof(float) * 3 * particles_.size(),
                              positions_);
    queue_.enqueueWriteBuffer(velocities_buffer_, CL_TRUE, 0,
                              sizeof(float) * 3 * particles_.size(),
                              velocities_);
    queue_.enqueueWriteBuffer(masses_buffer_, CL_TRUE, 0,
                              sizeof(float) * particles_.size(), masses_);

    queue_.enqueueWriteBuffer(radiuses_buffer_, CL_TRUE, 0,
                              sizeof(float) * particles_.size(), radiuses_);

    cl::NDRange global(size_);
    cl::NDRange local(1);

    check_collision_kernel_.setArg(0, positions_buffer_);
    check_collision_kernel_.setArg(1, velocities_buffer_);
    check_collision_kernel_.setArg(2, masses_buffer_);
    check_collision_kernel_.setArg(3, radiuses_buffer_);
    check_collision_kernel_.setArg(4, (int)size_);
    check_collision_kernel_.setArg(5, time);

    /*queue_.enqueueNDRangeKernel(check_collision_kernel_, cl::NullRange,
     * global,*/
    /*                            local);*/

    interaction_kernel_.setArg(0, positions_buffer_);
    interaction_kernel_.setArg(1, velocities_buffer_);
    interaction_kernel_.setArg(2, masses_buffer_);
    interaction_kernel_.setArg(3, radiuses_buffer_);
    interaction_kernel_.setArg(4, (int)size_);
    interaction_kernel_.setArg(5, time);

    queue_.enqueueNDRangeKernel(interaction_kernel_, cl::NullRange, global,
                                local);

    update_kernel_.setArg(0, positions_buffer_);
    update_kernel_.setArg(1, velocities_buffer_);
    update_kernel_.setArg(2, (int)size_);
    update_kernel_.setArg(3, time);

    queue_.enqueueNDRangeKernel(update_kernel_, cl::NullRange, global, local);

    queue_.enqueueReadBuffer(positions_buffer_, CL_TRUE, 0,
                             sizeof(float) * 3 * size_, positions_);
    queue_.enqueueReadBuffer(velocities_buffer_, CL_TRUE, 0,
                             sizeof(float) * 3 * size_, velocities_);
    queue_.enqueueReadBuffer(radiuses_buffer_, CL_TRUE, 0,
                             sizeof(float) * size_, radiuses_);

    FromCL();

    LOG_GLOBAL_INFO("dt: {}; particles.size: {}", time_step, particles_.size());
  } catch (cl::Error &err) {
    LOG_GLOBAL_ERROR("OpenCL Error: {0} ({1})", err.what(), err.err());
  }
}
