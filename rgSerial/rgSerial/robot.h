#ifndef ROBOT
#define ROBOT

#include <GL/glew.h>
#include <vector>
#include <glprimitivies.h>

struct Point2D {
  Point2D(float x, float y) : x(x), y(y) {}
  float x, y;
};

class UltraSonicSensor {
 public:
  UltraSonicSensor(size_t ReadSize) : ReadSize(ReadSize) {}

  Point2D polarToCartesian(float angle, float d) {
    Point2D p(0, 0);
    return p;
  }

  void appendData(float* data) {
    for (size_t i = 0; i < ReadSize; ++i)
      Points.push_back(polarToCartesian(i, data[i]));
  }

 private:
  size_t ReadSize;
  std::vector<Point2D> Points;
};

class Robot {
 public:
  Robot(float Radius, float SensorY, size_t ReadSize)
      : Radius(Radius), SensorY(SensorY), Sensor(ReadSize) {}

  void appendData(float* data) { Sensor.appendData(data); }

  UltraSonicSensor* getSensor() { return &Sensor; }

  void set2DMode() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 150, 0, 150);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }

  void render() {
    set2DMode();
    glPushMatrix();
    glTranslatef(75, Radius, 0);
    glColor3f(0.5, 0.5, 0.5);
    glp::circle(Radius);
    glp::draw_axes(Radius, Radius);
    glColor3f(0.5, 0.2, 0.1);
    glTranslatef(0, SensorY, 0);
    glp::circle(Radius / 5);
    glPopMatrix();
  }

 private:
  float Radius;   // Robot radius
  float SensorY;  // Y Sensor distance from center
  UltraSonicSensor Sensor;
};

#endif  // ROBOT
