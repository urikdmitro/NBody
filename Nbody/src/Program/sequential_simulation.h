#ifndef __NBODY_NAIVE_SIMULATION_H_
#define __NBODY_NAIVE_SIMULATION_H_

#include <vector>

#include "Program/OpenCLSimulation/opencl_particle.h"
#include "simulation.h"

class SequentialSimulation : public Simulation {

private:
  std::vector<Particle> particles_;

  float force_constant_ = 0.0000000000667f;
  float time_step_;
  float last_time_ = 0;

public:
  SequentialSimulation(const std::vector<Particle> &particles, float time_step)
      : particles_(particles), time_step_(time_step) {}

  void OnUpdate(float ts) override;
  float GetLastTime() override { return last_time_; }

  const std::vector<Particle> &GetParticles() const override {
    return particles_;
  }

  float GetDistance(Particle a, Particle b);
  Vec VelocityInteraction(Particle a, Particle b);

  float ConserveMomentum(float mass_a, float mass_b, float velocity_a,
                         float velocity_b);
  Particle Colision(Particle a, Particle b);

  bool HasSamePosition(Particle a, Particle b);
};

#endif
