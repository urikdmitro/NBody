
#include "openmp_simulation.h"
#include <cmath>

OpenMPSimulation::OpenMPSimulation(const std::vector<Particle> &particles,
                                   float time_step)

    : particles_(particles), time_step_(time_step) {}

const std::vector<Particle> &OpenMPSimulation::GetParticles() const {
  return particles_;
}

void OpenMPSimulation::OnUpdate(float time_step) {
  last_time_ += time_step * time_step_;

#pragma omp parallel for schedule(static, 1)
  for (int i = 0; i < particles_.size(); ++i) {
#pragma omp parallel for
    for (int j = 0; j < particles_.size(); ++j) {
      if (i != j) {
        if (HasSamePosition(particles_[i], particles_[j]) && false) {
          particles_[i] = Colision(particles_[i], particles_[j]);
          particles_.erase(particles_.begin() + j);

        } else {
          Vec velocity = VelocityInteraction(particles_[i], particles_[j]);

          particles_[i].velocity.x -= velocity.x;
          particles_[i].velocity.y -= velocity.y;
          particles_[i].velocity.z -= velocity.z;
        }
      }
    }
  }

#pragma omp parallel for
  for (int i = 0; i < particles_.size(); ++i) {
    particles_[i].position.x +=
        (particles_[i].velocity.x * time_step_ * time_step);
    particles_[i].position.y +=
        (particles_[i].velocity.y * time_step_ * time_step);
    particles_[i].position.z +=
        (particles_[i].velocity.z * time_step_ * time_step);
  }
}

float OpenMPSimulation::GetDistance(Particle a, Particle b) {
  return std::sqrt(
      ((a.position.x - b.position.x) * (a.position.x - b.position.x)) +
      ((a.position.y - b.position.y) * (a.position.y - b.position.y)) +
      ((a.position.z - b.position.z) * (a.position.z - b.position.z)));
}

Particle OpenMPSimulation::Colision(Particle a, Particle b) {
  Vec velocity = {ConserveMomentum(a.mass, b.mass, a.velocity.x, b.velocity.x),
                  ConserveMomentum(a.mass, b.mass, a.velocity.y, b.velocity.y),
                  ConserveMomentum(a.mass, b.mass, a.velocity.z, b.velocity.z)};

  return {a.position, velocity, a.mass + b.mass, std::max(a.radius, b.radius)};
}
float OpenMPSimulation::ConserveMomentum(float mass_a, float mass_b,
                                         float velocity_a, float velocity_b) {

  return ((mass_a * velocity_a) + (mass_b * velocity_b)) / (mass_a + mass_b);
}

Vec OpenMPSimulation::VelocityInteraction(Particle a, Particle b) {
  float distance = GetDistance(a, b);
  double g = (b.mass * force_constant_ / (distance * distance * distance)) *
             time_step_;

  return {float(g * (a.position.x - b.position.x)),
          float(g * (a.position.y - b.position.y)),
          float(g * (a.position.z - b.position.z))};
}

bool OpenMPSimulation::HasSamePosition(Particle a, Particle b) {
  return a.radius + b.radius > GetDistance(a, b);
}
