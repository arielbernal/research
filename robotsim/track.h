#ifndef TRACK_H
#define TRACK_H


class Track {
 public:
  Track(size_t N = 5) : N(N), Mz(N, N), d(25) {
    Mz.initialize();
    getEdges();
  }

  void render() {
    drawMaze(Mz, d);
  }

  Point2d getBeginCenter() {
    Cell* b = Mz.getBegin();
    return Point2d(b->j * d - N * d / 2 + d / 2, (N - b->i) * d - N * d / 2 - d / 2);
  }

  void getDistanceToEdge(Robot& r) {

  }

 protected:
  void drawMaze(Maze& Mz, float d) {
    glColor3f(0, 0.4, 0.7);
    glBegin(GL_LINES);
    for (auto& e : edges) {
      glVertex2f(e.p0.x, e.p0.y);
      glVertex2f(e.p1.x, e.p1.y);
    }
    glEnd();
  }

  void getEdges() {
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
  }

 private:
  size_t N;
  Maze Mz;
  float d;
  std::vector<Edge2d> edges;
};

#endif