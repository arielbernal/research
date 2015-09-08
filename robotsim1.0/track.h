#ifndef TRACK_H
#define TRACK_H

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include "maze.h"
#include "point2d.h"

class Track {
 public:
  Track() {}

  void render() {
    glColor3f(0, 0.4, 0.7);
    glBegin(GL_LINES);
    for (auto& e : edges) {
      glVertex2f(e.p0.x, e.p0.y);
      glVertex2f(e.p1.x, e.p1.y);
    }
    glEnd();
    glColor3f(0.3, 0.3, 0.3);

    size_t NL = landmarks.size();
    for (size_t i = 0; i < NL; ++i) {
      glColor3f(0.3, 0.3, 0.4);
      if (i == 0) glColor3f(0.1, 0.3, 0.1);
      if (i == NL - 1) glColor3f(0.3, 0.1, 0.1);
      auto& e = landmarks[i];
      drawDisk(e.x, e.y, 1, 20);
    }
  }

  void getEdgesFromMaze(const Maze& Mz, float d) {
    edges.clear();
    Cell* Grid = Mz.getGrid();
    unsigned N = Mz.getWidth();
    unsigned M = Mz.getHeight();
    for (unsigned i = 0; i < M; ++i) {
      for (unsigned j = 0; j < N; ++j) {
        unsigned Cell = Grid[i * N + j].v;
        float x = j * d - N * d / 2;
        float y = (M - i) * d - N * d / 2;
        if (Cell & WN) edges.push_back(Edge2d(x, y, x + d, y));
        if (Cell & WE) edges.push_back(Edge2d(x + d, y, x + d, y - d));
        if (Cell & WS) edges.push_back(Edge2d(x, y - d, x + d, y - d));
        if (Cell & WW) edges.push_back(Edge2d(x, y, x, y - d));
        if (Cell & BN) edges.push_back(Edge2d(x, y, x + d, y));
        if (Cell & BE) edges.push_back(Edge2d(x + d, y, x + d, y - d));
        if (Cell & BS) edges.push_back(Edge2d(x, y - d, x + d, y - d));
        if (Cell & BW) edges.push_back(Edge2d(x, y, x, y - d));
      }
    }
    Cell* b = Mz.getBegin();
    Begin = Point2d(b->j * d - N * d / 2 + d / 2,
                    (N - b->i) * d - N * d / 2 - d / 2);
  }

  void addEdge(float x0, float y0, float x1, float y1) {
    edges.push_back(Edge2d(x0, y0, x1, y1));
  }

  void addEdge(const Edge2d& e) { edges.push_back(e); }

  void addLandmark(float x, float y) { landmarks.push_back(Point2d(x, y)); }
  void addLandmark(const Point2d& p) { landmarks.push_back(p); }

  void makePolygon(float xc, float yc, float r, float nedges) {
    float dalpha = 2 * M_PI / nedges;
    for (size_t i = 0; i < nedges; ++i) {
      float x0 = xc + r * cos(dalpha * i);
      float y0 = yc + r * sin(dalpha * i);
      float x1 = xc + r * cos(dalpha * (i + 1));
      float y1 = yc + r * sin(dalpha * (i + 1));
      edges.push_back(Edge2d(x0, y0, x1, y1));
    }
  }

  const std::vector<Edge2d>& getEdges() const { return edges; }
  const std::vector<Point2d>& getLandmarks() const { return landmarks; }
  const std::vector<float>& getDk() const { return Dk; }
  Point2d getInitialPoint() { return landmarks[0]; }

  void makePoygonLandmarks(float xc, float yc, float r, float nedges,
                           float alpha = 0, float dalpha = 0) {
    if (dalpha == 0) dalpha = 2 * M_PI / nedges;
    for (size_t i = 0; i < nedges; ++i) {
      float x = xc + r * cos(alpha + dalpha * i);
      float y = yc + r * sin(alpha + dalpha * i);
      landmarks.push_back(Point2d(x, y));
    }
    updateMarkDistances();
  }

  void updateMarkDistances() {
    Dk.resize(landmarks.size());
    float d = 0;
    size_t N = landmarks.size();
    Dk[N - 1] = 0;
    for (int i = N - 2; i >= 0; --i) {
      d += distance(landmarks[i + 1], landmarks[i]);
      Dk[i] = d;
    }
  }

  void save(const std::string& Filename) {
    std::ofstream ofs(Filename.c_str());
    if (!ofs.is_open()) {
      std::cout << "Error saving to file : " << Filename << std::endl;
      return;
    }

    ofs << edges.size() << " " << landmarks.size() << "\n";
    for (auto& e : edges)
      ofs << e.p0.x << " " << e.p0.y << " " << e.p1.x << " " << e.p1.y << "\n";

    for (auto& e : landmarks) ofs << e.x << " " << e.y << "\n";

    ofs.close();
  }

  void load(const std::string& Filename) {
    edges.clear();
    landmarks.clear();

    std::ifstream ifs(Filename.c_str());
    if (!ifs.is_open()) {
      std::cout << "Error loading file : " << Filename << std::endl;
      return;
    }
    size_t NEdges, NLandmarks;
    ifs >> NEdges >> NLandmarks;
    for (size_t i = 0; i < NEdges; ++i) {
      Edge2d e;
      ifs >> e.p0.x >> e.p0.y >> e.p1.x >> e.p1.y;
      edges.push_back(e);
    }
    for (size_t i = 0; i < NLandmarks; ++i) {
      Point2d p;
      ifs >> p.x >> p.y;
      landmarks.push_back(p);
    }
    if(!landmarks.empty()) updateMarkDistances();
  }

 private:
  std::vector<Edge2d> edges;
  std::vector<Point2d> landmarks;
  std::vector<float> Dk;
  Point2d Begin;
};

#endif