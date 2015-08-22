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
#include "robot_unit.h"
#include "ffnn3l.h"


class GA {
 public:
  GA(size_t N) : N(N), Population(N), TMax(0), t(0) {
    newRandomPopulation();
    started = false;
    generation = 0;
  }

  int generation;

  void update(float dt) {
    if (started) {
      if (t < TMax) {
        for (size_t i = 0; i < N; ++i) Population[i].update(dt);
        float vmax = 0;
        for (size_t i = 0; i < N; ++i) {
          float v = Population[i].getV();
          if (v > vmax) vmax = v;
        }
        t += dt;
      } else {
        float davg = 0;
        for (size_t i = 0; i < N; ++i)
          davg += sqrt(Population[i].getDistance2());
        davg /= N;
        std::cout << generation++ << "  d = " << davg << std::endl;
        nextGeneration();
        //started = false;
        t = 0;
      }
    }
  }

  void sortPopulation() {
    std::sort(Population.begin(), Population.end(),
              [](const RobotUnit& a, const RobotUnit& b)
                  -> bool { return (a.getDistance2() < b.getDistance2()); });
  }

  RobotUnit reproduce(RobotUnit& x, RobotUnit& y) {
    RobotUnit child;
    child.getParentsGenes(x.getBrain(), y.getBrain());
    return child;
  }

  void nextGeneration() {
    sortPopulation();
    Population[0].setGlow();
    std::vector<RobotUnit> NP(N);
    static std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, Population.size() / 2 - 1);
    for (size_t i = 0; i < N; ++i) {
      RobotUnit child;
      child.getParentGenes(Population[i % 2].getBrain());
      child.randomMutation();
      NP[i] = child;
    }
    /*
    for (size_t i = 0; i < Population.size() / 20; ++i) {
      size_t i0 = distribution(generator);
      size_t i1 = distribution(generator);
      RobotUnit x = Population[i0];
      RobotUnit y = Population[i1];
      for (int j = 0; j < 20; ++j) {
        RobotUnit child = reproduce(x, y);
        child.randomMutation();
        NP[20 * i + j] = child;
      }
    }*/
    Population = NP;
  }

  void startSimulation(float T) {
    TMax = T;
    started = true;
  }

  void render() {
    for (size_t i = 0; i < N; ++i) {
      Population[i].render();
    }
  }

 protected:
  void newRandomPopulation() {
    Population.clear();
    Population.resize(N);
    for (size_t i = 0; i < N; ++i) {
      Population[i] = RobotUnit();
    }
  }

 private:
  size_t N;
  std::vector<RobotUnit> Population;
  float TMax;
  float t = 0;
  bool started;
};

#endif