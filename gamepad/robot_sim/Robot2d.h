#ifndef GLROBOT2D_H
#define GLROBOT2D_H

#include <svector.h>
#include <list>
#include <tuple>

using namespace svector;

#define MAXRPS 2
#define COUNTS_PER_REV 3200

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

  void phiW(float throttleL, float throttleR, float &wl, float &wr) {
    wl = throttleL / 255.0f * MAXRPS;
    wr = throttleR / 255.0f * MAXRPS * 0.95;
  }

  void idealPhiW(float throttleL, float throttleR, float &wl, float &wr) {
    wl = throttleL / 255.0f * MAXRPS;
    wr = throttleR / 255.0f * MAXRPS;
  }

  void setThrottle(float throttleL, float throttleR) { // 0..255
    TL = throttleL;
    TR = throttleR;
    phiW(throttleL, throttleR, WL, WR);
  }

  void forwardKinematics(float wl, float wr, float dt, float x, float y,
                         float theta, float &xp, float &yp, float &thetap) {
    float xtemp;
    float ytemp;
    float thetatemp;
    float VL = 2 * M_PI * rw * wl;
    float VR = 2 * M_PI * rw * wr;
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
    EncL += WL * dt * COUNTS_PER_REV;
    EncR += WR * dt * COUNTS_PER_REV;
  }

#define sign(a) (((a) < 0) ? -1 : ((a) > 0))

  void processQueue() {
    if (!EncodersQueue.empty()) {
      auto &E = EncodersQueue.front();
      int TCL = std::get<0>(E);
      int TCR = std::get<1>(E);
      float coeffl = std::get<2>(E);
      float coeffr = std::get<3>(E);
      if (!std::get<4>(E)) {
        EncL = 0;
        EncR = 0;
        std::get<4>(E) = true;
        TL = 255 * coeffl;
        TR = 255 * coeffr;
        std::cout << "TCL = " << TCL << " TCR = " << TCR << " TL = " << TL
                  << "  TR = " << TR << "  " << coeffl << " " << coeffr
                  << std::endl;
        setThrottle(TL, TR);
      } else {
        float error = fabs(EncL / coeffl) - fabs(EncR / coeffr);
        // float adjust = error != 0 ? (error > 0 ? 1 : -1) : 0;
        float Kp = 5;
        float adjust = Kp * error;

        TL -= adjust * sign(TCL);
        TR -= adjust * sign(TCR);
        if (TL > 255) {
          TL = 255;
        }
        if (TR > 255) {
          TR = 255;
        }
        if (TL < -255) {
          TL = -255;
        }
        if (TR < -255) {
          TR = -255;
        }

        std::cout << "     ENCL = " << EncL << " ENCR = " << EncR
                  << " TCL = " << TCL << " TCR = " << TCR << " TL = " << TL
                  << "  TR = " << TR << " ERROR = " << error << std::endl;
        setThrottle(TL, TR);
        float dl = EncL - TCL;
        float dr = EncR - TCR;
        if (sqrt(dr * dr + dl * dl) < 10) {
          setThrottle(0, 0);
          EncodersQueue.pop_front();
        }
      }
    }
  }

  void update(float dt) {
    T += dt;
    forwardKinematics(WL, WR, dt, x, y, theta, x, y, theta);
    updateEstimatePosition();
    updateEncodersCounter(dt);
    processQueue();
    // followTarget();
  }

  std::list<std::tuple<int, int, float, float, bool>> EncodersQueue;

  void enqueueTuple(int tcl, int tcr) {
    float coeffl = sign(tcl);
    float coeffr = sign(tcr);
    if (fabs(tcl) >= fabs(tcr))
      coeffr = tcr / fabs(tcl);
    else
      coeffl = tcl / fabs(tcr);
    EncodersQueue.push_back(std::make_tuple(tcl, tcr, coeffl, coeffr, false));
  }

  void enqueueRotateAngle(float dtheta) {
    float tc = dtheta * L / (2 * M_PI * rw) * COUNTS_PER_REV;
    enqueueTuple(-tc, tc);
  }

  void enqueueForward(float dist) {
    float tc = dist / (2 * M_PI * rw) * COUNTS_PER_REV;
    enqueueTuple(tc, tc);
  }

  void gotoTarget(float xt, float yt) {
    setTarget(xt, yt);
    float dy = yt - yEst;
    float dx = xt - xEst;
    float alpha = atan2(dy, dx);
    float dtheta = alpha - theta;
    float dist = sqrt(dx * dx + dy * dy);
    enqueueRotateAngle(dtheta);
    enqueueForward(dist);
  }

  void followTarget() {
    float cost = cos(M_PI / 2 - theta);
    float sint = sin(M_PI / 2 - theta);
    float dx = cost * (xTarget - xEst) - sint * (yTarget - yEst);
    float dy = sint * (xTarget - xEst) + cost * (yTarget - yEst);
    float wl, wr;
    idealPhiW(255, 255, wl, wr);
    float VL = 2 * M_PI * rw * wl;
    float VR = 2 * M_PI * rw * wr;
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
      } else if (abs(dy) < 0.1) {
        VL = VR = 0;
      }
    } else {
      if (dx > 0)
        VR = -VR;
      VL = -VR;
    }
    TL = VL * 255.0f / (2 * M_PI * rw * MAXRPS);
    TR = VR * 255.0f / (2 * M_PI * rw * MAXRPS);
    setThrottle(TL, TR);
  }

  void updateEstimatePosition() {
    if (T - tEst > 0.002f) {
      float DT = T - tEst;
      float wl = EncL / 3200 / DT;
      float wr = EncR / 3200 / DT;
      forwardKinematics(wl, wr, DT, xEst, yEst, thetaEst, xEst, yEst, thetaEst);
      tEst = T;
      //  EncL = 0;
      //      EncR = 0;
      xEst = x;
      yEst = y;
      thetaEst = theta;
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
  float L;  // Diameter of the robot
  float rw; // Radius wheel
  float T;  // Time
  float WR; // Wheel angular velocity right
  float WL; // Wheel angular velocity left
  float TL; // Throttle left
  float TR; // Throttle right

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