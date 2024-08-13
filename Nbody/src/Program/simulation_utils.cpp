#include "simulation_utils.h"
#include "Program/OpenCLSimulation/opencl_particle.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

bool writeToFile(const std::string &filename,
                 const std::vector<TimeSlice> &a_vec) {
  std::ofstream outfile(filename);
  if (!outfile.is_open()) {
    return false;
  }

  // Write each element of a_vec
  for (const TimeSlice &a : a_vec) {
    // Write the number of particles in this A structure
    outfile << a.particles.size() << std::endl;

    // Write each particle in this A structure
    for (const Particle &particle : a.particles) {
      outfile << particle.position.x << " " << particle.position.y << " "
              << particle.position.z << " " << particle.velocity.x << " "
              << particle.velocity.y << " " << particle.velocity.z << " "
              << particle.mass << " " << particle.radius << " "
              << particle.is_exist << std::endl;
    }

    // Write the time for this A structure
    outfile << a.time << std::endl;
  }

  outfile.close();
  return true;
}

TimeSlice readFromFile(const std::string &filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    return {}; // Повертаємо порожній TimeSlice у випадку невдалого відкриття
               // файлу
  }

  TimeSlice time_slice;

  // Read the number of particles in this TimeSlice
  int num_particles;
  infile >> num_particles;

  time_slice.particles.resize(num_particles);

  // Read each particle in this TimeSlice
  for (Particle &particle : time_slice.particles) {
    infile >> particle.position.x >> particle.position.y >>
        particle.position.z >> particle.velocity.x >> particle.velocity.y >>
        particle.velocity.z >> particle.mass >> particle.radius >>
        particle.is_exist;
    if (infile.fail()) {
      break; // Error handling: reached end of file or invalid data
    }
  }

  // Read the time for this TimeSlice
  infile >> time_slice.time;

  infile.close();
  return time_slice;
}

float FloatRandom() {
  float rand = static_cast<float>(std::rand());
  return rand / RAND_MAX;
}

std::vector<Particle> GenParticles(int particles_amount_, Vec bounds,
                                   float mass_range[2], float velocity_max,
                                   float radius_range[2], float time_step) {
  srand(std::time(NULL));
  std::vector<Particle> particles_;
  particles_.reserve(particles_amount_);

  for (int i = 0; i < particles_amount_; ++i) {
    Vec position = {bounds.x * (FloatRandom()), bounds.y * (FloatRandom()),
                    bounds.z * (FloatRandom())};

    float theta = 2.0 * M_PI * FloatRandom();
    float phi = std::acos(2.0 * (FloatRandom() - 0.5));
    Vec velocity = {velocity_max * std::sin(phi) * std::cos(theta),
                    velocity_max * std::sin(phi) * std::sin(theta),
                    velocity_max * std::cos(phi)};

    float mass_fraction = FloatRandom();
    float mass = mass_range[0] * 1.989E30 * 1E-20 * (1.0 - mass_fraction) +
                 mass_range[1] * 1.989E30 * 1E-15 * mass_fraction;

    float radius_fraction = FloatRandom();
    float radius;

    radius = radius_range[0] * (1.0 - radius_fraction) +
             radius_range[1] * radius_fraction;

    Particle particle = {position, velocity, mass, radius, 1};
    particles_.push_back(particle);
  }
  /**/
  /*{*/
  /*  Vec position = {bounds.x / 2, bounds.y / 2, bounds.z / 2};*/
  /**/
  /*  float theta = 2.0 * M_PI * FloatRandom();*/
  /*  float phi = std::acos(2.0 * (FloatRandom() - 0.5));*/
  /*  Vec velocity = {velocity_max * std::sin(phi) * std::cos(theta),*/
  /*                  velocity_max * std::sin(phi) * std::sin(theta),*/
  /*                  velocity_max * std::cos(phi)};*/
  /**/
  /*  float mass = mass_range[1] * 1.989E20;*/
  /**/
  /*  float radius_fraction = FloatRandom();*/
  /*  float radius;*/
  /*  radius = radius_range[1] * 10;*/
  /**/
  /*  Particle particle = {position, velocity, mass, radius, 1};*/
  /*  particles_.push_back(particle);*/
  /*}*/
  /**/
  /*Particle sun = {{0, 0, 0}, {0, 0, 0}, 1.989E30, 6963.42, 1};*/
  /*particles_.push_back(sun);*/
  /**/
  /*Particle Earth = {{0, -696342, 0}, {0, 0, 52E3}, 5.972E24, 6371, 1};*/
  /*Earth.speed = {29.8, 0, 0};*/
  /*particles_.push_back(Earth);*/
  return particles_;
}

std::vector<Particle> GenParticles(int particles_amount_) {
  srand(std::time(NULL));

  Vec bounds = {10.0, 10.0, 10.0};
  float velocity_max = 500;
  float mass_range[2] = {0.025 * 1.989E30 * 1E-20, 100.0 * 1.989E30 * 1E-15};
  float velocity_range[2] = {-500, 500};
  float radius_range[2] = {0.005, 0.025};
  float radius_range2[2] = {0.1, 0.5};
  float time_step = 1E-6;

  std::vector<Particle> particles_;
  particles_.reserve(particles_amount_);

  for (int i = 0; i < particles_amount_; ++i) {
    Vec position = {bounds.x * (FloatRandom()), bounds.y * (FloatRandom()),
                    bounds.z * (FloatRandom())};

    float theta = 2.0 * M_PI * FloatRandom();
    float phi = std::acos(2.0 * (FloatRandom() - 0.5));
    Vec velocity = {velocity_max * std::sin(phi) * std::cos(theta),
                    velocity_max * std::sin(phi) * std::sin(theta),
                    velocity_max * std::cos(phi)};

    float mass_fraction = FloatRandom();
    float mass =
        mass_range[0] * (1.0 - mass_fraction) + mass_range[1] * mass_fraction;

    float radius_fraction = FloatRandom();
    float radius;

    radius = radius_range[0] * (1.0 - radius_fraction) +
             radius_range[1] * radius_fraction;

    Particle particle = {position, velocity, mass, radius, 1};
    particles_.push_back(particle);
  }

  return particles_;
}
