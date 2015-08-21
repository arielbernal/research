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
  RobotUnit(float d = 50) : brain(NI, NH, NO), d(d), input(NI), output(NO) {
    static std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 2 * M_PI);
    float thetaTarget = distribution(generator);
    target.x = cos(thetaTarget) * d;
    target.y = sin(thetaTarget) * d;
    float thetaRobot =  distribution(generator);
    robot.setAngle(thetaRobot);
    glow = false;
  }

  void print() {
    std::cout << "T = " << target.x << ", " << target.y
              << " Theta = " << RAD(robot.getAngle()) << std::endl;
  }

  void render() { 
    robot.render(glow); 
    //glColor3f(1, 1, 0);
    //glBegin(GL_LINES);
    //glVertex2f(robot.getX(), robot.getY());
    //glVertex2f(target.x, target.y);
    //glEnd();
  }

  Point2d getTarget() { return target; }

  void update(float dt) {
    input[0] = robot.getMotorLeft() / 100.0f;
    input[1] = robot.getMotorRight() / 100.0f;
    input[2] = target.x - robot.getX();
    input[3] = target.y - robot.getY();
    input[4] = robot.getAngle();
    brain.feedForward(input, output);
    robot.setMotors(output[0] * 100, output[1] * 100);
    robot.update(dt);
  }

  float getV() {
    return (fabs(robot.getMotorRight()) + fabs(robot.getMotorLeft())) / 2;
  }

  float getDistance2() const {
    float dx = target.x - robot.getX();
    float dy = target.y - robot.getY();
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
  Point2d target;
  float d;
  std::vector<double> input;
  std::vector<double> output;
  bool glow;
};

#endif