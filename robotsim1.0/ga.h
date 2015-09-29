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
#include "utils.h"

class GA {
public:
  GA(size_t N)
      : N(N), Population(N), TMax(0), t(0), generation(0), InitialAngle(0),
        StopSimulation(false), dt(0.01f), isRunning(false), SlowDown(0),
        Sorting(false) {
    newPopulation();
    idTrack = 0;
  }
  ~GA() {
    for (size_t i = 0; i < tracks.size(); ++i) {
      delete tracks[i];
    }
  }
  void render() {
    if (!Sorting) {
      Population[0].setGlow(true);
      Population[0].render();
      Population[0].setGlow(false);
      for (size_t i = 1; i < 1000; ++i)
        Population[i].render();
    }
    tracks[idTrack]->render();
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

  void saveMostFit(const std::string &Filename) {
    Population[0].save(Filename);
  }

  void loadMostFit(const std::string &Filename) {
    for (size_t i = 0; i < N; ++i) {
      Population[i].load(Filename);
      if (i > 10)
        Population[i].randomMutation();
    }
    resetConditions();
  }

  void resetConditions() {
    for (auto &e : Population)
      e.resetUnit();
    t = 0;
  }

  float getTime() { return t; }
  float getDt() { return dt; }

  void setTrack(size_t i) {
    for (auto &e : Population)
      e.setTrack(tracks[i]);
  }

  void slowDown(float dv) {
    SlowDown += dv;
    if (SlowDown < 0)
      SlowDown = 0;
  }

  void addTrack(Track *track) {
    tracks.push_back(track);
    D.push_back(0);
  }

  void getTrack() { return tracks[idTrack]; }

protected:
  void simulate() {
    isRunning = true;
    StopSimulation = false;
    resetConditions();
    std::cout << "Thread Started" << std::endl;
    size_t iMazeChange = 0;
    while (!StopSimulation) {
      std::cout << "Generation = " << generation << std::endl;
      bool done = false;
      while (t < TMax && !done) {
        done = true;
#pragma omp parallel for
        for (int i = 0; i < N; ++i) {
          auto &e = Population[i];
          if (e.isAlive()) {
            e.update(dt);
            done = false;
          }
        }
        t += dt;
        if (SlowDown)
          Sleep(SlowDown);
      }
      TMax += 0.1;

      int isCollided = 0;
      int isNotAlive = 0;
      for (auto &e : Population) {
        if (e.isCollided())
          isCollided++;
        if (!e.isAlive())
          isNotAlive++;       
        e.updateFitnessVal();
      }

      Sorting = true;
      sortPopulation();
      Sorting = false;
      D[idTrack] = Population[0].getDistance();
      float AvgD = 0;
      for (size_t i = 0; i <= idTrack; ++i)
        AvgD += D[i];
      AvgD = AvgD / (idTrack + 1);

      std::cout << " Collided = " << isCollided
                << " Death toll = " << isNotAlive << std::endl;
      for (size_t i = 0; i < 10; ++i) {
        auto &a = Population[i];
        std::cout << a.isAlive() << "  --- > "
                  << "D = " << a.getDistance() << " E = " << a.getEnergy()
                  << " F = " << a.getFitnessVal();
        std::cout << " d = " << a.getDistanceT() << std::endl;
      }
      std::cout << "Track = " << idTrack << " Max D = " << D[idTrack]
                << "  AvgD = " << AvgD << std::endl;

      nextGeneration();
      iMazeChange++;
      if (iMazeChange > 5) {
        idTrack++;
        if (idTrack >= tracks.size())
          idTrack = 0;
        // idTrack = rand() % tracks.size();
        setTrack(idTrack);
        iMazeChange = 0;
        std::cout << "Saving" << std::endl;
        saveMostFit("nn/best01.nn");
      }
      resetConditions();
    }
    isRunning = false;
    std::cout << "Thread Stop" << std::endl;
  }

  static void *static_simulate(void *This) {
    ((GA *)This)->simulate();
    return NULL;
  }

  void newPopulation() {
    for (size_t i = 0; i < N; ++i)
      Population[i] = RobotUnit();
  }

  void sortPopulation() {
    float eps = 2;
    std::sort(Population.begin(), Population.end(),
              [eps](const RobotUnit &a, const RobotUnit &b)
                  -> bool { return a.getFitnessVal() > b.getFitnessVal(); });
  }

  void nextGeneration() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(seed);
    int k = 3;
    std::uniform_int_distribution<int> uniform(0, N / k - 1);
    int j = 0;
    for (size_t i = N / k; i < N; ++i) {
      size_t i0 = uniform(generator);
      size_t i1 = uniform(generator);
      while (i1 != i0) {
        i1 = uniform(generator);
      }
      const FFNN3L &NN1 = Population[i0].getNN();
      const FFNN3L &NN2 = Population[i1].getNN();
      j++;
      Population[i].crossOver(NN1, NN2);
      Population[i].randomMutation();
    }
    generation++;
  }

private:
  size_t N;
  std::vector<RobotUnit> Population;
  float TMax;
  float t;
  size_t generation;
  float InitialAngle;
  std::vector<Track *> tracks;
  std::vector<float> D;
  size_t idTrack;
  bool StopSimulation;
  bool isRunning;
  float dt;
  float SlowDown;
  bool Sorting;
};

#endif
