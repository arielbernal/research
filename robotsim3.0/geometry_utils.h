#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

bool SegmentCircleIntersection(const Edge2d& E, const Point2d& C, float r) {
    Point2d A = E.p0;
    Point2d B = E.p1;
    Point2d V = B - A;
    Point2d P = C - A;
    float Vnorm = V.norm();
    float projv = dot(V, P) / Vnorm;
    if (projv < 0) return (P.norm() <= r);
    if (projv > Vnorm) return (distance(C, B) <= r);
    Point2d Proj = projv * V / Vnorm;
    return (distance(C, A + Proj) <= r);
  }

  bool LineEdgeIntersection(const Edge2d& E, const Edge2d& L, Point2d& I) {
    Point2d v = L.p1 - L.p0;
    Point2d u = E.p1 - E.p0;
    Point2d vp(-v.y, v.x);
    float t = dot(L.p0 - E.p0, vp);
    float denom = dot(u, vp);

    if (denom == 0) return false;
    t /= denom;
    if (t < 0 || t > 1) return false;
    I = E.p0 + t * u;
    return true;
  }

  bool RayEdgeIntersection(const Edge2d& E, const Edge2d& L, Point2d& I) {
    Point2d v = L.p1 - L.p0;  // we assume v
    Point2d u = E.p1 - E.p0;
    Point2d vp(-v.y, v.x);
    Point2d s = L.p0 - E.p0;
    float t2 = dot(s, vp);
    float denom = dot(u, vp);

    if (denom == 0) return false;
    t2 /= denom;
    if (t2 < 0 || t2 > 1) return false;

    float t1 = (s.y * u.x - s.x * u.y) / denom;
    if (t1 < 0) return false;

    I = E.p0 + t2 * u;
    return true;
  }


#endif