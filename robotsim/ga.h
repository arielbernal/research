#ifndef GA_H
#define GA_H

#include <iostream>
#include "include/glheaders.h"
#include <cmath>
#include "include/glprimitives.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

#include "robot_path.h"
#include "point2d.h"
#include "robot.h"
#include "robot_ga.h"
#include "ffnn3l.h"

class GA {
 public:
  GA(size_t N)
      : N(N),
        Population(N),
        TMax(0),
        t(0),
        generation(0),
        started(false),
        InitialPos(0, 0),
        InitialAngle(0),
        StopSimulation(false) {
    newPopulation();
  }

  void setInitialPos(const Point2d &p, float angle) {
    InitialPos = p;
    InitialAngle = angle;
    for (auto &e : Population) e.setPos(p, angle);
  }

  void render() {
    for (auto &e : Population) {
      if (!e.isCollided() || e.isGlow()) e.render();
    }
  }

  void update(float dt, const Track &track) {
    if (started) {
      if (t < TMax) {
        float DistanceToTarget = 10E20;
        size_t iBest = 0;
        for (size_t i = 0; i < N; ++i) {
          auto &e = Population[i];
          e.setGlow(false);
          if (!e.isCollided()) {
            e.update(dt, track);
          }
          float d = e.getDistance();
          if (d < DistanceToTarget) {
            DistanceToTarget = d;
            iBest = i;
          }
        }
        Population[iBest].setGlow(true);
        t += dt;
      } else {
        int collisions = 0;
        float davg = 0;
        for (auto &e : Population) {
          davg += e.getDistance();
          if (e.isCollided()) collisions++;
        }
        davg /= N;
        std::cout << "Generation " << generation++ << "  DAvg = " << davg
                  << " Collisions = " << collisions << std::endl;
        nextGeneration();
        if (StopSimulation) {
          started = false;
        }
        t = 0;
      }
    }
  }

  void startSimulation(float T) {
    TMax = T;
    started = true;
    StopSimulation = false;
    t = 0;
    resetConditions();
  }

  bool isStarted() { return started; }
  void stopSimulation() { StopSimulation = true;}

  void saveMostFit(const std::string& Filename) {
    sortPopulation();
    Population[0].save(Filename);
  }

  void loadMostFit(const std::string& Filename) {
    for (size_t i = 0; i < N; ++i) {
      Population[i].load(Filename);
      Population[i].randomMutation(); 
    }
  }

 protected:
  void newPopulation() {
    for (size_t i = 0; i < N; ++i) Population[i] = RobotGA();
  }

  void sortPopulation() {
    float eps = 1;
    std::sort(Population.begin(), Population.end(),
              [eps](const RobotGA &a, const RobotGA &b) -> bool {
      bool inRange = a.getDistance() < eps && b.getDistance() < eps;
      bool bestTime = a.getT() < b.getT();
      bool bestDistance = a.getDistance() < b.getDistance();
      return ((inRange && bestTime) || (!inRange && bestDistance));
    });
  }

  void resetConditions() {
    setInitialPos(InitialPos, InitialAngle);
    for (auto &e : Population) {
      e.setGlow(false);
      e.setCollided(false);
      e.setT(0);
    }
  }

  void nextGeneration() {
    sortPopulation();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> uniform(0, N / 4);
    for (size_t i = N / 4; i < N; ++i) {
      const FFNN3L &NN1 = Population[uniform(generator)].getNN();
      const FFNN3L &NN2 = Population[uniform(generator)].getNN();
      Population[i].crossOver(NN1, NN2);
      Population[i].randomMutation();
    }
    resetConditions();
  }

 private:
  size_t N;
  std::vector<RobotGA> Population;
  float TMax;
  float t;
  bool started;
  size_t generation;
  Point2d InitialPos;
  float InitialAngle;
  bool StopSimulation;
};

// class GA {
//  public:
//   GA(size_t N) : N(N), Population(N), TMax(0), t(0) {
//     newRandomPopulation();
//     started = false;
//     generation = 0;
//   }

//   int generation;

//   void update(float dt) {
//     if (started) {
//       if (t < TMax) {
//         for (size_t i = 0; i < N; ++i) Population[i].update(dt);
//         float vmax = 0;
//         for (size_t i = 0; i < N; ++i) {
//           float v = Population[i].getV();
//           if (v > vmax) vmax = v;
//         }
//         t += dt;
//       } else {
//         float davg = 0;
//         for (size_t i = 0; i < N; ++i)
//           davg += sqrt(Population[i].getDistance2());
//         davg /= N;
//         std::cout << generation++ << "  d = " << davg << std::endl;
//         nextGeneration();
//         //started = false;
//         t = 0;
//       }
//     }
//   }

//   void sortPopulation() {
//     std::sort(Population.begin(), Population.end(),
//               [](const RobotUnit& a, const RobotUnit& b)
//                   -> bool { return (a.getDistance2() < b.getDistance2()); });
//   }

//   RobotUnit reproduce(RobotUnit& x, RobotUnit& y) {
//     RobotUnit child;
//     child.getParentsGenes(x.getBrain(), y.getBrain());
//     return child;
//   }

//   void nextGeneration() {
//     sortPopulation();
//     Population[0].setGlow();
//     std::vector<RobotUnit> NP(N);
//     static std::default_random_engine generator;
//     std::uniform_int_distribution<int> distribution(0, Population.size() / 2
//     - 1);
//     for (size_t i = 0; i < N; ++i) {
//       RobotUnit child;
//       child.getParentGenes(Population[i % 2].getBrain());
//       child.randomMutation();
//       NP[i] = child;
//     }
//     /*
//     for (size_t i = 0; i < Population.size() / 20; ++i) {
//       size_t i0 = distribution(generator);
//       size_t i1 = distribution(generator);
//       RobotUnit x = Population[i0];
//       RobotUnit y = Population[i1];
//       for (int j = 0; j < 20; ++j) {
//         RobotUnit child = reproduce(x, y);
//         child.randomMutation();
//         NP[20 * i + j] = child;
//       }
//     }*/
//     Population = NP;
//   }

//   void startSimulation(float T) {
//     TMax = T;
//     started = true;
//   }

//   void render() {
//     for (size_t i = 0; i < N; ++i) {
//       Population[i].render();
//     }
//   }

//  protected:
//   void newRandomPopulation() {
//     Population.clear();
//     Population.resize(N);
//     for (size_t i = 0; i < N; ++i) {
//       Population[i] = RobotUnit();
//     }
//   }

//  private:
//   size_t N;
//   std::vector<RobotUnit> Population;
//   float TMax;
//   float t = 0;
//   bool started;
// };

#endif
