#ifndef GA_H
#define GA_H

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

class GA {
 public:
  GA(size_t N)
      : N(N),
        Population(N),
        TMax(0),
        t(0),
        generation(0),
        InitialAngle(0),
        StopSimulation(false),
        dt(0.01f),
        isRunning(false),
        SlowDown(0),
        Sorting(false) {
    newPopulation();
  }

  void render() {
    if (!Sorting) {
      Population[0].setGlow(true);
      for (size_t i = 0; i < 10; ++i)
        Population[i].render();
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
      if (i > 10)
        Population[i].randomMutation();
    }
  }

  void resetConditions() {
    for (auto& e : Population)
      e.resetUnit();
    t = 0;
  }

  float getTime() { return t; }
  float getDt() { return dt; }

  void setTrack(Track* newTrack) {
    track = newTrack;
    for (auto& e : Population)
      e.setTrack(track);
  }

  void slowDown(float dv) {
    SlowDown += dv;
    if (SlowDown < 0)
      SlowDown = 0;
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
      for (auto& e : Population)
        if (e.isCollided())
          isCollided++;
      Sorting = true;
      sortPopulation();
      Sorting = false;
      std::cout << " Best Time = " << Population[0].getTime()
                << " Collided = " << isCollided << std::endl;
      for (size_t i = 0; i < 10; ++i) {
        auto &a = Population[i];
        std::cout << "     " << a.getDistance() << "   "
                  << a.getDistanceT() << "  "
                  << a.getTime() << " "
                  << a.isAlive() << "  --- > " << a.getFitnessVal() << std::endl;
      }
      nextGeneration();
    }
    isRunning = false;
    std::cout << "Thread Stop" << std::endl;
  }

  static void* static_simulate(void* This) {
    ((GA*)This)->simulate();
    return NULL;
  }

  void newPopulation() {
    for (size_t i = 0; i < N; ++i)
      Population[i] = RobotUnit();
  }

  void sortPopulation() {
    float eps = 2;
    std::sort(Population.begin(), Population.end(),
              [eps](const RobotUnit& a, const RobotUnit& b) -> bool {
            
                return a.getFitnessVal() > b.getFitnessVal();
                // bool la = a.isCollided();
                // bool lb = b.isCollided();
                // if (!la && !lb) {
                //  if (da == db)
                //    return a.getTime() < b.getTime();
                //  else
                //    return da > db;
                //}
                // else if (!la && !lb)
                //  return da > db;
                // else if (!la)
                //  return true;
                // else
                //  return false;

                // if (!la)
                //  return true;
                // if (!lb)
                //  return false;
                // return da > db;

                // if (da == db)
                // return a.getTime() < b.getTime();
                // return da > db;
                
                //if (da == db)
                //  return a.getDistanceT() > b.getDistanceT();
                //return da > db;


              });
  }

  void nextGeneration() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(seed);
    int k = 10;
    std::uniform_int_distribution<int> u2(0, N / k - 1);
    int j = 0;
    for (size_t i = N / k; i < N; ++i) {
      const FFNN3L& NN1 = Population[j % (N / k - 1)].getNN();
      const FFNN3L& NN2 = Population[u2(generator)].getNN();
      j++;
      Population[i].crossOver(NN1, NN2);
      Population[i].randomMutation();
    }
    resetConditions();
    generation++;
  }

 private:
  size_t N;
  std::vector<RobotUnit> Population;
  float TMax;
  float t;
  size_t generation;
  float InitialAngle;
  Track* track;
  bool StopSimulation;
  bool isRunning;
  float dt;
  float SlowDown;
  bool Sorting;
};

#endif
