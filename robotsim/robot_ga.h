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
#include "track.h"

class RobotGA {
 public:
  RobotGA(size_t NSensors = 5)
      : NN(9, 14, 2),
        NSensors(NSensors),
        DistSensors(NSensors),
        Distance(0),
        MaxDistance(1) {
    glow = false;
    collided = false;
    T = 0;
  }

  void setPos(const Point2d& p) { robot.setPos(p); }
  void setPos(const Point2d& p, float angle) { robot.setPos(p, angle); }
  void setT(float t = 0) { T = t; }
  float getT() const { return T; }

  void render() {
    robot.render(glow);
    if (glow) renderSensorLines();
  }

  void setNN(const FFNN3L& net) { NN = net; }

  void update(float dt, const Track& track) {
    std::vector<double> Input(8);
    std::vector<double> Output(2);
    Input[0] = robot.getMotorLeft() / 100.0f;
    Input[1] = robot.getMotorRight() / 100.0f;
    Input[2] = DistSensors[0] / 100.0f - 1;
    Input[3] = DistSensors[1] / 100.0f - 1;
    Input[4] = DistSensors[2] / 100.0f - 1;
    Input[5] = DistSensors[3] / 100.0f - 1;
    Input[6] = DistSensors[4] / 100.0f - 1;
    Input[7] = robot.getAngle() / M_PI - 1;
    Input[8] = Distance / MaxDistance;
    NN.feedForward(Input, Output);
    robot.setMotors(Output[0] * 100, Output[1] * 100);
    robot.update(dt);
    T += dt;
    if (checkCollision(track)) setCollided(true);
    updateSensorDistances(track);
    updateTraveledDistance(track);
  }

  void renderSensorLines() {
    Point2d C = robot.pos();
    float theta = robot.getAngle();
    glColor3f(0.5, 0.5, 0.5);
    float dalpha = M_PI / (NSensors - 1);
    for (size_t i = 0; i < 5; ++i) {
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

  bool SegmentCircleIntersection(const Edge2d& E, const Point2d& C, float r) {
    Point2d A = E.p0;
    Point2d B = E.p1;
    Point2d V = B - A;
    Point2d P = C - A;
    float Vnorm = V.norm();
    float projv = dot(V, P) / Vnorm;
    if (projv < 0) return (P.norm() <= r);
    if (projv > Vnorm) return (distance(C, B) <= r);
    Point2d Proj = projv * V / Vnorm;
    return (distance(C, A + Proj) <= r);
  }

  bool LineEdgeIntersection(const Edge2d& E, const Edge2d& L, Point2d& I) {
    Point2d v = L.p1 - L.p0;
    Point2d u = E.p1 - E.p0;
    Point2d vp(-v.y, v.x);
    float t = dot(L.p0 - E.p0, vp);
    float denom = dot(u, vp);

    if (denom == 0) return false;
    t /= denom;
    if (t < 0 || t > 1) return false;
    I = E.p0 + t * u;
    return true;
  }

  bool RayEdgeIntersection(const Edge2d& E, const Edge2d& L, Point2d& I) {
    Point2d v = L.p1 - L.p0;  // we assume v
    Point2d u = E.p1 - E.p0;
    Point2d vp(-v.y, v.x);
    Point2d s = L.p0 - E.p0;
    float t2 = dot(s, vp);
    float denom = dot(u, vp);

    if (denom == 0) return false;
    t2 /= denom;
    if (t2 < 0 || t2 > 1) return false;

    float t1 = (s.y * u.x - s.x * u.y) / denom;
    if (t1 < 0) return false;

    I = E.p0 + t2 * u;
    return true;
  }

  bool isCollided() { return collided; }
  void setCollided(bool v = true) { collided = v; }

  bool checkCollision(const Track& track) {
    Point2d C = robot.pos();
    float R = robot.getR();
    for (auto& e : track.getEdges())
      if (SegmentCircleIntersection(e, C, R)) return true;
    return false;
  }

  void updateSensorDistances(const Track& track) {
    Point2d C = robot.pos();
    float theta = robot.getAngle();
    float dalpha = M_PI / (NSensors - 1);
    float MaxDistance = 200;
    for (size_t i = 0; i < NSensors; ++i) {
      DistSensors[i] = MaxDistance;
      Point2d Q(C.x + 10 * cos(theta - M_PI / 2 + i * dalpha),
                C.y + 10 * sin(theta - M_PI / 2 + i * dalpha));
      Edge2d L(C, Q);
      Point2d I;
      for (auto& e : track.getEdges())
        if (RayEdgeIntersection(e, L, I)) {
          float d = distance(C, I);
          if (DistSensors[i] > d) DistSensors[i] = d;
        }
    }
  }

  float updateTraveledDistance(const Track& track) {
    const std::vector<Point2d>& landmarks = track.getLandmarks();
    MaxDistance = track.getDk()[0];

    size_t MSize = landmarks.size();
    float dmin = 10e20;
    size_t kmin = 0;
    for (size_t i = 0; i < MSize; ++i) {
      float d = distance(robot.pos(), landmarks[i]);
      if (d < dmin) {
        dmin = d;
        kmin = i;
      }
    }
    Distance = dmin;
    if (kmin == MSize - 1) return Distance;

    Point2d P = robot.pos() - landmarks[kmin];
    Point2d V = landmarks[kmin + 1] - landmarks[kmin];
    float Projv = dot(P, V) / V.norm();
    Distance = track.getDk()[kmin] - Projv;
    return Distance;
  }

  float getDistance() const { return Distance; }

  void setGlow(bool v = true) { glow = v; }
  bool isGlow() { return glow; }

  FFNN3L& getNN() { return NN; }

  void crossOver(const FFNN3L& x, const FFNN3L& y) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> distribution(0, 1);
    size_t NI = NN.getNI();
    size_t NH = NN.getNH();
    size_t NO = NN.getNO();

    float ir = 0.5f;  // distribution(generator);

    for (size_t j = 0; j < NH; ++j) {
      if (j < ir * NH)
        for (size_t i = 0; i <= NI; ++i) NN.getW0()[j][i] = x.getW0()[j][i];
      else
        for (size_t i = 0; i <= NI; ++i) NN.getW0()[j][i] = y.getW0()[j][i];
    }

    for (size_t j = 0; j < NO; ++j) {
      if (j < ir * NO)
        for (size_t i = 0; i <= NH; ++i) NN.getW1()[j][i] = x.getW1()[j][i];
      else
        for (size_t i = 0; i <= NH; ++i) NN.getW1()[j][i] = y.getW1()[j][i];
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

    float k = 6.0f;
    float pr = 0.8f;

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

  void save(const std::string& Filename) { NN.save(Filename); }

  void load(const std::string& Filename) { NN.load(Filename); }

 private:
  FFNN3L NN;
  Robot robot;
  bool glow;
  size_t NSensors;
  std::vector<float> DistSensors;
  bool collided;
  float Distance;
  float MaxDistance;
  float T;
};

#endif