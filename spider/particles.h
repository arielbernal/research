#ifndef PARTICLES_H
#define PARTICLES_H
#include <stdlib.h>
#include <svector.h>
#include <malloc.h>
#include "worldsystem.h"

using namespace svector;

struct Particle {
  float m;         // mass
  float4 x;        // position
  float4 v;        // velocity
  float4 f;        // force
  float4 contact;  // contact force
  Particle() : m(1) {}
};


typedef  void(dydtFunc*)(float t, std::vector<float4> &y, std::vector<float4> &res);

void ODERK4Solver(float t, std::vector<float4> &y, std::vector<float4> &yf, dydtFunc *dydt) {
  yf = y;
  dydt(t, y, res);
}


class ParticleSystem {
 public:
  ParticleSystem() : world(0) {}

  ParticleSystem(WorldSystem *world, size_t num_particles)
      : world(world), n(num_particles), t(0) {
    create(num_particles);
  }

  void clear() {
    p.clear();
    y.clear();
    yf.clear();
  }

  void create(size_t num_particles) {
    clear();
    n = num_particles;
    p.resize(n);
    y.resize(2 * n);
    yf.resize(2 * n);
  }

  void testParticles() {
    for (size_t i = 0; i < n; ++i) {
      float x = rand() / float(RAND_MAX) * 2 + 6;
      float y = rand() / float(RAND_MAX) * 2 + 6;
      float z = rand() / float(RAND_MAX) * 2 + 20;
      float vx = 3.8f * rand() / float(RAND_MAX) - 2;
      float vy = 3.8f * rand() / float(RAND_MAX) - 2;
      float vz = 0 * rand() / float(RAND_MAX);
      // x = 10;
      // y = 2.5;
      // z = 25;
      // vx = 0;
      // vy = 0;
      // vz = 0;
      p[i].m = 1;
      p[i].x = float4(x, y, z);
      p[i].v = float4(vx, vy, vz);
    }
  }

  float4 getParticlePosition(size_t id) { return p[id].x; }

  size_t getNumParticles() { return n; }

 protected:
 private:
  WorldSystem *world;
  std::vector<Particle> p;
  std::vector<float4> y;
  std::vector<float4> yf;
  size_t n;
  float t;
};

#endif