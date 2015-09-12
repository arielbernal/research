#ifndef POINT2D_H
#define POINT2D_H

struct Point2d {
  Point2d(float x = 0, float y = 0) : x(x), y(y) {}
  Point2d(const Point2d &p) : x(p.x), y(p.y) {}
  Point2d(float k) : x(k), y(k) {};

  void set(float xv, float yv) {
    x = xv;
    y = yv;
  }
  void operator()(float X, float Y) {
    x = X;
    y = Y;
  }
  void operator()(const Point2d &p) {
    x = p.x;
    y = p.y;
  }
  void operator=(const Point2d &p) {
    x = p.x;
    y = p.y;
  }
  Point2d operator+() { return *this; }
  Point2d operator-() {
    Point2d t(-x, -y);
    return t;
  }
  Point2d &operator*=(float v) {
    x *= v;
    y *= v;
    return *this;
  }
  Point2d &operator/=(float v) {
    x /= v;
    y /= v;
    return *this;
  }
  Point2d &operator+=(const Point2d &v) {
    x += v.x;
    y += v.y;
    return *this;
  }
  Point2d &operator-=(const Point2d &v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }
  float norm() { return sqrt(x * x + y * y); }
  float x;
  float y;
};

Point2d operator+(const Point2d &v, const Point2d &w) {
  Point2d z(v);
  z += w;
  return z;
}

Point2d operator-(const Point2d &v, const Point2d &w) {
  Point2d z(v);
  z -= w;
  return z;
}

Point2d operator*(const Point2d &v, const Point2d &w) {
  Point2d z(v.x * w.x, v.y * w.y);
  return z;
}

Point2d operator*(float &v, const Point2d &w) {
  Point2d z(v * w.x, v * w.y);
  return z;
}

Point2d operator*(const Point2d &v, float &w) {
  Point2d z(v.x * w, v.y * w);
  return z;
}

Point2d operator/(float &v, const Point2d &w) {
  Point2d z(v / w.x, v / w.y);
  return z;
}

Point2d operator/(const Point2d &v, float &w) {
  Point2d z(v.x / w, v.y / w);
  return z;
}

float distance(const Point2d &p1, const Point2d &p2) {
  float dx = p2.x - p1.x;
  float dy = p2.y - p1.y;
  return sqrt(dx * dx + dy * dy);
}

float dot(const Point2d &a, const Point2d &b) { return a.x * b.x + a.y * b.y; }

struct Edge2d {
  Edge2d(float x0, float y0, float x1, float y1) : p0(x0, y0), p1(x1, y1) {}

  Edge2d(Point2d p0, Point2d p1) : p0(p0), p1(p1) {}

  Edge2d() {}

  float length() { return distance(p0, p1); }

  Point2d p0;
  Point2d p1;
};

#endif
