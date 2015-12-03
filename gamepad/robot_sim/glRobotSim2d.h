#ifndef GLROBOTSIM2D_H
#define GLROBOTSIM2D_H

#include <svector.h>
#include "../include/glprimitives.h"
#include "../include/gl2dmodel.h"

using namespace svector;

class Robot2D {
public:
  Robot2D(float L, float rw, float x0, float y0, float theta)
      : L(L), rw(rw), T(0), x(x0), y(y0), theta(theta), xEst(0), yEst(0),
        tEst(0), thetaEst(theta) {}

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
      xtemp = x - VL * sin(theta) * dt;
      ytemp = y + VL * cos(theta) * dt;
      thetatemp = theta;
    }
    xp = xtemp;
    yp = ytemp;
    thetap = thetatemp;
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

  void updateEncodersCounter(float dt) {
    EncL += WL * dt * 3200;
    EncR += WR * dt * 3200;    
  }

  void update(float dt) {
    T += dt;
    float VL = 2 * M_PI * rw * WL;
    float VR = 2 * M_PI * rw * WR;
    forwardKinematics(VL, VR, dt,x, y, theta, x, y, theta);
    updateEncodersCounter(dt);
    updateEstimatePosition();
    updatePIDLoop();
  }

  void updatePIDLoop() {
    if (xTarget != x || yTarget != y) {
      float Errx = x - xTarget;
      float Erry = y - yTarget;
      float d = sqrt(Errx * Errx + Erry * Erry);
      if (dTarget >= d) {

      }

    }
  }

  void setTarget(float xt, float yt) {
    xTarget = xt;
    yTarget = yt;
    float Errx = x - xTarget;
    float Erry = y - yTarget;
    dTarget = sqrt(Errx * Errx + Erry * Erry);
    setThrottle(100, 100);
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

class GLRobotSim2D : public GL2DModel {
public:
  GLRobotSim2D(Robot2D &robot, float ViewWidth = 100, int WinWidth = 1200,
               int WinHeight = 1000)
      : GL2DModel(ViewWidth, WinWidth, WinHeight), robot(robot) {}

  void render() {
    glScalef(1, -1, 1);

    float r = robot.L / 2;
    float rw = robot.rw;
    float arrowLength = r + 5;
    float dw2 = 0.4;

    glPushMatrix();
    glTranslatef(robot.x, robot.y, 0);
    glRotatef(robot.theta / M_PI * 180 - 90, 0, 0, 1);

    glColor3f(1, 1, 1);
    drawCircle(0, 0, r, 30);

    glColor3f(1, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-r - dw2, rw);
    glVertex2f(-r - dw2, -rw);
    glVertex2f(-r + dw2, -rw);
    glVertex2f(-r + dw2, rw);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(r - dw2, rw);
    glVertex2f(r - dw2, -rw);
    glVertex2f(r + dw2, -rw);
    glVertex2f(r + dw2, rw);
    glEnd();

    glTranslatef(0, r, 0);
    glColor3f(0, 1, 0);
    drawDisk(0, 0, r / 10, 30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(robot.xEst, robot.yEst, 0);
    glRotatef(robot.thetaEst / M_PI * 180 - 90, 0, 0, 1);

    glColor3f(0.5, 0.5, 0.5);
    drawCircle(0, 0, r, 30);

    glColor3f(0.5, 0.5, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-r - dw2, rw);
    glVertex2f(-r - dw2, -rw);
    glVertex2f(-r + dw2, -rw);
    glVertex2f(-r + dw2, rw);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(r - dw2, rw);
    glVertex2f(r - dw2, -rw);
    glVertex2f(r + dw2, -rw);
    glVertex2f(r + dw2, rw);
    glEnd();

    glTranslatef(0, r, 0);
    glColor3f(0, 0.5, 0);
    drawDisk(0, 0, r / 10, 30);
    glPopMatrix();
  }

private:
  Robot2D &robot;
};

#endif // GLROBOTSIM2D_H