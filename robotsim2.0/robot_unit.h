#ifndef ROBOTUNIT_H
#define ROBOTUNIT_H

#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <chrono>
#include "include/glheaders.h"
#include "include/glprimitives.h"
#include "ffnn3l.h"
#include "point2d.h"
#include "robot.h"
#include "track.h"
#include "geometry_utils.h"

class RobotUnit {
public:
  RobotUnit(size_t NSensors = 7)
      : NN(NSensors + 2, NSensors + 6, 2), NSensors(NSensors),
      DistSensors(NSensors), collided(false), glow(false), t(0), Distance(0), DistanceT(0),
        track(0), angle0(0) {}

  void render() {
    float r = 1;
    float g = 1;
    float b = 1;
    if (collided) {
      g = 0;
      b = 0;
    }
    robot.render(r, g, b, glow);
    if (glow)
      renderSensorLines();
  }

  void renderSensorLines() {
    Point2d C = robot.getPos();
    float theta = robot.getAngle();
    glColor3f(0.5, 0.5, 0.5);
    float dalpha = M_PI / (NSensors - 1);
    for (size_t i = 0; i < NSensors; ++i) {
      float r = DistSensors[i];
      Point2d Q(C.x + r * cos(theta - M_PI / 2 + i * dalpha),
                C.y + r * sin(theta - M_PI / 2 + i * dalpha));
      drawDisk(Q.x, Q.y, 1, 20);
      glBegin(GL_LINES);
      glVertex2f(C.x, C.y);
      glVertex2f(Q.x, Q.y);
      glEnd();
    }
  }

  FFNN3L &getNN() { return NN; }
  void setNN(const FFNN3L &net) { NN = net; }
  void setPos(const Point2d &p) { robot.setPos(p); }
  void setPos(const Point2d &p, float angle) { robot.setPos(p, angle); }

  bool isCollided() const { return collided; }
  void setCollided(bool v = true) { collided = v; }
  void setTime(float T) { t = T; }
  float getTime() const { return t; }
  void setGlow(bool v) { glow = v; }
  float getDistance() const { return Distance; }
  float setDistance(float v) { Distance = v; }
  float getDistanceT() const { return DistanceT;  }

  void update(float dt) {
    if (!isCollided()) {
      std::vector<double> Input;
      std::vector<double> Output(2);
      Input.push_back(robot.getMotorLeft() / 100.0f);
      Input.push_back(robot.getMotorRight() / 100.0f);
      for (size_t i = 0; i < NSensors; ++i)
        Input.push_back(DistSensors[i] / 100.0f - 1);

      NN.feedForward(Input, Output);
      robot.setMotors(Output[0] * 100, Output[1] * 100);
      Point2d p = robot.getPos();
      robot.update(dt);
      DistanceT += distance(p, robot.getPos());
      t += dt;

      if (checkCollision()) {
        setCollided(true);
      } else {
        updateSensorDistances();
        updateVisitedLandmarks();
      }
    }
  }

  bool checkCollision() {
    Point2d C = robot.getPos();
    float R = robot.getR();
    for (auto &e : track->getEdges())
      if (SegmentCircleIntersection(e, C, R))
        return true;
    return false;
  }

  void updateSensorDistances() {
    Point2d C = robot.getPos();
    float theta = robot.getAngle();
    float dalpha = M_PI / (NSensors - 1);
    float MD = 200;
    for (size_t i = 0; i < NSensors; ++i) {
      DistSensors[i] = MD;
      Point2d Q(C.x + 10 * cos(theta - M_PI / 2 + i * dalpha),
                C.y + 10 * sin(theta - M_PI / 2 + i * dalpha));
      Edge2d L(C, Q);
      Point2d I;
      for (auto &e : track->getEdges())
        if (RayEdgeIntersection(e, L, I)) {
          float d = distance(C, I);
          if (DistSensors[i] > d)
            DistSensors[i] = d;
        }
    }
  }

  void crossOver(const FFNN3L &x, const FFNN3L &y) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> distribution(0, 0.5);
    size_t NI = NN.getNI();
    size_t NH = NN.getNH();
    size_t NO = NN.getNO();

    float ir1 = 0.7f; // distribution(generator);
    float ir2 = 0.5f; // distribution(generator);

    for (size_t j = 0; j < NH; ++j) {
      if (j < ir1 * NH)
        for (size_t i = 0; i <= NI; ++i)
          NN.getW0()[j][i] = x.getW0()[j][i];
      else
        for (size_t i = 0; i <= NI; ++i)
          NN.getW0()[j][i] = y.getW0()[j][i];
    }

    for (size_t j = 0; j < NO; ++j) {
      if (j < ir2 * NO)
        for (size_t i = 0; i <= NH; ++i)
          NN.getW1()[j][i] = x.getW1()[j][i];
      else
        for (size_t i = 0; i <= NH; ++i)
          NN.getW1()[j][i] = y.getW1()[j][i];
    }
  }

  void randomMutation() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> uniform(0, 1);
    std::normal_distribution<float> normal(0, 1);

    size_t NI = NN.getNI();
    size_t NH = NN.getNH();
    size_t NO = NN.getNO();

    float k = 3.0f;
    float pr = 0.75f;

    for (size_t j = 0; j < NH; ++j)
      for (size_t i = 0; i <= NI; ++i)
        if (uniform(generator) > pr) {
          NN.getW0()[j][i] =
              fabs(NN.getW0()[j][i] / k) * normal(generator) + NN.getW0()[j][i];
        }

    for (size_t j = 0; j < NO; ++j)
      for (size_t i = 0; i <= NH; ++i)
        if (uniform(generator) > pr) {
          NN.getW1()[j][i] =
              fabs(NN.getW1()[j][i] / k) * normal(generator) + NN.getW1()[j][i];
        }
  }

  void save(const std::string &Filename) { NN.save(Filename); }
  void load(const std::string &Filename) { NN.load(Filename); }

  void updateVisitedLandmarks() {
    auto &e = track->getLandmarks();
    for (size_t i = 0; i < e.size(); ++i)
      if (distance(robot.getPos(), e[i]) < 15) {
        Landmarks[i] = true;
        break;
      }
    Distance = 0;
    for (size_t i = 0; i < Landmarks.size(); ++i)
      if (Landmarks[i])
        Distance++;
  }

  void setTrack(Track *trk, float angle = 0) {
    track = trk;
    angle0 = angle;
    Landmarks.resize(track->getLandmarks().size());
    resetUnit();
  }

  void resetUnit() {
    if (track) {
      robot.setPos(track->getInitialPoint(), angle0);
      robot.setMotors(0, 0);
      t = 0;
      collided = false;
      Distance = 0;
      DistanceT = 0;
      std::fill(Landmarks.begin(), Landmarks.end(), false);
      updateSensorDistances();
    }
  }

  float distanceToTarget() { return 0; }

private:
  FFNN3L NN;
  Robot robot;
  size_t NSensors;
  std::vector<float> DistSensors;
  bool collided;
  bool glow;
  float t;
  float Distance;
  float DistanceT;
  Track *track;
  std::vector<bool> Landmarks;
  float angle0;
};

#endif