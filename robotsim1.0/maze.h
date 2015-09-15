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
  bool visited;

  void set(unsigned i, unsigned j, unsigned v) {
    this->i = i;
    this->j = j;
    this->v = v;
    visited = false;
  } 
  bool hasAllWalls() {
    return (v & 0x0F) == 0x0F;
  }
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
  Maze(unsigned M, unsigned N) : N(N), M(M), Begin(0), End(0) {
    Grid = new Cell[N * M];
    initialize();
  }

  ~Maze() {
    delete Grid;
  }
 
  void generate(unsigned m, unsigned n) {
    N = n;
    M = m;
    delete Grid;
    Begin = 0;
    End = 0;
    Grid = new Cell[N * M];
    initialize();
  }

  void initialize() {
    for (unsigned i = 0; i < M; ++i)
      for (unsigned j = 0; j < N; ++j)
        Grid[i * M + j].set(i, j, 0x0F);
    for (unsigned j = 0; j < N; ++j) {
      Grid[0 * N + j].v |= BN; // N Border
      Grid[(M - 1) * N + j].v |= BS; // S border
    }
    for (unsigned i = 0; i < M; ++i) {
      Grid[i * N + 0].v |= BW; // E Border
      Grid[i * N + N - 1].v |= BE; // W Border
    }
    generate(); 
    setBegin(0, 0);
    setEnd(M - 1, N - 1);
    solve();
  }  
   
 
  Cell *getGrid() const {
    return Grid;
  }
  unsigned getWidth() const {
    return N;
  }
  unsigned getHeight() const {
    return M;
  }
  
  void setBegin(unsigned i, unsigned j) {
     Begin = &Grid[i * N + j];
  }

  void setEnd(unsigned i, unsigned j) {
     End = &Grid[i * N + j];
  }

  Cell *getBegin() const{
    return Begin;
  }

  Cell *getEnd() const {
    return End;
  }


  Cell *getNeighbor(Cell *C , unsigned dir) {
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
    std::stack<Cell*> Cells;
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
           

  Cell *nextSolution(Cell *Current) {
    Cell *Neighbors[4];
    unsigned Dir[5];
    unsigned NMax = 0;
    for (unsigned k = 0; k < 4; ++k) {
      if (!Current->hasWall(k)) {
        Cell *Neighbor = getNeighbor(Current, k);
        if (Neighbor && !Neighbor->visited) {
          Neighbors[NMax] = Neighbor;
          Dir[NMax] = k;
          ++NMax;
        }
      }
    }
    if (NMax) {
      unsigned n = rand() % NMax;
      Cell *Neighbor = Neighbors[n];
      Neighbor->visited = true;
      Sol.push_back(Current);
      Visited.push_back(Current);
      return Neighbor;
    } else {
      Cell *Neighbor = Sol.back();
      Visited.push_back(Current);
      Sol.pop_back();
      return Neighbor;
    }
  }

  void solve() {
    Sol.clear();
    Visited.clear();
    Cell *CurrentSol = Begin;
    Begin->visited = true;
    while (CurrentSol != End) {
      CurrentSol = nextSolution(CurrentSol);
    }
    Sol.push_back(End);
    Visited.push_back(End);
  }

  Cell *nextDistanceToEnd(Cell *Current, std::vector<bool>& Visited, std::list<Cell*> Solution) {
    Cell *Neighbors[4];
    unsigned Dir[5];
    unsigned NMax = 0;
    for (unsigned k = 0; k < 4; ++k) {
      if (!Current->hasWall(k)) {
        Cell *Neighbor = getNeighbor(Current, k);
        unsigned idx = Neighbor->i * M + Neighbor->j;
        if (Neighbor && !Visited[idx]) {
          Neighbors[NMax] = Neighbor;
          Dir[NMax] = k;
          ++NMax;
        }
      }
    }
    if (NMax) {
      unsigned n = rand() % NMax;
      Cell *Neighbor = Neighbors[n];
      unsigned idx = Neighbor->i * M + Neighbor->j;
      Visited[idx] = true;
      Sol.push_back(Current);
      return Neighbor;
    }
    else {
      Cell *Neighbor = Sol.back();
      Sol.pop_back();
      return Neighbor;
    }
  }

  size_t distanceToEnd(size_t i, size_t j) {
    Cell *CurrentSol = &Grid[i * M + j];
    std::vector<bool> Visited(M * N);
    std::fill(Visited.begin(), Visited.end(), false);
    Visited[0] = true;
    std::list<Cell*> Solution;
    while (CurrentSol != End) {
      CurrentSol = nextDistanceToEnd(CurrentSol, Visited, Solution);
    }
    return Solution.size();
  }
  
  typedef std::list<Cell*>::iterator Iterator;
  Iterator solBegin() {
    return Sol.begin();
  }

  Iterator solEnd() {
    return Sol.end();
  }
    
  Iterator visitedBegin() {
    return Visited.begin();
  }
 
  Iterator visitedEnd() {
    return Visited.end();
  }

private:
   unsigned N;
   unsigned M;
   Cell *Grid;
   Cell *Begin;
   Cell *End;
   std::list<Cell*> Sol;
   std::list<Cell*> Visited;
};


#endif