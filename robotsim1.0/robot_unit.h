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

class RobotUnit {
 public:
  RobotUnit() : NNPath(5, 8, 3), NNKinetic(3, 8, 2) {
    glow = false;
  }

  void setPos(const Point2d& p) { robot.setPos(p); }

  void render() { robot.render(glow); }

  void setTarget(const Point2d& t, float angle) {
    Target = t;
    Ttheta = angle;
  }

  void updateRelativeTarget() {  
    dtheta = Ttheta - robot.getAngle();
    float dx = Target.x - robot.getX();
    float dy = Target.y - robot.getY();
    float r = sqrt(dx * dx + dy * dy);
    DTarget.x = -r * sin(robot.getAngle());
    DTarget.y = r * cos(robot.getAngle());
  }

  void setNNKinetic(const FFNN3L& net) { NNKinetic = net; }

  void update(float dt) {
    updateRelativeTarget();

    std::vector<double> PathIn(5);
    std::vector<double> PathOut(3);
    PathIn[0] = robot.getMotorLeft() / 100.0f;
    PathIn[1] = robot.getMotorRight() / 100.0f;
    PathIn[2] = DTarget.x;
    PathIn[3] = DTarget.y;
    PathIn[4] = dtheta;
    NNPath.feedForward(PathIn, PathOut);

    std::vector<double> KineticOut[2];
    //NNKinetic.feedForward(PathOut, KineticOut);

    //robot.setMotors(KineticOut[0] * 100, KineticOut[1] * 100);
    robot.update(dt);
  }

  void setGlow() { glow = true; }

  FFNN3L& getNNPath() { return NNPath; }

  void crossOver(FFNN3L& x, FFNN3L& y) {
    static std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0, 1);
    size_t NI = NNPath.getNI();
    size_t NH = NNPath.getNH();
    size_t NO = NNPath.getNO();

    float ir = 0.7f;  // distribution(generator);

    for (size_t j = 0; j < NH; ++j) {
      if (j <= ir * NH)
        for (size_t i = 0; i <= NI; ++i) NNPath.getW0()[j][i] = x.getW0()[j][i];
      else
        for (size_t i = 0; i <= NI; ++i) NNPath.getW0()[j][i] = y.getW0()[j][i];
    }

    for (size_t j = 0; j < NO; ++j) {
      if (j <= ir * NO)
        for (size_t i = 0; i <= NH; ++i) NNPath.getW1()[j][i] = x.getW1()[j][i];
      else
        for (size_t i = 0; i <= NH; ++i) NNPath.getW1()[j][i] = y.getW1()[j][i];
    }
  }

 private:
  FFNN3L NNPath;
  FFNN3L NNKinetic;
  Robot robot;
  bool glow;
  Point2d Target;
  float Ttheta;
  Point2d DTarget;
  float dtheta;
};

#endif