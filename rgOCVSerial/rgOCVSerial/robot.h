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
  void set(float cx, float cy) {
    x = cx;
    y = cy;
  }

  float x, y;
};

class Robot {
 public:
  Robot(float Radius, float SensorY, size_t ReadSize)
      : Radius(Radius),
        SensorY(SensorY),
        ReadSize(ReadSize),
        Position(0, 0),
        Angle(0) {
      Position.set(50, 50);
  }

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
      std::cout << "t = " << data[i] << " P.x = " << p.x << " p.y = " << p.y
                << std::endl;
    }
  }

  void moveTo(float x, float y, float angle) {
    Position.set(x, y);
    Angle = angle;
  }

  void randomMove() {
    Angle += rand() / float(RAND_MAX) * 10 - 5;
    float x = Position.x + rand() / float(RAND_MAX) * 2 - 1;
    float y = Position.y + rand() / float(RAND_MAX) * 2 - 1;
    Position.set(x, y);

    std::cout << "Angle = " << Angle << std::endl;
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
    glTranslatef(Position.x, Position.y, 0);
    glRotatef(Angle, 0, 0, 1);
    glColor3f(1.0f, 1.0f, 1.0f);
    glp::circle(Radius);
    glp::draw_axes(Radius, Radius);
    glColor3f(0.5f, 0.2f, 0.1f);
    glTranslatef(0, SensorY, 0);
    glp::circle(Radius / 8);
    glColor3f(2 / 255.0f, 132 / 255.0f, 130 / 255.0f);
    glBegin(GL_LINES);
    for (auto& e : Points) {
      glVertex2f(0, 0);
      glVertex2f(e.x, e.y);
    }
    glEnd();
    glColor3f(1, 1, 1);
    glPopMatrix();
  }

 private:
  float Radius;   // Robot radius
  float SensorY;  // Y Sensor distance from center
  size_t ReadSize;
  Point2D Position;
  float Angle;
  std::vector<Point2D> Points;
};

#endif  // ROBOT
