#ifndef PARTICLES_H
#define PARTICLES_H
#include <stdlib.h>
#include <vector>
#include <svector.h>
#include "ode_solver.h"
#include "world.h"

using namespace svector;

struct Particle {
  float m;         // mass
  float4 x;        // position
  float4 v;        // velocity
  float4 f;        // force
  float4 contact;  // contact force
  Particle() : m(1) {}
};

class ParticleSystem {
 public:
  ParticleSystem() : p(0), y(0), yf(0), t(0) {}

  void clear() {
    p.clear();
    y.clear();
    yf.clear();
    t = 0;
    kd = 0.3f;
    g = -9.8f;
  }

  void create(size_t n) {
    clear();
    p.resize(n);
    y.resize(2 * n);
    yf.resize(2 * n);
  }

  void createTest() {
    create(1);
    float x = 0;
    float y = 0;
    float z = 0;
    float vx = 0;
    float vy = 0;
    float vz = 10;
    p[0].m = 1;
    p[0].x = float4(x, y, z);
    p[0].v = float4(vx, vy, vz);
  }

  void zeroForces() {
    for (size_t i = 0; i < p.size(); ++i) p[i].f = 0;
  }

  void calcForces() {
    zeroForces();
    for (size_t i = 0; i < p.size(); ++i) {
      p[i].f += float4(0, 0, g) * p[i].m;  // gravity
      p[i].f += -kd * p[i].v;              // drag
    }
  }

  void dydt(float t, std::vector<float4> &y, std::vector<float4> &res) {
    for (size_t i = 0; i < p.size(); ++i) {
      res[2 * i] = y[2 * i + 1];
      res[2 * i + 1] = p[i].f / p[i].m;
    }
  }

  void getState(std::vector<float4> &y) {
    for (size_t i = 0; i < p.size(); ++i) {
      y[2 * i] = p[i].x;
      y[2 * i + 1] = p[i].v;
    }
  }

  void setState(std::vector<float4> &y) {
    for (size_t i = 0; i < p.size(); ++i) {
      p[i].x = y[2 * i];
      p[i].v = y[2 * i + 1];
    }
  }

  void printState() {
    for (size_t i = 0; i < p.size(); ++i)
      std::cout << "t = " << t << " \t" << p[i].x.str() << " - " << p[i].v.str()
                << std::endl;
  }

  static void dydtStatic(float t, std::vector<float4> &y,
                         std::vector<float4> &res, void *dydt_args) {
    ((ParticleSystem *)dydt_args)->dydt(t, y, res);
  }

  void checkCollisions(std::vector<float4> &y0, std::vector<float4> &y1) {}

  void step(float dt) {
    printState();
    calcForces();
    getState(y);
    ODERK2Solver(t, dt, y, yf, &dydtStatic, this);
    checkCollisions(y, yf);
    setState(yf);
    t += dt;
  }

  size_t size() { return p.size(); }

  float4 getParticlePosition(size_t i) { return p[i].x; }

 private:
  std::vector<Particle> p;
  std::vector<float4> y;
  std::vector<float4> yf;
  float t;
  float g;   // gravity
  float kd;  // drag constant
};

#endif