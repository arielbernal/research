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
  Track(size_t MazeM, size_t MazeN, float d) : Mz(MazeM, MazeN), DMaze(d) {
    getEdgesFromMaze(Mz, d);
  }

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
    const std::vector<Cell>& Grid = Mz.getGrid();
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
    const Cell* b = Mz.getBegin();
    Begin = Point2d(b->j * d - (M - 1) * d / 2,
                    (N - b->i) * d - (N + 1) * d / 2);
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        Point2d P(j * d - (M - 1) * d / 2, (N - i) * d - (N + 1) * d / 2);
        landmarks.push_back(P);
        P(j * d - (M - 1) * d / 2 - d / 4, (N - i) * d - (N + 1) * d / 2 + d /4 );
        landmarks.push_back(P);
        P(j * d - (M - 1) * d / 2 + d / 4, (N - i) * d - (N + 1) * d / 2 - d /4 );
        landmarks.push_back(P);
        P(j * d - (M - 1) * d / 2 + d / 4, (N - i) * d - (N + 1) * d / 2 + d /4 );
        landmarks.push_back(P);
        P(j * d - (M - 1) * d / 2 - d / 4, (N - i) * d - (N + 1) * d / 2 - d /4 );
        landmarks.push_back(P);

      }
    }
    updateMarkDistances();
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
    if (!landmarks.empty()) updateMarkDistances();
  }

  const Maze& getMaze() const { return Mz; }

  size_t getMazeDistance(size_t i0, size_t j0, size_t i1, size_t j1) {
    return Mz.getDistance(i0, j0, i1, j1);
  }

  float getMazeDistanceTo(float x, float y, size_t i1, size_t j1) {
    size_t M = Mz.getHeight();
    size_t N = Mz.getWidth();

    size_t j0 = x / DMaze + N / 2;
    size_t i0 = M / 2 - y / DMaze;
    std::list<Cell*> Solution;
    float d = Mz.solve(i0, j0, i1, j1, Solution);
    std::list<Cell*>::iterator it = Solution.begin();
    it++;
    if (it == Solution.end()) it = Solution.begin();
    auto &e = (*it);
    float xn = (float(e->j) - N / 2 + 0.5) * DMaze;
    float yn = (M / 2 - float(e->i) - 0.5) * DMaze;
    return d * DMaze + distance(Point2d(x, y), Point2d(xn, yn));
  }

  void drawPathToEnd(size_t i, size_t j) {
    std::list<Cell*> Solution;
    Mz.solve(i, j, Solution);

    size_t M = Mz.getHeight();
    size_t N = Mz.getWidth();   
    glBegin(GL_LINE_STRIP);
    for (auto& e : Solution) {
      float x = (float(e->j) - N / 2 + 0.5) * DMaze;
      float y = (M / 2 - float(e->i) - 0.5) * DMaze;
   //   std::cout << e->i << " " << e->j << std::endl;
      glVertex2f(x, y);
    }
    glEnd();
  }

  size_t getXId(float x) {
    size_t N = Mz.getWidth();
    return x / DMaze + N / 2;
  }

  size_t getYId(float y) {
    size_t M = Mz.getHeight();
    return M / 2 - y / DMaze;
  }

  float getMazeDistanceToEnd(float x, float y) {
    return getMazeDistanceTo(x, y, Mz.getEnd()->i, Mz.getEnd()->j);
  }

 private:
  std::vector<Edge2d> edges;
  std::vector<Point2d> landmarks;
  std::vector<float> Dk;
  Point2d Begin;

  Maze Mz;
  float DMaze;
};

#endif