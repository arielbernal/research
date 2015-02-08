#ifndef PARTICLES_H
#define PARTICLES_H
#include <stdlib.h>
#include <vector>
#include <svector.h>
#include "ode_solver.h"
#include "world.h"

using namespace svector;

struct Particle {
  float m;    // mass
  float4 x;   // position
  float4 v;   // velocity
  float4 f;   // force
  float4 fc;  // contact force
  Particle() : m(1) {}
};

class ParticleSystem {
 public:
  ParticleSystem() : world(0), p(0), y(0), yf(0), t(0) {}

  void setWorld(World *w) { world = w; }

  void clear() {
    p.clear();
    y.clear();
    yf.clear();
    t = 0;
    kd = 0.3f;
    g = -9.8f;
    g = -10.0f;
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
      //   p[i].f += -kd * p[i].v;              // drag
      p[i].f += p[i].fc;
      p[i].f /= p[i].m;  // just get the acceleration
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

  void dydt(float t, std::vector<float4> &y, std::vector<float4> &res) {
    for (size_t i = 0; i < p.size(); ++i) {
      res[2 * i] = y[2 * i + 1];
      res[2 * i + 1] = p[i].f;
    }
  }

  void dydtCollisions(float t, std::vector<float4> &y,
                      std::vector<float4> &res) {
    for (size_t i = 0; i < idc.size(); ++i) {
      size_t id = idc[i];
      res[2 * i] = y[2 * i + 1];
      res[2 * i + 1] = p[id].f;
    }
  }

  void resolveCollisions(std::vector<float4> &yc, std::vector<float4> &yf,
                         float dt) {
    std::vector<float4> ycf(yc.size());
    ODERK2Solver(t, dt, yc, ycf, &dydtStaticCollisions, this);
    for (size_t i = 0; i < idc.size(); ++i) {
      size_t id = idc[i];
      yf[2 * id] = ycf[2 * i];
      yf[2 * id + 1] = ycf[2 * i + 1];
    }
  }

  void checkCollisions(std::vector<float4> &y0, std::vector<float4> &y1,
                       float dt) {
    Collision c;
    float muk = 0.2f;
    std::vector<float4> yc;
    idc.clear();
    for (size_t i = 0; i < p.size(); ++i) {
      if (world->checkCollision(y0[2 * i], y1[2 * i], c)) {
        if (c.contact) {
          float4 v0 = y0[2 * i + 1];
          float4 vn = dot3d(v0, c.N) * c.N;
          float4 vt = v0 - vn;

          float fn_norm = dot3d(p[i].f, c.N);
          float4 fn = -fn_norm * c.N;
          float4 fk = -muk * fn_norm * vt / vt.norm();
          p[i].fc = fn + fk;
        } else {
          float4 v = y0[2 * i + 1] * (1 - c.t) + y1[2 * i + 1] * c.t;
          float4 vn = -dot3d(v, c.N) * c.N;
          float4 vf = v - vn;
          yc.push_back(c.p);
          yc.push_back(v);
          idc.push_back(i);
          std::cout << "c.p = " << c.p.str() << " v = " <<  vf.str() << std::endl;
          resolveCollisions(yc, y1, dt);
          std::cout << "resolved y1 = " << y1[2 * i].str()
                    << " v = " << y1[2 * i + 1].str() << "\n";
          // exit(1);
        }
      }
    }
    if (!idc.empty()) {
//      resolveCollisions(yc, yf, dt);
    }
  }

  void step(float dt) {
    printState();
    calcForces();
    getState(y);
    ODERK2Solver(t, dt, y, yf, &dydtStatic, this);
    checkCollisions(y, yf, dt);
    setState(yf);
    t += dt;
  }

  size_t size() { return p.size(); }

  float4 getParticlePosition(size_t i) { return p[i].x; }

 protected:
  static void dydtStatic(float t, std::vector<float4> &y,
                         std::vector<float4> &res, void *dydt_args) {
    ((ParticleSystem *)dydt_args)->dydt(t, y, res);
  }

  static void dydtStaticCollisions(float t, std::vector<float4> &y,
                                   std::vector<float4> &res, void *dydt_args) {
    ((ParticleSystem *)dydt_args)->dydtCollisions(t, y, res);
  }

 private:
  World *world;
  std::vector<Particle> p;
  std::vector<float4> y;
  std::vector<float4> yf;
  std::vector<size_t> idc;  // collision ids
  float t;
  float g;   // gravity
  float kd;  // drag constant
};

#endif