#ifndef INCLUDE_OPENCLSIMULATION_OPENCL_PARTICLE_H_
#define INCLUDE_OPENCLSIMULATION_OPENCL_PARTICLE_H_

typedef struct Vec {
  double x;
  double y;
  double z;

  /* Vec(float x, float y, float z) : x(x), y(x), z(z) {} */
} Vec;

typedef struct {
  Vec position;
  Vec velocity;
  float mass;
  float radius;
  bool is_exist;
} Particle;

#endif // INCLUDE_OPENCLSIMULATION_OPENCL_PARTICLE_H_
