#ifndef PARTICLES_H
#define PARTICLES_H
#include <stdlib.h>
#include <svector.h>

using namespace svector;

struct Particle {
  float m;   // mass
  float4 x;  // position
  float4 v;  // velocity
  float4 f;  // force
};

class ParticleSystem {
public:
  ParticleSystem() : p(0), n(0), t(0), tmp1(0), tmp2(0), g(-9.8f) {}

  ParticleSystem(size_t num_particles) : n(num_particles), t(0), g(-9.8f) {
	p = (Particle*)_aligned_malloc(n * sizeof(Particle), 0x100);
	tmp1 = (float4*)_aligned_malloc(2 * n * sizeof(float4), 0x100);
	tmp2 = (float4*)_aligned_malloc(2 * n * sizeof(float4), 0x100);
  }

  ~ParticleSystem() { clear(); }

  void clear() {
    if (p) {
      _aligned_free(p);
      p = 0;
    }
    if (tmp1) {
      _aligned_free(tmp1);
      tmp1 = 0;
    }
    if (tmp2) {
      _aligned_free(tmp2);
      tmp2 = 0;
    }
  }

  void create(size_t num_particles) {
    clear();
    n = num_particles;
    t = 0;
	p = (Particle*)_aligned_malloc(n * sizeof(Particle), 0x100);
	tmp1 = (float4*)_aligned_malloc(2 * n * sizeof(float4), 0x100);
	tmp2 = (float4*)_aligned_malloc(2 * n * sizeof(float4), 0x100);
  }



  void eulerStep(float dt) {
    computeDerivative(tmp1);  // tmp1 = dY/dt
    scaleVector(tmp1, dt);    // tmp1 *= dt
    getParticleState(tmp2);   // tmp2 <- p
    addVectors(tmp2, tmp1);   // tmp2 += tmp1;
    setParticleState(tmp2);   // p <- tmp2
    t += dt;
  }

  void testParticles() {
    for (size_t i = 0; i < n; ++i) {
      float x = rand() / float(RAND_MAX) * 10;
      float y = rand() / float(RAND_MAX) * 10;
      x = 5;
      y = 5;
      float z = 10;
      p[i].m = 1;
      p[i].x = float4(x, y, z);
    }
  }

  float4 getParticlePosition(size_t id) {
  	return p[id].x;
  }

  size_t getNumParticles() {
  	return n;
  }

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
      std::cout << "p[i].x = " << p[i].x.str() << std::endl;
    }
  }

  void applyGravity() {
    for (size_t i = 0; i < n; ++i) p[i].f.z += p[i].m * g;
  }

  void zeroForces() {
    for (size_t i = 0; i < n; ++i) p[i].f = 0;
  }

  void computeForces() {
    zeroForces();
    applyGravity();
  }

  void computeDerivative(float4 *dst) {
    computeForces();
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
  Particle *p;
  size_t n;
  float t;
  float4 *tmp1;
  float4 *tmp2;
  const float g;  
};

#endif