#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <glheaders.h>
#include <cmath>
#include <glprimitives.h>
#include <vector>
#include "point2d.h"

#define DEG(X) X / M_PI * 180.0
#define RAD(X) X / 180.0 * M_PI

class Robot {
 public:
  Robot(float theta = M_PI / 2, float x = 0, float y = 0)
      : x(x), y(y), theta(theta) {
    r = 14.5 / 2.0f;
    rw = 3.4;
    MotorLeft = 0;
    MotorRight = 0;
    k0 = 55.0f / 60.0f;
    k1 = 55.0f / 60.0f;
  }

  void setPos(float posx, float posy) {
    x = posx;
    y = posy;
  }

  void setPos(const Point2d& p) {
    x = p.x;
    y = p.y;
  }

  void setPos(const Point2d& p, float angle) {
    x = p.x;
    y = p.y;
    theta = angle;
  }

  void setAngle(float angle) { theta = angle; }

  void setMotors(float Left, float Right) {
    setMotorLeft(Left);
    setMotorRight(Right);
  }

  void setMotorLeft(float Left) {
    if (Left > 100)
      Left = 100;
    else if (Left < -100)
      Left = -100;
    MotorLeft = Left;
  }

  void setMotorRight(float Right) {
    if (Right > 100)
      Right = 100;
    else if (Right < -100)
      Right = -100;
    MotorRight = Right;
  }

  float getX() const { return x; }
  float getY() const { return y; }
  float getAngle() { return theta; }
  float getMotorLeft() { return MotorLeft; }
  float getMotorRight() { return MotorRight; }
  float getR() { return r; }

  void simulate(float dt, float& xp, float& yp, float& thetap) {
    float Vl = MotorLeft / 100.0f * k0 * 2 * M_PI * rw;
    float Vr = MotorRight / 100.0f * k1 * 2 * M_PI * rw;
    float d = 2 * r;
    float w = 0;
    float R = 0;
    if (Vl != Vr) {
      w = (Vr - Vl) / d;
      R = r * (Vr + Vl) / (Vr - Vl);
      Point2d ICC(x - R * sin(theta), y + R * cos(theta));
      float dtheta = w * dt;
      float cosw = cos(dtheta);
      float sinw = sin(dtheta);
      xp = cosw * (x - ICC.x) - sinw * (y - ICC.y) + ICC.x;
      yp = sinw * (x - ICC.x) + cosw * (y - ICC.y) + ICC.y;
      thetap = theta + dtheta;
      thetap = thetap - int(thetap / (2 * M_PI)) * 2 * M_PI;
    }
    else {
      xp = x + Vl * cos(theta) * dt;
      yp = y + Vl * sin(theta) * dt;
      thetap = theta;
    }
  }


  void relativeMove(float dt, float& dx, float& dy, float& dtheta) {
    float Vl = MotorLeft / 100.0f * k0 * 2 * M_PI * rw;
    float Vr = MotorRight / 100.0f * k1 * 2 * M_PI * rw;
    float d = 2 * r;
    float w = 0;
    float R = 0;
    if (Vl != Vr) {
      w = (Vr - Vl) / d;
      R = r * (Vr + Vl) / (Vr - Vl);
      Point2d ICC(-R * sin(theta), R * cos(theta));
      dtheta = w * dt;
      float cosw = cos(dtheta);
      float sinw = sin(dtheta);
      dx = -cosw * ICC.x + sinw * ICC.y + ICC.x;
      dy = -sinw * ICC.x - cosw * ICC.y + ICC.y;
      dtheta = dtheta - int(dtheta / (2 * M_PI)) * 2 * M_PI;
    }
    else {
      dx = Vl * cos(theta) * dt;
      dy = Vl * sin(theta) * dt;
      dtheta = 0;
    }
  }


  void update(float dt) {
    simulate(dt, x, y, theta);
  }

  void rotateLeft() {
    MotorLeft = -100;
    MotorRight = 100;
  }

  void rotateRight() {
    MotorLeft = 100;
    MotorRight = -100;
  }

  void moveForward() {
    MotorLeft = 100;
    MotorRight = 100;
  }

  void stop() {
    MotorLeft = 0;
    MotorRight = 0;
  }

  void render(float cr = 1, float cg = 1, float cb = 1, bool glow = false) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(theta / M_PI * 180 - 90, 0, 0, 1);

    float arrowLength = r + 5;
    float dw2 = 0.4;

    glColor3f(cr, cg, cb);
    if (glow) {
      glLineWidth(4);
    }
    drawCircle(0, 0, r, 30);
    if (glow) glLineWidth(1.5);

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

    glPopMatrix();

    Point2d p = posFront();
    glColor3f(0, 1, 0);
    drawDisk(p.x, p.y, 1, 20);
  }

  Point2d getPos() { return Point2d(x, y); }
  Point2d posFront() { return Point2d(x + r * cos(theta), y + r * sin(theta)); }

 private:
  float x, y, theta;
  float r;   // wheel to center distance
  float rw;  // wheel radius
  float k0;  // max angular speed motor0 (Left)
  float k1;  // max angular speed motor1 (Right)
  float MotorLeft;
  float MotorRight;
};

#endif