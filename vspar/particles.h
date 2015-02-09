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
  ParticleSystem() : world(0), p(0), y(0), yf(0), t(0) {
    ode.setDyDt([this](float t, float4v &y0, float4v &y1) { this->dydt(t, y0, y1); });
    ode.setDyDtScalar([this](float t, float4v &y0, float4v &y1, size_t id) { this->dydtScalar(t, y0, y1, id); });
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
    float z = 0;
    float vx = 0;
    float vy = 5;
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
      res[2 * i + 1] = p[i].f;
    }
  }

  void dydtScalar(float t, float4v &y, float4v &res, size_t id) {
    res[0] = y[1];
    res[1] = p[id].f;
  }
  
  void resolveCollisions(float4v &yc, float4v &yf,
                         float dt) {
    //float4v ycf(yc.size());
    //ODERK2Solver(t, dt, yc, ycf, &dydtStaticCollisions, this);
    //for (size_t i = 0; i < idc.size(); ++i) {
    //  size_t id = idc[i];
    //  yf[2 * id] = ycf[2 * i];
    //  yf[2 * id + 1] = ycf[2 * i + 1];
    //}
  }

  void checkCollisions(float4v &y0, float4v &y1,
                       float dt) {
    Collision c;
    float muk = 0.01f;
    float4v yc(2);
    float4v ycr(2);
    for (size_t i = 0; i < p.size(); ++i) {
      if (world->checkCollision(y0[2 * i], y1[2 * i], c)) {
        if (c.contact) {
          std::cout << "------------- Contact ------------- \n";
          float4 v0 = y1[2 * i + 1];
          float4 vn = dot3d(v0, c.N) * c.N;
          float4 vt = v0 - vn;
          float fn_norm = dot3d(p[i].f, c.N);
          float4 fn = -fn_norm * c.N;
          float vt_norm = vt.norm();
          float4 fk;
          if (vt_norm > 0.001f)
            fk = muk * fn_norm * vt / vt.norm();
          std::cout << "p.f = " << p[i].f.str() << " fk = " << fk.str() << std::endl;
          p[i].fc = fn + fk;
          ycr[0] = c.p;
          ycr[1] = vt;

        } else {
          float4 v = y0[2 * i + 1] * (1 - c.t) + y1[2 * i + 1] * c.t;
          float4 vn = dot3d(v, c.N) * c.N;
          float4 vf = v - (1 + 0.3f) * vn;
          yc[0] = c.p;
          yc[1] = vf;
          p[i].fc = 0;
          //std::cout << "v = " << v.str() << " vf = " << vf.str() << std::endl;
          ode.RK2Solve(t, dt * c.t, yc, ycr, i);
          if (world->checkCollision(yc[0], ycr[0], c)) {
            //std::cout << "collide again!!! is just a contact\n";
            //std::cout << "c.p = " << c.p.str() << " c.t = " << c.t << std::endl;
            float4 v0 = ycr[1];
            float4 vn = dot3d(v0, c.N) * c.N;
            float4 vt = v0 - vn;
            float fn_norm = dot3d(p[i].f, c.N);
            float4 fn = -fn_norm * c.N;
            float vt_norm = vt.norm();
            float4 fk;
            if (vt_norm > 0.001f)
              fk = -muk * fn_norm * vt / vt.norm();
            p[i].fc = fn + fk;
            ycr[1] = vt;
            ycr[0] = c.p;
            //std::cout << "--->>>>>>>>> new p = " << ycr[0].str() << "  new v = " << ycr[1].str() << std::endl;
          }
          //std::cout << "Collision resolved\n";
        }
        y1[2 * i] = ycr[0];
        y1[2 * i + 1] = ycr[1];
       
      }
      else {
        p[i].fc = 0;
      }
    }
  }

  void step(float dt) {
    printState();
    calcForces();
    getState(y);
    ode.RK2Solve(t, dt, y, yf);
    checkCollisions(y, yf, dt);
    setState(yf);
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
};

#endif