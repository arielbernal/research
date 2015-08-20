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


struct RobotEvent {
  int type;
  float time;
  float MotorLeft;
  float MotorRight;
  
  enum {STOP, LEFT, RIGHT, FORWARD};

  RobotEvent(int type, float time, float MotorLeft = 0, float MotorRight = 0) 
    : type(type), 
    time(time),
    MotorLeft(MotorLeft), 
    MotorRight(MotorRight) {}
};

class Robot {
 public:
  Robot() : x(0), y(0), theta(M_PI / 4) {
    r = 14.5 / 2.0f;
    rw = 3.4;
    MotorLeft = 0;
    MotorRight = 0;
    k0 = 55.0f / 60.0f;
    k1 = 55.0f / 60.0f;
  }

  void setPos(float posx, float posy, float angle) {
    x = posx;
    y = posy;
    theta = angle;
  }

  void setMotors(float Left, float Right) {
    MotorLeft = Left;
    MotorRight = Right;
  }
  void setMotorLeft(float Left) { MotorLeft = Left; }
  void setMotorRight(float Right) { MotorRight = Right; }

  float getX() { return x; }
  float getY() { return y; }
  float getTheta() { return theta; }

  void update(float dt) {
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
      x = cosw * (x - ICC.x) - sinw * (y - ICC.y) + ICC.x;
      y = sinw * (x - ICC.x) + cosw * (y - ICC.y) + ICC.y;
      theta = theta + dtheta;
      theta = theta - int(theta / (2 * M_PI)) * 2 * M_PI;
    } else {
      x = x + Vl * cos(theta) * dt;
      y = y + Vl * sin(theta) * dt;
    }
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

  void render() {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(theta / M_PI * 180 - 90, 0, 0, 1);

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
  Point2d posFront() { return Point2d(x + r * cos(theta), y + r * sin(theta)); }

  void followPath() {
   /*     float dx = p.x - x;
        float dy = p.y - y;
        float alpha = atan2(dy, dx);
        alpha = alpha - int(alpha / (2 * M_PI)) * 2 * M_PI;
        float dalpha = theta - alpha;
        std::cout << DEG(theta) << " " << DEG(alpha) << " " << DEG(dalpha)
                  << std::endl;
        if (fabs(dalpha) > M_PI / 20) {
          if (dalpha < 0) {
            tEvent = t + 0.8f;
            rotateLeft();
          } else {
            tEvent = t + 0.8f;
            rotateRight();
          }
        }
      }
    }*/
  }


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