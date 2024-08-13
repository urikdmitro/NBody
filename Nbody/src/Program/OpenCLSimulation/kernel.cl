constant int timestep = 86400; /// 24*60*60, seconds in a day
constant float G = -6.67e-11;  // graviational constant

// kernel void nbody_force_calculation(global float *positions,
//                                     global float *velocities,
//                                     global float *masses,
//                                     global float *radiuses, int n_bodies,
//                                     float timestep) {
//
//   int id = get_global_id(0);
//   if (id > n_bodies)
//     return;
//
//   radiuses[id] += 1;
// }
kernel void nbody_force_calculation(global float *positions,
                                    global float *velocities,
                                    global float *masses,
                                    global float *radiuses, int n_bodies,
                                    float timestep) {

  const int id = get_global_id(0);
  const int id3 = id * 3;
  const int id31 = id3 + 1;
  const int id32 = id3 + 2; // saves 2 computations this way
  float acc1 = 0.0f;
  float acc2 = 0.0f;
  float acc3 = 0.0f;

  if (id < n_bodies) {
    float cPos1 = positions[id3];
    float cPos2 = positions[id31];
    float cPos3 = positions[id32];

    // for each body
    for (int i = 0; i < n_bodies; i++) {
      // calculate force for each body

      if (i == id) {
        continue;
      }
      // distance without square root
      float dis1 = cPos1 - positions[i * 3];
      float dis2 = cPos2 - positions[i * 3 + 1];
      float dis3 = cPos3 - positions[i * 3 + 2];

      float sq = dis1 * dis1 + dis2 * dis2 + dis3 * dis3;
      float distance = sqrt(sq);

      // if (radiuses[id] + radiuses[i] < distance) {
      //   radiuses[id] += radiuses[i];
      //   radiuses[i] = 0;
      //
      //   acc1 = (masses[id] * velocities[id3] + masses[i] * velocities[3 * i])
      //   /
      //          (masses[id] + masses[i]);
      //   acc2 = (masses[id] * velocities[id31] +
      //           masses[i] * velocities[3 * i + 1]) /
      //          (masses[id] + masses[i]);
      //
      //   acc3 = (masses[id] * velocities[id32] +
      //           masses[i] * velocities[3 * i + 2]) /
      //          (masses[id] + masses[i]);
      //   break;
      // }

      // the squared distance is needed twice
      // otherwise we have to square the sqrt again
      // using native methods for massive performance boost
      // rsqrt is inverse sqrt 1/sqrt(x)
      // masses have already been precalculated with G=6.7*10^(-11)
      // so that they don't have to be calculated multiple times
      // float temp = native_divide(G * masses[i], sq) * native_rsqrt(sq);
      float temp = -(G * masses[i]) / (distance * distance * distance);

      // calculates the acceleration for the x y z and sums them up
      acc1 += dis1 * temp;
      acc2 += dis2 * temp;
      acc3 += dis3 * temp;
    }

    velocities[id3] -= acc1 * timestep;
    velocities[id31] -= acc2 * timestep;
    velocities[id32] -= acc3 * timestep;
  }
}

kernel void check_collision(global float *positions, global float *velocities,
                            global float *masses, global float *radiuses,
                            int n_bodies, float timestep) {

  const int id = get_global_id(0);
  const int id3 = id * 3;
  const int id31 = id3 + 1;
  const int id32 = id3 + 2; // saves 2 computations this way
  float acc1 = 0.0f;
  float acc2 = 0.0f;
  float acc3 = 0.0f;

  if (id < n_bodies) {
    float cPos1 = positions[id3];
    float cPos2 = positions[id31];
    float cPos3 = positions[id32];

    // for each body
    for (int i = 0; i < n_bodies; i++) {
      // calculate force for each body

      if (i == id) {
        continue;
      }
      // distance without square root
      float dis1 = cPos1 - positions[i * 3];
      float dis2 = cPos2 - positions[i * 3 + 1];
      float dis3 = cPos3 - positions[i * 3 + 2];

      float sq = dis1 * dis1 + dis2 * dis2 + dis3 * dis3;
      float distance = sqrt(sq);

      if (radiuses[id] + radiuses[i] < distance) {
        atomic_xchg(radiuses + id, radiuses[id] + radiuses[i]);
        atomic_xchg(radiuses + i, 0);

        acc1 = (masses[id] * velocities[id3] + masses[i] * velocities[3 * i]) /
               (masses[id] + masses[i]);
        acc2 = (masses[id] * velocities[id31] +
                masses[i] * velocities[3 * i + 1]) /
               (masses[id] + masses[i]);

        acc3 = (masses[id] * velocities[id32] +
                masses[i] * velocities[3 * i + 2]) /
               (masses[id] + masses[i]);
        break;
      }
    }

    barrier(CLK_GLOBAL_MEM_FENCE);

    velocities[id3] = acc1;
    velocities[id31] = acc2;
    velocities[id32] = acc3;
  }
}

kernel void nbody_update(global float *positions, global float *velocities,
                         int nrBodies, float timestep) {
  // updates positions based on velocities of a body and timestep
  //  float timestep = 86400;// seconds in a day
  int i = get_global_id(0);

  if (i < nrBodies) {
    positions[i * 3] += velocities[i * 3] * timestep;
    positions[i * 3 + 1] += velocities[i * 3 + 1] * timestep;
    positions[i * 3 + 2] += velocities[i * 3 + 2] * timestep;
  }
}
