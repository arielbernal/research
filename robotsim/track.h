#ifndef TRACK_H
#define TRACK_H

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
    Begin = Point2d(b->j * d - N * d / 2 + d / 2, (N - b->i) * d - N * d / 2 - d / 2);
  }

  void addEdge(float x0, float y0, float x1, float y1){
    edges.push_back(Edge2d(x0, y0, x1, y1));
  }

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

 private:
  std::vector<Edge2d> edges;
  Point2d Begin;
};

#endif