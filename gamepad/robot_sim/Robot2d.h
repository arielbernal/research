#ifndef GLROBOT2D_H
#define GLROBOT2D_H

#include <svector.h>

using namespace svector;

class Robot2D {
public:
  Robot2D(float L, float rw, float x0, float y0, float theta)
      : L(L), rw(rw), T(0), x(x0), y(y0), theta(theta), xEst(0), yEst(0),
        tEst(0), thetaEst(theta), xTarget(x), yTarget(y) {}

  void setPos(float xp, float yp, float thetap) {
    x = xp;
    y = yp;
    theta = thetap;
    thetaEst = theta;
  }

#define MAXRPS 2

  void setThrottle(float throttleL, float throttleR) { // 0..255
    WL = throttleL / 255.0f * MAXRPS;
    WR = throttleR / 255.0f * MAXRPS;
  }

  void forwardKinematics(float VL, float VR, float dt, float x, float y,
                         float theta, float &xp, float &yp, float &thetap) {
    float xtemp;
    float ytemp;
    float thetatemp;
    if (VL != VR) {
      float R = L / 2 * (VR + VL) / (VR - VL);
      float w = (VR - VL) / L;
      float ICCx = x - R * sin(theta);
      float ICCy = y + R * cos(theta);
      float wdt = w * dt;
      float coswdt = cos(wdt);
      float sinwdt = sin(wdt);
      xtemp = coswdt * (x - ICCx) - sinwdt * (y - ICCy) + ICCx;
      ytemp = sinwdt * (x - ICCx) + coswdt * (y - ICCy) + ICCy;
      thetatemp = theta + wdt;
      thetatemp = thetatemp - int(thetatemp / (2 * M_PI)) * 2 * M_PI;
    } else {
      xtemp = x + VL * cos(theta) * dt;
      ytemp = y + VL * sin(theta) * dt;
      thetatemp = theta;
    }
    xp = xtemp;
    yp = ytemp;
    thetap = thetatemp;
  }

  void updateEncodersCounter(float dt) {
    EncL += WL * dt * 3200;
    EncR += WR * dt * 3200;
  }

  void update(float dt) {
    T += dt;
    float VL = 2 * M_PI * rw * WL;
    float VR = 2 * M_PI * rw * WR;
    forwardKinematics(VL, VR, dt, x, y, theta, x, y, theta);
    updateEncodersCounter(dt);
    followTarget();
  }

  void followTarget() {
    float cost = cos(theta);
    float sint = sin(theta);
    float dx = cost * (xTarget - x) + sint * (yTarget - y);
    float dy = -sint * (xTarget - x) + cost * (yTarget - y);
    float VL, VR;
    VR = 100;
    if (dx != 0) {
      float R = (dx * dx - dy * dy) / (2 * dx);
      VL = VR * (R - 1) / (R + 1);
    }
    else if (dy == 0) {
      VL = VR = 0;
    }
    else if (dy < 0) {
      VL = -VR;
    }
    float TL = VL / (2 * M_PI * rw) *255.0f / MAXRPS;
    float TR = VR / (2 * M_PI * rw) *255.0f / MAXRPS;
    setThrottle(TR, TR);
  }

  void updateEstimatePosition() {
    if (T - tEst > 0.020f) {
      float DT = T - tEst;
      float VL = 2 * M_PI * rw * EncL / 3200 / DT;
      float VR = 2 * M_PI * rw * EncR / 3200 / DT;
      forwardKinematics(VL, VR, DT, xEst, yEst, thetaEst, xEst, yEst, thetaEst);
      tEst = T;
      EncL = 0;
      EncR = 0;
    }
  }

  float clamp(float v, float vmin, float vmax) {
    if (v < vmin)
      v = vmin;
    if (v > vmax)
      v = vmax;
    return v;
  }

  void setTarget(float xt, float yt) {
    xTarget = xt;
    yTarget = yt;
  }

  float x;
  float y;
  float theta;
  float L;  // Leght of the robot
  float rw; // radius wheel
  float T;  // Time
  float WR; // angular velocity right
  float WL; // angular velocity left

  float EncL; // Encoders count
  float EncR;

  float tEst; // Last estimated time
  float xEst; // Estimated position
  float yEst;
  float thetaEst;

  float xTarget;
  float yTarget;
  float dTarget;
};

#endif // GLROBOT2D_H