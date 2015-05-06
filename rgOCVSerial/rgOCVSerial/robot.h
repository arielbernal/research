#ifndef ROBOT
#define ROBOT

#include <GL/glew.h>
#include <vector>
#include <glprimitivies.h>
#include <stdint.h>
#include <iostream>

#define M_PI 3.14159265358

struct Point2D {
  Point2D(float x, float y) : x(x), y(y) {}
  float x, y;
};

class Robot {
 public:
  Robot(float Radius, float SensorY, size_t ReadSize)
      : Radius(Radius), SensorY(SensorY), ReadSize(ReadSize) {}

  Point2D polarToCartesian(float angle, float d) {
    float angleR = angle * M_PI / 180.0f;
    Point2D p(d * cos(angleR), d * sin(angleR));
    return p;
  }

  float usTocm(float time) { return time / 58 + 2.5; }

  void appendData(uint16_t* data) {
    for (size_t i = 0; i < ReadSize; ++i) {
      Points.push_back(polarToCartesian(i, usTocm(data[i])));
      Point2D p = polarToCartesian(i, usTocm(data[i]));
      std::cout << "t = " << data[i] <<  " P.x = " << p.x << " p.y = " << p.y << std::endl;
    }

  }

  void set2DMode() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }

  void render() {
    set2DMode();
    glPushMatrix();
    glTranslatef(50, Radius, 0);
    glColor3f(0.5, 0.5, 0.5);
    glp::circle(Radius);
    glp::draw_axes(Radius, Radius);
    glColor3f(0.5f, 0.2f, 0.1f);
    glTranslatef(0, SensorY, 0);
    glp::circle(Radius / 8);
    glColor3f(2/255.0f,132/255.0f,130/255.0f);
    glBegin(GL_LINES);
    for (auto& e : Points) {
      glVertex2f(0, 0);
      glVertex2f(e.x, e.y);
    }
    glEnd();
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(-7,0);
    glVertex2f(-7,12);
    glVertex2f(-7,12);
    glVertex2f(23,12);
    glVertex2f(23,12);
    glVertex2f(23,0);

    glEnd();

    glPopMatrix();
  }

 private:
  float Radius;   // Robot radius
  float SensorY;  // Y Sensor distance from center
  size_t ReadSize;
  std::vector<Point2D> Points;
};

#endif  // ROBOT
