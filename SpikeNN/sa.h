#ifndef SA_H
#define SA_H

#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <pthread.h>

#include "include/glheaders.h"
#include "include/glprimitives.h"
#include "point2d.h"
#include "robot.h"
#include "robot_unit.h"
#include "ffnn3l.h"
#include "utils.h"

class SA {
 public:
  SA(size_t N) : N(N) {}

  void render() {
    if (!Sorting) {
      Population[0].setGlow(true);
      for (size_t i = 0; i < 10; ++i) Population[i].render();
      Population[0].setGlow(false);
    }
  }

  void startSimulation(float T, float Dt) {
    TMax = T;
    dt = Dt;
    if (!isRunning) {
      pthread_t hThread;
      pthread_create(&hThread, nullptr, &GA::static_simulate, this);
    }
  }

  void stopSimulation() {
    std::cout << "Stopping..." << std::endl;
    StopSimulation = true;
  }

  void saveMostFit(const std::string& Filename) {
    sortPopulation();
    Population[0].save(Filename);
  }

  void loadMostFit(const std::string& Filename) {
    for (size_t i = 0; i < N; ++i) {
      Population[i].load(Filename);
      if (i > 10) Population[i].randomMutation();
    }
  }

  void resetConditions() {
    for (auto& e : Population) e.resetUnit();
    t = 0;
  }

  float getTime() { return t; }
  float getDt() { return dt; }

  void setTrack(Track* newTrack) {
    track = newTrack;
    for (auto& e : Population) e.setTrack(track);
  }

  void slowDown(float dv) {
    SlowDown += dv;
    if (SlowDown < 0) SlowDown = 0;
  }

 protected:
  void simulate() {
    isRunning = true;
    StopSimulation = false;
    resetConditions();
    std::cout << "Thread Started" << std::endl;
    while (!StopSimulation) {
      std::cout << "Generation = " << generation << std::endl;
      bool done = false;
      while (t < TMax && !done) {
        done = true;
#pragma omp parallel for
        for (int i = 0; i < N; ++i) {
          auto& e = Population[i];
          if (e.isAlive()) {
            e.update(dt);
            done = false;
          }
        }
        t += dt;
        Sleep(SlowDown);
      }

      int isCollided = 0;
      float avgD = 0;
      int iD = 0;
      for (auto& e : Population) {
        if (e.isCollided()) isCollided++;
        e.updateFitnessVal();
        if (e.isAlive()) {
          avgD += e.getDistance();
          iD++;
        }
      }
      avgD /= iD;
      Sorting = true;
      sortPopulation();
      Sorting = false;
      std::cout << " AverageD = " << avgD << " Collided = " << isCollided
                << std::endl;
      for (size_t i = 0; i < 10; ++i) {
        auto& a = Population[i];
        std::cout << a.isAlive() << "  --- > "
                  << "D = " << a.getDistance() << " E = " << a.getEnergy()
                  << " F = " << a.getFitnessVal();
        std::cout << " x = " << a.getX() << " y = " << a.getY()
                  << " i=" << a.getYId() << " j=" << a.getXId()
                  << " d = " << a.getDistanceT() << std::endl;
      }
      nextGeneration();
    }
    isRunning = false;
    std::cout << "Thread Stop" << std::endl;
  }

  static void* static_simulate(void* This) {
    ((SA*)This)->simulate();
    return NULL;
  }

 private:
  RobotUnit robot;
};

#endif
