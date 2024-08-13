#include "sequential_simulation.h"
#include <cmath>

void SequentialSimulation::OnUpdate(float time_step) {
  last_time_ += time_step_ * time_step;
  for (int i = 0; i < particles_.size(); ++i) {
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

  for (int i = 0; i < particles_.size(); ++i) {
    particles_[i].position.x +=
        (particles_[i].velocity.x * time_step_ * time_step);
    particles_[i].position.y +=
        (particles_[i].velocity.y * time_step_ * time_step);
    particles_[i].position.z +=
        (particles_[i].velocity.z * time_step_ * time_step);
  }
}

float SequentialSimulation::GetDistance(Particle a, Particle b) {
  return std::sqrt(
      ((a.position.x - b.position.x) * (a.position.x - b.position.x)) +
      ((a.position.y - b.position.y) * (a.position.y - b.position.y)) +
      ((a.position.z - b.position.z) * (a.position.z - b.position.z)));
}

Particle SequentialSimulation::Colision(Particle a, Particle b) {
  Vec velocity = {ConserveMomentum(a.mass, b.mass, a.velocity.x, b.velocity.x),
                  ConserveMomentum(a.mass, b.mass, a.velocity.y, b.velocity.y),
                  ConserveMomentum(a.mass, b.mass, a.velocity.z, b.velocity.z)};

  return {a.position, velocity, a.mass + b.mass, std::max(a.radius, b.radius)};
}
float SequentialSimulation::ConserveMomentum(float mass_a, float mass_b,
                                             float velocity_a,
                                             float velocity_b) {

  return ((mass_a * velocity_a) + (mass_b * velocity_b)) / (mass_a + mass_b);
}

Vec SequentialSimulation::VelocityInteraction(Particle a, Particle b) {
  float distance = GetDistance(a, b);
  double g = (b.mass * force_constant_ / (distance * distance * distance)) *
             time_step_;

  return {(float)(g * (a.position.x - b.position.x)),
          (float)(g * (a.position.y - b.position.y)),
          (float)(g * (a.position.z - b.position.z))};
}

bool SequentialSimulation::HasSamePosition(Particle a, Particle b) {
  return a.radius + b.radius > GetDistance(a, b);
}

/* OpenMPSimulation::OpenMPSimulation(const std::vector<CLParticle> &particles,
 * float time_step) */
/*     : particles_(particles), time_step_(time_step) {} */
