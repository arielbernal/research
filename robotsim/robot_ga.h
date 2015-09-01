#ifndef ROBOTGA_H
#define ROBOTGA_H

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

class RobotGA {
 public:
  RobotGA(size_t NSensors = 5) : NN(3, 8, 2), NSensors(NSensors) {
    glow = false;
  }
  
  void setPos(const Point2d& p) { robot.setPos(p); }
  void setPos(const Point2d& p, float angle) { robot.setPos(p, angle); }

  void render() { robot.render(glow); }

  void setNN(const FFNN3L& net) { NN = net; }

  void update(float dt) {
    std::vector<double> Input(5);
    std::vector<double> Output(3);
    Input[0] = robot.getMotorLeft() / 100.0f;
    Input[1] = robot.getMotorRight() / 100.0f;
//    Input[2] = DTarget.x;
//    Input[3] = DTarget.y;
//    Input[4] = dtheta;
    
    //NN.feedForward(Input, Output);
    //robot.setMotors(Output[0] * 100, Output[1] * 100);
    robot.update(dt);
  }

  bool checkCollision(const Track& track) {
    Point2d C = robot.pos();
    float R = robot.getR();
    for (auto &e : track.getEdges()) {
      Point2d A = e.p0;
      Point2d B = e.p1;
    
      Point2d BA = B - A;
      Point2d CA = C - A;
      float area2 = fabs(BA.x * CA.y - BA.y * CA.x);
      float LAB = BA.norm();
      float h = area2 / LAB;
      if (h < R) return true;
    }
    return false;
  }



  void setGlow() { glow = true; }

  FFNN3L& getNN() { return NN; }

  void crossOver(FFNN3L& x, FFNN3L& y) {
    static std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0, 1);
    size_t NI = NN.getNI();
    size_t NH = NN.getNH();
    size_t NO = NN.getNO();

    float ir = 0.7f;  // distribution(generator);

    for (size_t j = 0; j < NH; ++j) {
      if (j <= ir * NH)
        for (size_t i = 0; i <= NI; ++i) NN.getW0()[j][i] = x.getW0()[j][i];
      else
        for (size_t i = 0; i <= NI; ++i) NN.getW0()[j][i] = y.getW0()[j][i];
    }

    for (size_t j = 0; j < NO; ++j) {
      if (j <= ir * NO)
        for (size_t i = 0; i <= NH; ++i) NN.getW1()[j][i] = x.getW1()[j][i];
      else
        for (size_t i = 0; i <= NH; ++i) NN.getW1()[j][i] = y.getW1()[j][i];
    }
  }

 private:
  FFNN3L NN;
  Robot robot;
  bool glow;
  size_t NSensors;
};

#endif