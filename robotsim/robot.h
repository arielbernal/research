#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <glheaders.h>
#include <cmath>
#include <glprimitives.h>
#include <vector>
#include "point2d.h"

class Robot {
 public:
  Robot() : x(0), y(0), theta(0), t(0) {
    r = 10;
    rw = 3;
    dt = 0.033f;
    Motors[0] = 0;
    Motors[1] = 0;
    k0 = 55.0f / 60.0f;
    k1 = 55.0f / 60.0f;
  }

  void setPos(float posx, float posy, float angle) {
    x = posx;
    y = posy;
    theta = angle;
  }

  void setMotors(float Left, float Right) {
    Motors[0] = Left;
    Motors[1] = Right;
  }

  void setMotorLeft(float Left) { Motors[0] = Left; }

  void setMotorRight(float Right) { Motors[1] = Right; }

  float getX() { return x; }
  float getY() { return y; }
  float gettheta() { return theta; }

  void renderFrontPath() {
    theta = M_PI/2.0f;
    float dt = 8.0f;
    float xp = x;
    float yp = y;
    float thetap = theta;
    for (int Ml = -100; Ml <= 100; ++Ml) {
      for (int Mr = -100; Mr <= 100; ++Mr) {
        float Vl = Ml / 100.0f * k0 * 2 * M_PI * rw;
        float Vr = Mr / 100.0f * k1 * 2 * M_PI * rw;
        float d = 2 * r;
        float w = 0;
        float R = 0;
        if (Vl != Vr) {
          w = (Vr - Vl) / d;
          R = r * (Vr + Vl) / (Vr - Vl);
          Point2d ICC(x - R * sin(theta), y + R * cos(theta));
          //std::cout << " R = " << R  << " w = " << w << " ICC= "<< ICC.x << ", " << ICC.y << std::endl;
          float dtheta = w * dt;
          float cosw = cos(w * dt);
          float sinw = sin(w * dt);
          xp = cosw * (x - ICC.x) - sinw * (y - ICC.y) + ICC.x;
          yp = sinw * (x - ICC.x) + cosw * (y - ICC.y) + ICC.y;
          thetap = theta + dtheta;
        } else {
          xp += Vl * cos(theta) * dt;
          yp += Vl * sin(theta) * dt;
        }
        //std::cout << "xp = " << xp << " yp = " << yp << " Vl = " << Vl
        //          << " Vr = " << Vr << " Theta = " << thetap  * 180 / M_PI<< std::endl;
        glLineWidth(2);
        glPointSize(1);

        glPushMatrix();
        glTranslatef(x, y, 0);
        glRotatef(-90+theta / M_PI * 180, 0, 0, 1);
        //glColor3f(1, 1, 1);
        //glBegin(GL_LINES);
        //glVertex2f(-10, 0);
        //glVertex2f(10, 0);
        //glVertex2f(0, 10);
        //glVertex2f(0, 0);
        //glEnd();

        
        glBegin(GL_POINTS);
          glColor3f(0, 1, 0);  glVertex2f(0, 0);
//          glColor3f(1, 0, 0);  glVertex2f(-10, 0);
//          glColor3f(1, 1, 0);  glVertex2f(10, 0);
        glEnd();

        glPopMatrix();

        glPushMatrix();
        glTranslatef(xp, yp, 0);
        glRotatef(-90+thetap / M_PI * 180, 0, 0, 1);
        //glColor3f(1, 1, 1);
        //glBegin(GL_LINES);
        //  glVertex2f(-10, 0);
        //  glVertex2f(10, 0);
        //  glVertex2f(0, 10);
        //  glVertex2f(0, 0);
        //glEnd();

        glBegin(GL_POINTS);
          glColor3f(1, 1, 1);  glVertex2f(0, 0);
//          glColor3f(1, 0, 0);  glVertex2f(-10, 0);
//          glColor3f(1, 1, 0);  glVertex2f(10, 0);
        glEnd();
        glPopMatrix();
      }
    }
  }

  void update() {
    t += dt;
    if (tEvent > 0 && t >= tEvent) {
      Motors[0] = MotorsEnd[0];
      Motors[1] = MotorsEnd[1];
      tEvent = 0;
    }

    float v0 = Motors[0] / 100.0f * k0 * 2 * M_PI * rw;  // speed motor left
    float v1 = Motors[1] / 100.0f * k1 * 2 * M_PI * rw;  // speed motor right
    float ar = theta / 180.0f * M_PI;
    float rx0 = x + r * cos(ar);
    float ry0 = y + r * sin(ar);

    float da0 = -v0 / (2 * M_PI * r) * dt;
    ar += da0;
    float lx1 = rx0 - 2 * r * cos(ar);
    float ly1 = ry0 - 2 * r * sin(ar);

    float da1 = v1 / (2 * M_PI * r) * dt;
    ar += da1;
    float rx1 = lx1 + 2 * r * cos(ar);
    float ry1 = ly1 + 2 * r * sin(ar);

    x = (rx1 + lx1) / 2;
    y = (ry1 + ly1) / 2;
    theta = atan2(ry1 - ly1, rx1 - lx1) * 180 / M_PI;
  }

  void rotateLeft(float delay) {
    tEvent = t + delay;
    Motors[0] = -100;
    Motors[1] = 100;
    MotorsEnd[0] = 0;
    MotorsEnd[1] = 0;
  }

  void rotateRight(float delay) {
    tEvent = t + delay;
    Motors[0] = 100;
    Motors[1] = -100;
    MotorsEnd[0] = 0;
    MotorsEnd[1] = 0;
  }

  void stimate(float m0, float m1, float dt, float &xe, float &ye,
               float &thetae) {
    float v0 = m0 / 100.0f * k0 * 2 * M_PI * rw;  // speed motor left
    float v1 = m1 / 100.0f * k1 * 2 * M_PI * rw;  // speed motor right
    float ar = theta / 180.0f * M_PI;
    float rx0 = x + r * cos(ar);
    float ry0 = y + r * sin(ar);

    float da0 = -v0 / (2 * M_PI * r) * dt;
    ar += da0;
    float lx1 = rx0 - 2 * r * cos(ar);
    float ly1 = ry0 - 2 * r * sin(ar);

    float da1 = v1 / (2 * M_PI * r) * dt;
    ar += da1;
    float rx1 = lx1 + 2 * r * cos(ar);
    float ry1 = ly1 + 2 * r * sin(ar);

    xe = (rx1 + lx1) / 2;
    ye = (ry1 + ly1) / 2;
    thetae = atan2(ry1 - ly1, rx1 - lx1) * 180 / M_PI;
  }

  void render() {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(theta, 0, 0, 1);

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

    // glColor4f(1, 0, 0, 0.3);
    // drawArrow(0, 0, 0, 0, arrowLength, 0, 0.5);

    glPopMatrix();

    Point2d p = posFront();
    glColor3f(1, 0, 0);
    drawDisk(p.x, p.y, 2, 40);
  }

  Point2d pos() { return Point2d(x, y); }
  Point2d posFront() {
    return Point2d(x + r * cos(theta / 180.0f * M_PI + M_PI / 2),
                   y + r * sin(theta / 180.0f * M_PI + M_PI / 2));
  }

  void saveStatus() {
    x0 = x;
    y0 = y;
    theta0 = theta;
    Motors0[0] = Motors[0];
    Motors0[1] = Motors[1];
    t0 = t;
  }

  void restoreStatus() {
    x = x0;
    y = y0;
    theta = theta0;
    Motors[0] = Motors0[0];
    Motors[1] = Motors0[1];
    t = t0;
  }

 private:
  float x, y, theta;
  float r;   // wheel to center distance
  float rw;  // wheel radius
  float t;   // time
  float dt;
  float k0;  // max angular speed motor0 (Left)
  float k1;  // max angular speed motor1 (Right)
  float Motors[2];

  float x0, y0, theta0;
  float Motors0[2];
  float t0;

  float MotorsEnd[2];
  float tEvent;
};

#endif