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
    kd = 0.02f;
    kr = 0.6f;
    muk = 0.05f;
    g = -9.8f;
   // g = -10.0f;
  }

  void create(size_t n) {
    clear();
    p.resize(n);
    y.resize(2 * n);
    yf.resize(2 * n);
  }

  void createTest() {
    // create(1);
    // float x = 0;
    // float y = 0;
    // float z = 1;
    // float vx = 0;
    // float vy = 2;
    // float vz = 20;
    // p[0].m = 1;
    // p[0].x = float4(x, y, z);
    // p[0].v = float4(vx, vy, vz);
    size_t N = 10000;
    create(N);
    for (size_t i = 0; i < N; ++i) {
      float x = rand() / float(RAND_MAX) * 2 + 6;
      float y = rand() / float(RAND_MAX) * 2 + 6;
      float z = rand() / float(RAND_MAX) * 2 + 20;
      float vx = 3.8f * rand() / float(RAND_MAX) - 2;
      float vy = 3.8f * rand() / float(RAND_MAX) - 2;
      float vz = 0 * rand() / float(RAND_MAX);
      p[i].m = 1;
      p[i].x = float4(x, y, z);
      p[i].v = float4(vx, vy, vz);
    }
  }

  void zeroForces() {
    for (size_t i = 0; i < p.size(); ++i) p[i].a = 0;
  }

  void calcForces() {
    zeroForces();
    for (size_t i = 0; i < p.size(); ++i) {
      p[i].fg = float4(0, 0, g) * p[i].m;  // gravity
      p[i].fd += -kd * p[i].v;             // drag
      if (p[i].contact) {
        float fn_norm = dot3d(p[i].fg, p[i].Nc);
        float4 fn = -fn_norm * p[i].Nc;
        float4 fr = fn_norm * p[i].v * muk;
        p[i].fc = fn + fr;
        //  std::cout << "Contact!!----------------> a = " << p[i].a.str() <<
        // std::endl;
      }
      p[i].a += p[i].fg + p[i].fc;
      +p[i].fd;
      p[i].a /= p[i].m;  // just get the acceleration
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
                << (p[i].contact ? " ------- Contact " : "") << std::endl;
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

  void checkCollisions(float4v &y0, float4v &y1, float dt) {
    Collision c;
    
    for (size_t i = 0; i < p.size(); ++i) {
      p[i].fc = 0;
      p[i].contact = false;
      if (world->checkCollision(y1[2 * i], y1[2 * i + 1], c)) {
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
    float tp = 0;
    float dtp = dt / 10.0f;
    blockData = false;
    while (tp <= dt) {
      //printState();
      //blockData = true;
      calcForces();
      getState(y);
      //      blockData = false;
      ode.RK2Solve(t, dtp, y, yf);
      checkCollisions(y, yf, dtp);
      //      blockData = true;
      setState(yf);
      //blockData = false;
      tp += dtp;
      t += dtp;
    }
     std::cout << "t = " << t << std::endl;
  }

  size_t size() { return p.size(); }

  float4 getParticlePosition(size_t i) { return p[i].x; }

 private:
  World *world;
  std::vector<Particle> p;
  float4v y;
  float4v yf;
  float t;
  float g;    // gravity
  float kd;   // drag constant
  float kr;
  float muk;  // kinetic friction coeficient
  ODESolver ode;
  bool blockData;
};



#endif