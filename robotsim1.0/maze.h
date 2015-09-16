#ifndef MAZE_H
#define MAZE_H

#include <stack>
#include <iostream>
#include <list>

const unsigned WN = 0x0001;
const unsigned WE = 0x0002;
const unsigned WS = 0x0004;
const unsigned WW = 0x0008;
const unsigned BN = 0x0010;
const unsigned BE = 0x0020;
const unsigned BS = 0x0040;
const unsigned BW = 0x0080;

struct Cell {
  unsigned i;
  unsigned j;
  unsigned v;

  void set(unsigned i, unsigned j, unsigned v) {
    this->i = i;
    this->j = j;
    this->v = v;
  }

  bool hasAllWalls() { return (v & 0x0F) == 0x0F; }

  bool hasWall(unsigned k) {
    if (k == 0) return v & WN;
    if (k == 1) return v & WE;
    if (k == 2) return v & WS;
    if (k == 3) return v & WW;
    return false;
  }

  void removeWall(unsigned k) {
    switch (k) {
      case 0:
        v &= 0xFE;
        break;
      case 1:
        v &= 0xFD;
        break;
      case 2:
        v &= 0xFB;
        break;
      case 3:
        v &= 0xF7;
        break;
    }
  }
};

class Maze {
 public:
  Maze() {}

  Maze(unsigned M, unsigned N)
      : N(N), M(M), Grid(N * M) {
    initialize();
    Begin = &Grid[0];
    End = &Grid[M * N - 1]; 
  }

  void initialize() {
    for (unsigned i = 0; i < M; ++i)
      for (unsigned j = 0; j < N; ++j) Grid[i * M + j].set(i, j, 0x0F);
    for (unsigned j = 0; j < N; ++j) {
      Grid[0 * N + j].v |= BN;        // N Border
      Grid[(M - 1) * N + j].v |= BS;  // S border
    }
    for (unsigned i = 0; i < M; ++i) {
      Grid[i * N + 0].v |= BW;      // E Border
      Grid[i * N + N - 1].v |= BE;  // W Border
    }
    generate();
  }

  unsigned getWidth() const { return N; }
  unsigned getHeight() const { return M; }

  Cell *getNeighbor(Cell *C, unsigned dir) {
    unsigned i = C->i;
    unsigned j = C->j;
    if (dir == 0 && !(C->v & BN) && i > 0) return &Grid[(i - 1) * N + j];
    if (dir == 1 && !(C->v & BE) && j < N + 1) return &Grid[i * N + j + 1];
    if (dir == 2 && !(C->v & BS) && i < M + 1) return &Grid[(i + 1) * N + j];
    if (dir == 3 && !(C->v & BW) && j > 0) return &Grid[i * N + j - 1];
    return NULL;
  }

  void generate() {
    unsigned T = N * M;
    unsigned Visited = 1;
    Cell *Current = &Grid[0];
    Cell *Neighbors[4];
    unsigned Dir[4];
    std::stack<Cell *> Cells;
    while (Visited < T) {
      unsigned NMax = 0;
      for (unsigned k = 0; k < 4; ++k) {
        Cell *Neighbor = getNeighbor(Current, k);
        if (Neighbor && Neighbor->hasAllWalls()) {
          Neighbors[NMax] = Neighbor;
          Dir[NMax] = k;
          ++NMax;
        }
      }
      if (NMax) {
        unsigned n = rand() % NMax;
        Cell *Neighbor = Neighbors[n];
        Current->removeWall(Dir[n]);
        Neighbor->removeWall((Dir[n] + 2) % 4);
        Cells.push(Current);
        Current = Neighbor;
        Visited++;
      } else {
        Current = Cells.top();
        Cells.pop();
      }
    }
  }

  Cell *nextSolution(const Cell *Current, std::vector<bool> &Visited,
                     std::list<Cell *> &Solution) {
    Cell *Neighbors[4];
    unsigned NMax = 0;
    for (unsigned k = 0; k < 4; ++k) {
      if (!Current->hasWall(k)) {
        Cell *Neighbor = getNeighbor(Current, k);
        unsigned idx = Neighbor->i * M + Neighbor->j;
        if (Neighbor && !Visited[idx]) {
          Neighbors[NMax] = Neighbor;
          ++NMax;
        }
      }
    }
    if (NMax) {
      unsigned n = 0;//rand() % NMax;
      Cell *Neighbor = Neighbors[n];
      unsigned idx = Neighbor->i * M + Neighbor->j;
      Visited[idx] = true;
      Solution.push_back(Current);
      return Neighbor;
    } else {
      Cell *Neighbor = Solution.back();
      Solution.pop_back();
      return Neighbor;
    }
  }

  // size_t solve(std::list<Cell *> &Solution) {
  //   return solve(Begin->i, Begin->j, End->i, End->j, Solution);
  // }

  size_t solve(size_t i0, size_t j0, size_t i1, size_t j1,
               std::list<Cell *> &Solution) {
    Cell *CurrentSol = &Grid[i0 * M + j0];
    Cell *EndSol = &Grid[i1 * M + j1];
    Solution.clear();
    std::vector<bool> Visited(M * N);
    std::fill(Visited.begin(), Visited.end(), false);
    while (CurrentSol != EndSol) {
      CurrentSol = nextSolution(CurrentSol, Visited, Solution);
    }
    // for(auto &e : Solution) {
    //   std::cout << "      " << e->i << " " << e->j << std::endl;
    // }
    return Solution.size();
  }

  size_t getDistance(size_t i0, size_t j0, size_t i1, size_t j1) {
    std::list<Cell *> Solution;
    return solve(i0, j0, i1, j1, Solution);
  }

  const Cell *getBegin() const { return Begin; }
  const Cell *getEnd() const  { return End; }

  const std::vector<Cell> &getGrid() const { return Grid; }

 private:
  unsigned N;
  unsigned M;
  std::vector<Cell> Grid;
  Cell *Begin;
  Cell *End;
};

#endif