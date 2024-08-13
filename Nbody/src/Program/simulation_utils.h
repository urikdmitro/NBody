#ifndef INCLUDE_PROGRAM_UTILS_H_
#define INCLUDE_PROGRAM_UTILS_H_

#include "Program/OpenCLSimulation/opencl_particle.h"
#include <iostream>
#include <string>
#include <vector>

std::vector<Particle> GenParticles(int particles_amount_, Vec bounds,
                                   float mass_range[2], float velocity_max,
                                   float radius_range[2], float time_step);
std::vector<Particle> GenParticles(int);

typedef struct {
  std::vector<Particle> particles;
  float time;
} TimeSlice;

bool writeToFile(const std::string &filename,
                 const std::vector<TimeSlice> &a_vec);
TimeSlice readFromFile(const std::string &filename);

#endif // INCLUDE_PROGRAM_UTILS_H_
