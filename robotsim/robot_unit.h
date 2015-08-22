#ifndef ROBOT_UNIT_H
#define ROBOT_UNIT_H

#include "include/glheaders.h"
#include "include/glprimitives.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include "ffnn3l.h"
#include "point2d.h"
#include "robot.h"

#define NI 5
#define NH 8
#define NO 2

class RobotUnit {
 public:
  RobotUnit() : brain(NI, NH, NO), input(NI), output(NO), distances(5) {
    static std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 2 * M_PI);
    float thetaRobot =  distribution(generator);
    robot.setAngle(thetaRobot);
    glow = false;
  }

  void setPos(const Point2d& p) {
    robot.setPos(p);
  }

  void render() { 
    robot.render(glow); 
  }

  void update(float dt) {
    input[0] = robot.getMotorLeft() / 100.0f;
    input[1] = robot.getMotorRight() / 100.0f;
    input[2] = 0;
    input[3] = 0;
    input[4] = robot.getAngle() / M_PI - 1;
    brain.feedForward(input, output);
    robot.setMotors(output[0] * 100, output[1] * 100);
    robot.update(dt);
  }

  float getV() {
    return (fabs(robot.getMotorRight()) + fabs(robot.getMotorLeft())) / 2;
  }

  float getDistance2() const {
    float dx = 0;
    float dy = 0;
    return dx * dx + dy * dy;
  }

  void setGlow() { glow = true; }

  FFNN3L& getBrain() {
    return brain;
  }


  void randomMutation() {
    static std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 100);
    std::normal_distribution<double> normal(0, 0.001f);

    size_t p = distribution(generator);
    if (p > 10) return;

    for (size_t j = 0; j < NH; ++j) {
      for (size_t i = 0; i <= NI; ++i) {
          size_t ir = distribution(generator);
          if (ir < 1)
            brain.getW0()[j][i] += normal(generator);
      }
    }

    for (size_t j = 0; j < NO; ++j) {
      for (size_t i = 0; i <= NH; ++i) {
        size_t ir = distribution(generator);
        if (ir < 1)
          brain.getW1()[j][i] += normal(generator);
      }
    }
  }

  void getParentGenes(FFNN3L& x) {
    for (size_t j = 0; j < NH; ++j) {
      for (size_t i = 0; i <= NI; ++i) {
         brain.getW0()[j][i] = x.getW0()[j][i];
      }
    }

    for (size_t j = 0; j < NO; ++j) {
      for (size_t i = 0; i <= NH; ++i) {
        brain.getW1()[j][i] = x.getW1()[j][i];
      }
    }
  }

  void getParentsGenes(FFNN3L& x, FFNN3L& y) {
    static std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 1);

    for (size_t j = 0; j < NH; ++j) {
      for (size_t i = 0; i <= NI; ++i) {
        size_t ir = distribution(generator);
        if (ir == 0)
          brain.getW0()[j][i] = x.getW0()[j][i];
        else
          brain.getW0()[j][i] = y.getW0()[j][i];
      }
    }

    for (size_t j = 0; j < NO; ++j) {
      for (size_t i = 0; i <= NH; ++i) {
        size_t ir = distribution(generator);
        if (ir == 0)
          brain.getW1()[j][i] = x.getW1()[j][i];
        else
          brain.getW1()[j][i] = y.getW1()[j][i];
      }
    }
  }

 private:
  FFNN3L brain;
  Robot robot;
  std::vector<double> input;
  std::vector<double> output;
  std::vector<float> distances;
  bool glow;
};

#endif