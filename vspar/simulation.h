#ifndef SIMULATION_H
#define SIMULATION_H

#include <pthread.h>
#include <unistd.h>
#include "particles.h"

class Simulation {
 public:
  enum status { READY, RUNNING, SUSPENDED, TERMINATED };

  Simulation(ParticleSystem *p)
      : requestTermination(false),
        suspendThread(true),
        stepMode(false),
        doStep(false),
        status(0),
        ps(p) {
    pthread_create(&mainThread, NULL, &Simulation::simulationThreadStatic,
                   this);
  }

  void simulationThread() {
    status = READY;
    size_t i = 0;
    while (!requestTermination) {
      if (!suspendThread) {
        if (!stepMode || doStep) {
          status = RUNNING;
          nextStep(i);
          ++i;
          if (stepMode) {
            status = READY;
            doStep = false;
          }
        } else {
          usleep(10000);
        }
      } else {
        if (status != SUSPENDED) {
          status = SUSPENDED;
          printStatus();
        }
        usleep(10000);
      }
    }
    status = TERMINATED;
    std::cout << "simulationThread finishing\n";
    pthread_exit(0);
  }

  void start() { suspendThread = false; }

  void terminate() { requestTermination = true; }

  void suspend() { suspendThread = true; }
  void resume() { suspendThread = false; }
  void step() {
    if (stepMode) {      
      doStep = true;
      if (suspendThread) suspendThread = false;
    }
  }

  void setStepMode(bool val) {
    stepMode = val;
    std::cout << (val ? "stepModeOn\n" : "stepModeOff\n");
  }

  bool isSuspended() { return (status == SUSPENDED); }
  bool isRunning() { return (status == RUNNING); }
  bool isReady() { return (status == READY); }
  bool isTerminated() { return status == TERMINATED; }

  void printStatus() {
    std::string st;
    if (status == SUSPENDED) st = "SUSPENDED";
    if (status == RUNNING) st = "RUNNING";
    if (status == TERMINATED) st = "TERMINATED";
    if (status == READY) st = "READY";
    std::cout << "Status = " << st << " - "
              << (stepMode ? "stepModeOn\n" : "stepModeOff\n");
  }

 protected:
  static void *simulationThreadStatic(void *This) {
    ((Simulation *)This)->simulationThread();
    return 0;
  }

  void nextStep(size_t i) { ps->step(0.01f); }

 private:
  pthread_t mainThread;
  bool requestTermination;
  bool suspendThread;
  bool stepMode;
  bool doStep;
  int status;
  ParticleSystem *ps;
};

#endif  // SIMULATION_H