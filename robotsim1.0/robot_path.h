#ifndef ROBOT_PATH_H
#define ROBOT_PATH_H

#include <iostream>
#include <glheaders.h>
#include <cmath>
#include <glprimitives.h>
#include <vector>
#include "point2d.h"


struct Path {
  std::vector<Point2d> path;
  Path() : iNode(0) {
    path.push_back(Point2d(0, 20));
    path.push_back(Point2d(0, 100));
    path.push_back(Point2d(100, 100));
  }

  void render() {
    glColor3f(0, 1, 0);
    for (size_t i = 0; i < path.size(); ++i) {
      drawDisk(path[i].x, path[i].y, 1, 20);
    }
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    for (size_t i = 0; i < path.size() - 1; ++i) {
      glVertex2f(path[i].x, path[i].y);
      glVertex2f(path[i + 1].x, path[i + 1].y);
    }
    glEnd();
  }

  bool isLast() {
    return (path.size() == iNode);
  }

  Point2d getNode() {
    return path[iNode];
  }

  void nextNode() {
    iNode++;
  }

  int iNode;
};

class PathR {
 public:
  PathR() {
    cpath.push_back(Point2d(0, 20));
    cpath.push_back(Point2d(0, 40));
    cpath.push_back(Point2d(40, 40));
    cpath.push_back(Point2d(40, 80));
    float dk = 5;
    for (size_t i = 0; i < cpath.size() - 1; ++i) {
      float x0 = cpath[i].x;
      float x1 = cpath[i + 1].x;
      float y0 = cpath[i].y;
      float y1 = cpath[i + 1].y;
      float dx = x1 - x0;
      float dy = y1 - y0;
      float nv = sqrt(dx * dx + dy * dy);
      size_t kmax = nv / dk;
      dx /= nv;
      dy /= nv;
      for (size_t k = 0; k < kmax; ++k) {
        Point2d p(x0 + k * dk * dx, y0 + k * dk * dy);
        path.push_back(p);
      }
    }
    iSelected = 0;
  }

  float distToSegment(const Point2d &p, const Point2d &a, const Point2d &b) {
    float l = distance(a, b);
    if (l == 0) return distance(p, a);
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float t = ((p.x - a.x) * dx + (p.y - a.y) * dy) / (l * l);
    if (t < 0) return distance(p, a);
    if (t > 1) return distance(p, b);
    Point2d xp(a.x + t * dx, a.y + t * dy);
    return distance(p, xp);
  }

  Point2d pointToSegment(const Point2d &p, const Point2d &a, const Point2d &b) {
    float l = distance(a, b);
    if (l == 0) return a;
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float t = ((p.x - a.x) * dx + (p.y - a.y) * dy) / (l * l);
    if (t < 0) return a;
    if (t > 1) return b;
    Point2d xp(a.x + t * dx, a.y + t * dy);
    return xp;
  }

  Point2d minDistPointSegment(const Point2d &p) {
    float dmin = 10E20;
    Point2d pmin;
    for (size_t i = 0; i < path.size() - 1; ++i) {
      Point2d xp = pointToSegment(p, path[i], path[i + 1]);
      float d = distance(p, xp);
      if (d < dmin) {
        dmin = d;
        pmin = xp;
      }
    }
    return pmin;
  }

  float selectMinPointDistance(const Point2d &p) {
    float dmin = 10E20;
    size_t iSelected = 0;
    for (size_t i = 0; i < path.size(); ++i) {
      float d = distance(p, path[i]);
      if (d < dmin) {
        dmin = d;
        iSelected = i;
      }
    }
    return dmin;
  }

  void render() {
    glColor3f(0.8, 0.8, 0.8);
    glLineWidth(2);
    glBegin(GL_LINES);
    for (size_t i = 0; i < path.size() - 1; ++i) {
      Point2d p0 = path[i];
      Point2d p1 = path[i + 1];

      glVertex2f(p0.x, p0.y);
      glVertex2f(p1.x, p1.y);
    }
    glEnd();
    glLineWidth(1.5);

    for (size_t i = 0; i < path.size(); ++i) {
      if (i == iSelected) {
        glColor3f(0, 1, 0);
        drawDisk(path[i].x, path[i].y, 1, 10);
      } else {
        glColor3f(1, 1, 0);
        drawCircle(path[i].x, path[i].y, 1, 10);
      }
    }
  }

  Point2d getSelected() { return path[iSelected]; }

 private:
  std::vector<Point2d> cpath;
  std::vector<Point2d> path;
  size_t iSelected;
};
#endif