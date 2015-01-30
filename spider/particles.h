#ifndef PARTICLES_H
#define PARTICLES_H
#include <stdlib.h>
#include <svector.h>
#include <malloc.h>
#include "worldsystem.h"

using namespace svector;

struct Particle {
  float m;          // mass
  float4 x;         // position
  float4 v;         // velocity
  float4 f;         // force
  float4 contact;  // contact force
  Particle() : m(1) {}
};

class ParticleSystem {
 public:
  ParticleSystem()
      : world(0), p(0), n(0), t(0), dydt(0), s0(0), s1(0), g(-9.8f) {}

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

  void eulerStep(float dt) {
    computeForces();
    computeDerivative(dydt);  // dY/dt
    scaleVector(dydt, dt);    // dY/dt * dt
    getParticleState(s1);     // s1 <- p
    addVectors(s1, dydt);     // s1 += dY/dt * dt;
    checkCollisions(s1);
    setParticleState(s1);  // p <- s1
    t += dt;
  }

  void checkCollisions(float4 *s1) {
    Collision c;
    for (size_t i = 0; i < n; ++i) {
      // std::cout << "p0=" << s0[2*i].str() << " p1=" << s1[2 * i].str();
      // std::cout << "v0=" << s0[2*i + 1].str() << " v1=" << s1[2 * i +
      // 1].str()<< std::endl;
      if (world->checkCollision(p[i].x, s1[2 * i], c)) {
        float4 N = c.N;
        s1[2 * i] = c.p;
        float4 Vn = dot3d(p[i].v, N) * N;
        float4 Vt = p[i].v - Vn;
        s1[2 * i + 1] = Vt - 0.4f * Vn;
        float muk = 1.f;//c.obj->getFriction();
        p[i].contact = -muk * dot3d(-p[i].f, N) * Vt;// - dot3d(p[i].f, N) * N * 0;
      } else {
        p[i].contact = 0;
      }
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

  void applycontact() {
    for (size_t i = 0; i < n; ++i) p[i].f += p[i].contact;
  }


  void zeroForces() {
    for (size_t i = 0; i < n; ++i) p[i].f = 0;
  }

  void computeForces() {
    zeroForces();
    applyGravity();
    applyDrag();
    applycontact();
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