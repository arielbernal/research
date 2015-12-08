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
    updateEstimatePosition();
    updateEncodersCounter(dt);
    followTarget();
  }

  void followTarget() {
    float cost = cos(M_PI / 2 - theta);
    float sint = sin(M_PI / 2 - theta);
    float dx = cost * (xTarget - x) - sint * (yTarget - y);
    float dy = sint * (xTarget - x) + cost * (yTarget - y);
     // std::cout << "theta = " << theta / M_PI * 180 << "  Dx = " << dx
     //           << "  Dy = " << dy << std::endl;
    float VL, VR;
    VR = 2 * M_PI * rw * 255 / 255.0f * MAXRPS;
    VL = 2 * M_PI * rw * 255 / 255.0f * MAXRPS;
    if (dy > 0) {
      if (fabs(dx) > 0.01) {
        float R = -(dx * dx + dy * dy) / (2 * dx);
        ICCR = R;
        ICCx = x - R * sin(theta);
        ICCy = y + R * cos(theta);
        if (R > 0)
          VL = VR * (R - L / 2) / (R + L / 2);
        else
          VR = VL * (R + L / 2) / (R - L / 2);
        // float R1 = L / 2 * (VR + VL) / (VR - VL);
        // float ICCx1 = x + R1 * sin(theta);
        // float ICCy1 = y - R1 * cos(theta);
        //  std::cout << "   x = " << x << "  y = " << y << " VL = " << VL
        //            << "  VR = " << VR << std::endl;
        //  std::cout << "       R = " << R << " ICCx = " << ICCx
        //            << "  ICCy = " << ICCy << std::endl;
        // // std::cout << "       R1 = " << R1 << " ICCx1 = " << ICCx1
        //           << "  ICCy1 = " << ICCy1 << std::endl;
      } else if (abs(dy) < 0.1) {
        VL = VR = 0;
      }
    } else {
      if (dx > 0)
        VR = -VR;
      VL = -VR;
    }
    float TL = VL * 255.0f / (2 * M_PI * rw * MAXRPS);
    float TR = VR * 255.0f / (2 * M_PI * rw * MAXRPS);
    setThrottle(TL, TR);
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

  float ICCx;
  float ICCy;
  float ICCR;
};

#endif // GLROBOT2D_H