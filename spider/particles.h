#ifndef PARTICLES_H
#define PARTICLES_H
#include <stdlib.h>
#include <svector.h>
#include <malloc.h>
#include "worldsystem.h"

using namespace svector;

struct Particle {
  float m;   // mass
  float4 x;  // position
  float4 v;  // velocity
  float4 f;  // force
  Particle() : m(1) {}
};

class ParticleSystem {
 public:
  ParticleSystem() : world(0), p(0), n(0), t(0), dydt(0), s0(0), s1(0), g(-9.8f) {}

  ParticleSystem(WorldSystem *world, size_t num_particles)
      : world(world), n(num_particles), t(0), g(-9.8f) {
    create(num_particles);
  }

  ~ParticleSystem() { clear(); }

  void clear() {
    if (p) {
      free(p);
      p = 0;
    }
    if (dydt) {
      free(dydt);
      dydt = 0;
    }
    if (s0) {
      free(s0);
      s0 = 0;
    }
    if (s1) {
      free(s1);
      s1 = 0;
    }
  }

  void create(size_t num_particles) {
    clear();
    n = num_particles;
    t = 0;
    p = (Particle *)memalign(0x100, n * sizeof(Particle));
    dydt = (float4 *)memalign(0x100, 2 * n * sizeof(float4));
    s0 = (float4 *)memalign(0x100, 2 * n * sizeof(float4));
    s1 = (float4 *)memalign(0x100, 2 * n * sizeof(float4));
  }

  void eulerStep(float dt) {    
    computeForces();
    computeDerivative(dydt);  // dY/dt
    scaleVector(dydt, dt);    // dY/dt * dt
    getParticleState(s0);   // s0 <- p
    getParticleState(s1);   // s1 <- p
    addVectors(s1, dydt);   // s1 += dY/dt * dt;
    checkCollisions(s0, s1);
    setParticleState(s1);   // p <- s1
    t += dt;  
  }

  void checkCollisions(float4 *s0, float4 *s1) {
    Collision c;
    for (size_t i = 0; i < n; ++i) {
      if (world->checkCollision(s1[2 * i], c)) {
        float4 N = c.N;
        float d = c.d;
        float4 Vn = dot3d(p[i].v, N) * N;
        float4 Vt = p[i].v - Vn;

        if (fabs(d) > 0) {
          float4 U = p[i].v;
          U.normalize();
          float vn = Vn.norm();
          float vt = Vt.norm();
          float k = vt / vn;
          float h = sqrt(1 + k * k) * fabs(d);
          // std::cout << "i=" << i << " d=" << d << " h=" << h << " s0=" <<
          // p[i].x.str() <<  " s1=" ;
          p[i].x += -U * h;
          // std::cout << p[i].x.str() << "  U=" << U.str()<< std::endl;
        }
        // p[i].f += -friction * dot3d(p[i].f, N) * Vt;
        p[i].v = Vt - 0.3f * Vn;
      }
    }
  }

  void testParticles() {
    for (size_t i = 0; i < n; ++i) {
      float x = rand() / float(RAND_MAX) * 1 + 5;
      float y = rand() / float(RAND_MAX) * 1 + 5;
      float z = rand() / float(RAND_MAX) * 1 + 20;
      float vx = 3.8f * rand() / float(RAND_MAX) - 2;
      float vy = 3.8f * rand() / float(RAND_MAX) - 2;
      float vz = 0 * rand() / float(RAND_MAX);
      x = 5;
      y = 2.5;
      z = 10;
      vx = 0;
      vy = 0;
      vz = 0;
      p[i].m = 1;
      p[i].x = float4(x, y, z);
      p[i].v = float4(vx, vy, vz);
    }
  }

  float4 getParticlePosition(size_t id) { return p[id].x; }

  size_t getNumParticles() { return n; }

 protected:
  void getParticleState(float4 *dst) {
    for (size_t i = 0; i < n; ++i) {
      *(dst++) = p[i].x;
      *(dst++) = p[i].v;
    }
  }

  void setParticleState(float4 *src) {
    for (size_t i = 0; i < n; ++i) {
      p[i].x = *(src++);
      p[i].v = *(src++);
    }
  }

  void applyGravity() {
    for (size_t i = 0; i < n; ++i) p[i].f.z += p[i].m * g;
  }

  void applyDrag() {
    for (size_t i = 0; i < n; ++i) p[i].f += -0.1f * p[i].v;
  }

  void zeroForces() {
    for (size_t i = 0; i < n; ++i) p[i].f = 0;
  }

  void computeForces() {
    zeroForces();
    applyGravity();
    applyDrag();
  }

  void computeDerivative(float4 *dst) {
    for (size_t i = 0; i < n; ++i) {
      *(dst++) = p[i].v;
      *(dst++) = p[i].f / p[i].m;
    }
  }

  void scaleVector(float4 *dst, float k) {
    for (size_t i = 0; i < 2 * n; ++i) dst[i] *= k;
  }

  void addVectors(float4 *dst, float4 *src) {
    for (size_t i = 0; i < 2 * n; ++i) dst[i] += src[i];
  }

 private:
  WorldSystem *world;
  Particle *p;
  size_t n;
  float t;
  float4 *dydt;
  float4 *s0;
  float4 *s1;
  const float g;
};

#endif