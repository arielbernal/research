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
  float4 a;   // acceleration
  float4 fg;  // force of gravity
  float4 fd;  // drag force
  float4 fc;  // contact force
  float4 Nc;  // contact Normal
  bool contact;
  Particle() : m(1), contact(false) {}
};

class ParticleSystem {
 public:
  ParticleSystem() : world(0), p(0), y(0), yf(0), t(0), blockData(false) {
    ode.setDyDt([this](float t, float4v &y0,
                       float4v &y1) { this->dydt(t, y0, y1); });
    ode.setDyDtScalar([this](float t, float4v &y0, float4v &y1,
                             size_t id) { this->dydtScalar(t, y0, y1, id); });
  }

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
    float z = 1;
    float vx = 0;
    float vy = 0;
    float vz = 0;
    p[0].m = 1;
    p[0].x = float4(x, y, z);
    p[0].v = float4(vx, vy, vz);
  }

  void zeroForces() {
    for (size_t i = 0; i < p.size(); ++i) p[i].a = 0;
  }

  void calcForces() {
    zeroForces();
    for (size_t i = 0; i < p.size(); ++i) {
      p[i].fg = float4(0, 0, g) * p[i].m;  // gravity
      //   p[i].f += -kd * p[i].v;              // drag
      if (p[i].contact) {
        float fn_norm = dot3d(p[i].fg, p[i].Nc);
        float4 fn = -fn_norm * p[i].Nc;
        p[i].fc = fn;
      }
      p[i].a += p[i].fg + p[i].fc;
      p[i].a /= p[i].m;  // just get the acceleration
      std::cout << "----------------> a = " << p[i].a.str() << std::endl;
    }
  }

  void getState(float4v &y) {
    for (size_t i = 0; i < p.size(); ++i) {
      y[2 * i] = p[i].x;
      y[2 * i + 1] = p[i].v;
    }
  }

  void setState(float4v &y) {
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

  void dydt(float t, float4v &y, float4v &res) {
    for (size_t i = 0; i < p.size(); ++i) {
      res[2 * i] = y[2 * i + 1];
      res[2 * i + 1] = p[i].a;
    }
  }

  void dydtScalar(float t, float4v &y, float4v &res, size_t id) {
    res[0] = y[1];
    res[1] = p[id].a;
  }

  void resolveCollisions(float4v &yc, float4v &yf, float dt) {
    // float4v ycf(yc.size());
    // ODERK2Solver(t, dt, yc, ycf, &dydtStaticCollisions, this);
    // for (size_t i = 0; i < idc.size(); ++i) {
    //  size_t id = idc[i];
    //  yf[2 * id] = ycf[2 * i];
    //  yf[2 * id + 1] = ycf[2 * i + 1];
    //}
  }

  void checkCollisions(float4v &y0, float4v &y1, float dt) {
    Collision c;
    float muk = 0.01f;
    float kr = 0.3f;
    for (size_t i = 0; i < p.size(); ++i) {
      p[i].fc = 0;
      p[i].contact = false;
      if (world->checkCollision(y1[2 * i], y1[2 * i + 1], c)) {
        std::cout << "Collision\n";
        std::cout << "x = " << y1[2 * i].str() << " v = " << y1[2 * i + 1].str()
                  << std::endl;
        std::cout << "c.N = " << c.N.str() << " c.i = " << c.i
                  << " v  = " << c.t << std::endl;
        float4 v = y1[2 * i + 1];
        float4 vn = dot3d(v, c.N) * c.N;
        float4 vt = v - vn;
        float4 vf = vt - kr * vn;
        p[i].contact = c.contact;
        p[i].Nc = c.N;
        if (p[i].contact) vf = vt;
        y1[2 * i + 1] = vf;
      }
    }
  }

  bool isDataBlocked() { return blockData; }

  void step(float dt) {
    printState();
    blockData = true;
    calcForces();
    getState(y);
    blockData = false;
    ode.RK2Solve(t, dt, y, yf);
    checkCollisions(y, yf, dt);
    blockData = true;
    setState(yf);
    blockData = false;
    t += dt;
  }

  size_t size() { return p.size(); }

  float4 getParticlePosition(size_t i) { return p[i].x; }

 private:
  World *world;
  std::vector<Particle> p;
  float4v y;
  float4v yf;
  float t;
  float g;   // gravity
  float kd;  // drag constant
  ODESolver ode;
  bool blockData;
};

#endif