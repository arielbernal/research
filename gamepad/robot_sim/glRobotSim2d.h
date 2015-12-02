#ifndef GLROBOTSIM2D_H
#define GLROBOTSIM2D_H

#include <svector.h>
#include "../include/glprimitives.h"
#include "../include/gl2dmodel.h"

using namespace svector;

class Robot2D {
public:
  Robot2D(float L, float rw, float x0, float y0, float theta)
      : L(L), rw(rw), T(0), x(x0), y(y0), theta(theta), xEst(0), yEst(0), tEst(0) {}

  void setPos(float xp, float yp, float thetap) {
    x = xp;
    y = yp;
    theta = thetap;
  }

#define MAXRPS 2

  void setV(float throttleL, float throttleR) { // 0..255
    WL = throttleL / 255.0f * MAXRPS;
    WR = throttleR / 255.0f * MAXRPS;
  }

  void update(float dt) {
    T += dt;
    float VL = 2 * M_PI * rw * WL;
    float VR = 2 * M_PI * rw * WR;
    EncL += WL * dt * 3200;
    EncR += WR * dt * 3200;
    
    if (T - tEst > 0.010f) {
      float DT = T - tEst;
      tEst = T;

    }
    float xp;
    float yp;
    float thetap;
    if (VL != VR) {
      float R = L / 2 * (VR + VL) / (VR - VL);
      float w = (VR - VL) / L;
      float ICCx = x - R * sin(theta);
      float ICCy = y + R * cos(theta);
      float wt = w * dt;
      float coswt = cos(wt);
      float sinwt = sin(wt);
      xp = coswt * (x - ICCx) - sinwt * (y - ICCy) + ICCx;
      yp = sinwt * (x - ICCx) + coswt * (y - ICCy) + ICCy;
      thetap = theta + wt;
      thetap = thetap - int(thetap / (2 * M_PI)) * 2 * M_PI;
    } else {
      xp = x - VL * sin(theta) * dt;
      yp = y + VL * cos(theta) * dt;
      thetap = theta;
      thetap = thetap - int(thetap / (2 * M_PI)) * 2 * M_PI;
    }
    x = xp;
    y = yp;
    theta = thetap;
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
};

class GLRobotSim2D : public GL2DModel {
public:
  GLRobotSim2D(Robot2D &robot, float ViewWidth = 100, int WinWidth = 1200,
               int WinHeight = 1000)
      : GL2DModel(ViewWidth, WinWidth, WinHeight), robot(robot) {}

  void render() {
    glPushMatrix();
    glScalef(1, -1, 1);
    glTranslatef(robot.x, robot.y, 0);
    glRotatef(robot.theta / M_PI * 180 - 90, 0, 0, 1);
    float r = robot.L / 2;
    float rw = robot.rw;

    float arrowLength = r + 5;
    float dw2 = 0.4;

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
  }

private:
  Robot2D &robot;
};

#endif // GLROBOTSIM2D_H