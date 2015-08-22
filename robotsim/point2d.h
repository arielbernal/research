#ifndef POINT2D_H
#define POINT2D_H




struct Point2d {
  Point2d(float x = 0, float y = 0) : x(x), y(y) {}
  void set(float xv, float yv) {
    x = xv;
    y = yv;
  }
  float x;
  float y;
};

float distance(const Point2d &p1, const Point2d &p2) {
  float dx = p2.x - p1.x;
  float dy = p2.y - p1.y;
  return sqrt(dx * dx + dy * dy);
}

struct Edge2d {
  Edge2d(float x0, float y0, float x1, float y1) : p0(x0, y0), p1(x1, y1) {}
  
  Edge2d(Point2d p0, Point2d p1) : p0(p0), p1(p1) {}

  float length() {
    return distance(p0, p1);
  }

  Point2d p0;
  Point2d p1;
};


#endif
