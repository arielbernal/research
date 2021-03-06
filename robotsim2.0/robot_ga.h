#ifndef ROBOTGA_H
#define ROBOTGA_H

// #include "include/glheaders.h"
// #include "include/glprimitives.h"
// #include <iostream>
// #include <cmath>
// #include <vector>
// #include <queue>
// #include <algorithm>
// #include <functional>
// #include "ffnn3l.h"
// #include "point2d.h"
// #include "robot.h"
// #include "track.h"

// class RobotGA {
//  public:
//   RobotGA(size_t NSensors = 7)
//       : NN(11, 16, 2),
//         NSensors(NSensors),
//         DistSensors(NSensors),
//         Distance(0),
//         MaxDistance(1) {
//     glow = false;
//     collided = false;
//     T = 0;
//     TTarget = 0;
//     AtTarget = false;
//   }

//   void setPos(const Point2d& p) { robot.setPos(p); }
//   void setPos(const Point2d& p, float angle) { robot.setPos(p, angle); }
//   void setT(float t = 0) { T = t; }
//   float getT() const { return T; }
//   float getTargetTime() const { return TTarget; }
//   bool isAtTarget() const { return AtTarget; }

//   void render() {
//     robot.render(glow);
//     if (glow) renderSensorLines();
//   }

//   void setNN(const FFNN3L& net) { NN = net; }

//   void update(float dt, const Track& track) {
//     std::vector<double> Input(11);
//     std::vector<double> Output(2);
//     Input[0] = robot.getMotorLeft() / 100.0f;
//     Input[1] = robot.getMotorRight() / 100.0f;
//     Input[2] = DistSensors[0] / 100.0f - 1;
//     Input[3] = DistSensors[1] / 100.0f - 1;
//     Input[4] = DistSensors[2] / 100.0f - 1;
//     Input[5] = DistSensors[3] / 100.0f - 1;
//     Input[6] = DistSensors[4] / 100.0f - 1;
//     Input[7] = DistSensors[5] / 100.0f - 1;
//     Input[8] = DistSensors[6] / 100.0f - 1;
//     Input[9] = robot.getAngle() / M_PI - 1;
//     Input[8] = Distance / MaxDistance;
//     NN.feedForward(Input, Output);
//     robot.setMotors(Output[0] * 100, Output[1] * 100);
//     robot.update(dt);
//     T += dt;
//     if (!isCollided()) {
//       if (checkCollision(track)) {
//         setCollided(true);
//       } else {
//         updateSensorDistances(track);
//         updateTraveledDistance(track);
//       }
//     }
//   }

//   void renderSensorLines() {
//     Point2d C = robot.pos();
//     float theta = robot.getAngle();
//     glColor3f(0.5, 0.5, 0.5);
//     float dalpha = M_PI / (NSensors - 1);
//     for (size_t i = 0; i < NSensors; ++i) {
//       float r = DistSensors[i];
//       Point2d Q(C.x + r * cos(theta - M_PI / 2 + i * dalpha),
//                 C.y + r * sin(theta - M_PI / 2 + i * dalpha));

//       drawDisk(Q.x, Q.y, 1, 20);
//       glBegin(GL_LINES);
//       glVertex2f(C.x, C.y);
//       glVertex2f(Q.x, Q.y);
//       glEnd();
//     }
//   }

  
//   bool isCollided() { return collided; }
//   void setCollided(bool v = true) { collided = v; }

//   bool checkCollision(const Track& track) {
//     Point2d C = robot.pos();
//     float R = robot.getR();
//     for (auto& e : track.getEdges())
//       if (SegmentCircleIntersection(e, C, R)) return true;
//     return false;
//   }

//   void updateSensorDistances(const Track& track) {
//     Point2d C = robot.pos();
//     float theta = robot.getAngle();
//     float dalpha = M_PI / (NSensors - 1);
//     float MD = 200;
//     for (size_t i = 0; i < NSensors; ++i) {
//       DistSensors[i] = MD;
//       Point2d Q(C.x + 10 * cos(theta - M_PI / 2 + i * dalpha),
//                 C.y + 10 * sin(theta - M_PI / 2 + i * dalpha));
//       Edge2d L(C, Q);
//       Point2d I;
//       for (auto& e : track.getEdges())
//         if (RayEdgeIntersection(e, L, I)) {
//           float d = distance(C, I);
//           if (DistSensors[i] > d) DistSensors[i] = d;
//         }
//     }
//   }

//   float updateTraveledDistance(const Track& track) {
//     const std::vector<Point2d>& landmarks = track.getLandmarks();
//     MaxDistance = track.getDk()[0];

//     size_t MSize = landmarks.size();
//     float dmin = 10e20;
//     size_t kmin = 0;
//     for (size_t i = 0; i < MSize; ++i) {
//       float d = distance(robot.pos(), landmarks[i]);
//       if (d < dmin) {
//         dmin = d;
//         kmin = i;
//       }
//     }
//     Distance = dmin;
//     if (kmin != MSize - 1) {
//       Point2d P = robot.pos() - landmarks[kmin];
//       Point2d V = landmarks[kmin + 1] - landmarks[kmin];
//       float Projv = dot(P, V) / V.norm();
//       Distance = track.getDk()[kmin] - Projv;
//     }

//     if (Distance < 2) {
//       // if (!AtTarget) {
//       //   TTarget = T;
//       //   AtTarget = true;
//       // }
//       AtTarget = true;
//       if (fabs(robot.getMotorRight()) > 5 && fabs(robot.getMotorLeft()) > 5)  {
//         TTarget = T;
//       }
//     } else {
//       AtTarget = false;
//     }


//     return Distance;
//   }

//   float getDistance() const { return Distance; }
//   void setDistance(float d) { Distance = 0; }
//   void setAtTarget(bool v) { AtTarget = v; }
//   void setTTarget(float t) { TTarget = t; }

//   void setGlow(bool v = true) { glow = v; }
//   bool isGlow() { return glow; }

//   FFNN3L& getNN() { return NN; }

//   void crossOver(const FFNN3L& x, const FFNN3L& y) {
//     unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//     static std::default_random_engine generator(seed);
//     std::uniform_real_distribution<float> distribution(0, 0.5);
//     size_t NI = NN.getNI();
//     size_t NH = NN.getNH();
//     size_t NO = NN.getNO();

//     float ir1 = 0.5f;  // distribution(generator);
//     float ir2 = 0.5f;  // distribution(generator);

//     for (size_t j = 0; j < NH; ++j) {
//       if (j < ir1 * NH)
//         for (size_t i = 0; i <= NI; ++i) NN.getW0()[j][i] = x.getW0()[j][i];
//       else
//         for (size_t i = 0; i <= NI; ++i) NN.getW0()[j][i] = y.getW0()[j][i];
//     }

//     for (size_t j = 0; j < NO; ++j) {
//       if (j < ir2 * NO)
//         for (size_t i = 0; i <= NH; ++i) NN.getW1()[j][i] = x.getW1()[j][i];
//       else
//         for (size_t i = 0; i <= NH; ++i) NN.getW1()[j][i] = y.getW1()[j][i];
//     }
//   }

//   void randomMutation() {
//     unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//     static std::default_random_engine generator(seed);
//     std::uniform_real_distribution<float> uniform(0, 1);
//     std::normal_distribution<float> normal(0, 1);

//     size_t NI = NN.getNI();
//     size_t NH = NN.getNH();
//     size_t NO = NN.getNO();

//     float k = 3.0f;
//     float pr = 0.75f;

//     for (size_t j = 0; j < NH; ++j)
//       for (size_t i = 0; i <= NI; ++i)
//         if (uniform(generator) > pr) {
//           NN.getW0()[j][i] =
//               fabs(NN.getW0()[j][i] / k) * normal(generator) + NN.getW0()[j][i];
//         }

//     for (size_t j = 0; j < NO; ++j)
//       for (size_t i = 0; i <= NH; ++i)
//         if (uniform(generator) > pr) {
//           NN.getW1()[j][i] =
//               fabs(NN.getW1()[j][i] / k) * normal(generator) + NN.getW1()[j][i];
//         }
//   }

//   void save(const std::string& Filename) { NN.save(Filename); }

//   void load(const std::string& Filename) { NN.load(Filename); }

//  private:
//   FFNN3L NN;
//   Robot robot;
//   bool glow;
//   size_t NSensors;
//   std::vector<float> DistSensors;
//   bool collided;
//   float Distance;
//   float MaxDistance;
//   float T;
//   float TTarget;
//   bool AtTarget;
// };

#endif