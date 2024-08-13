#ifndef NEW_SIMULATION
#define NEW_SIMULATION

#include "Program/simulation.h"
using nb_t = double;

const nb_t MinDistance = 1e-8f; //!< Minimum distance between two bodyes
const nb_t GravityConstSI = 6.67259e-11f; // m^3/(kg s^2);
const nb_t Au = 149597870700.0f;          //!< astronomical unit (m)
const nb_t Day = 86400.0f;                //!< Julian day (s)
const nb_t GravityConstAuDayKg =
    (GravityConstSI * Day * Day) / (Au * Au * Au); // au^3/(kg day^2);
const nb_t MassFactorSI = GravityConstSI;
const nb_t MassFactorAuDayKg = GravityConstAuDayKg;
/**/
/*class NewSimulation : public Simulation {*/
/*  float last_time_;*/
/*  std::vector<Particle> particles_;*/
/**/
/*public:*/
/*  const std::vector<Particle> &GetParticles() const override;*/
/*  void OnUpdate(float ts) override;*/
/*  float GetLastTime() override { return last_time_; };*/
/*};*/

#endif
