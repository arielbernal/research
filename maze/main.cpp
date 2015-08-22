#include <GL/glut.h>
#include <GL/glu.h>
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
   
 
  Cell *getGrid() {
    return Grid;
  }
  unsigned getWidth() {
    return N;
  }
  unsigned getHeight() {
    return M;
  }
  
  void setBegin(unsigned i, unsigned j) {
     Begin = &Grid[i * N + j];
  }

  void setEnd(unsigned i, unsigned j) {
     End = &Grid[i * N + j];
  }

  Cell *getBegin() {
    return Begin;
  }

  Cell *getEnd() {
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
   Cell *Grid;
   Cell *Begin;
   Cell *End;
   unsigned N;
   unsigned M;
   std::list<Cell*> Sol;
   std::list<Cell*> Visited;
};



Maze SmallMaze(4, 4);


void drawCellLine(float x, float y, float d, unsigned dir, unsigned type) {
  if (type == 0) 
    glColor3f(1, 1, 1);
  else
    glColor3f(1, 1, 0);
  glBegin(GL_LINES);
    if (dir == 0) { 
      glVertex2f(x , y);
      glVertex2f(x + d, y);
    }
    if (dir == 1) {
      glVertex2f(x + d, y);
      glVertex2f(x + d, y - d);
    }
    if (dir == 2) {
      glVertex2f(x, y - d);
      glVertex2f(x + d, y - d);
    }
    if (dir == 3) {
      glVertex2f(x, y);
      glVertex2f(x, y - d);
    }
  glEnd();
}

void drawMaze(Maze &Mz, float d) {
  Cell *Grid = Mz.getGrid();
  unsigned N = Mz.getWidth();
  unsigned M = Mz.getHeight();
  for (unsigned i = 0; i < M; ++i) {
    for (unsigned j = 0; j < N; ++j) {
      unsigned Cell = Grid[i * N + j].v;
      float x = j * d;
      float y = (M - i) * d;
      if (Cell & WN) drawCellLine(x, y, d, 0, 0);
      if (Cell & WE) drawCellLine(x, y, d, 1, 0);
      if (Cell & WS) drawCellLine(x, y, d, 2, 0);
      if (Cell & WW) drawCellLine(x, y, d, 3, 0);
      if (Cell & BN) drawCellLine(x, y, d, 0, 1);
      if (Cell & BE) drawCellLine(x, y, d, 1, 1);
      if (Cell & BS) drawCellLine(x, y, d, 2, 1);
      if (Cell & BW) drawCellLine(x, y, d, 3, 1);
    }
  }
}

void drawBeginEnd(Maze &Mz, float d) {
  Cell *Begin = Mz.getBegin();
  Cell *End = Mz.getEnd();
  unsigned N = Mz.getWidth();
  unsigned M = Mz.getHeight();
  float b = d / 10;
  float x = Begin->j * d;
  float y = (M - Begin->i) * d;
  glColor3f(0, 1, 0);
  glBegin(GL_QUADS);
    glVertex2f(x + b, y - b);
    glVertex2f(x + d - b, y - b);
    glVertex2f(x + d - b, y - d + b);
    glVertex2f(x + b, y - d + b);
  glEnd();
  x = End->j * d;
  y = (N - End->i) * d;
  glColor3f(1, 0, 0);
  glBegin(GL_QUADS);
    glVertex2f(x + b, y - b);
    glVertex2f(x + d - b, y - b);
    glVertex2f(x + d - b, y - d + b);
    glVertex2f(x + b, y - d + b);
  glEnd();
} 

void drawCell(float x0, float y0, float x1, float y1, float d, unsigned type) {
  if (type == 0)
    glColor3f(1, 1, 0);
  else
    glColor3f(0.5, 0.5, 0.5);
  float b = d / 4;
  glBegin(GL_QUADS);
    glVertex2f(x0 + b, y0 - b);
    glVertex2f(x0 + d - b, y0 - b);
    glVertex2f(x0 + d - b, y0 - d + b);
    glVertex2f(x0 + b, y0 - d + b);
  glEnd();
  glBegin(GL_QUADS);
    glVertex2f(x1 + b, y1 - b);
    glVertex2f(x1 + d - b, y1 - b);
    glVertex2f(x1 + d - b, y1 - d + b);
    glVertex2f(x1 + b, y1 - d + b);
  glEnd();
  float xc = (x0 + x1) / 2;
  float yc = (y0 + y1) / 2;
  glBegin(GL_QUADS);
    glVertex2f(xc + b, yc - b);
    glVertex2f(xc + d - b, yc - b);
    glVertex2f(xc + d - b, yc - d + b);
    glVertex2f(xc + b, yc - d + b);
  glEnd();
}



void drawSolution(Maze &Mz, float d) {
  unsigned M = Mz.getHeight();
  Maze::Iterator P = Mz.solBegin();
  Cell *Prev = (*P);
  float x0 = Prev->j * d;
  float y0 = (M - Prev->i) * d;
  ++P;
  for (Maze::Iterator I = P, E = Mz.solEnd(); I != E; ++I) {
    float x1 = (*I)->j * d;
    float y1 = (M - (*I)->i) * d;
    drawCell(x0, y0, x1, y1, d, 0);
    x0 = x1;
    y0 = y1;
  }
}  

void drawRoute(Maze &Mz, float d) {
   unsigned M = Mz.getHeight();
  Maze::Iterator P = Mz.visitedBegin();
  Cell *Prev = (*P);
  float x0 = Prev->j * d;
  float y0 = (M - Prev->i) * d;
  ++P;
  for (Maze::Iterator I = P, E = Mz.visitedEnd(); I != E; ++I) {
    float x1 = (*I)->j * d;
    float y1 = (M - (*I)->i) * d;
    drawCell(x0, y0, x1, y1, d, 1);
    x0 = x1;
    y0 = y1;
  }
} 

void draw(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1, 1, 1);
  glTranslatef(5, 5, 0);
  float d = 12 * 20;
  drawMaze(SmallMaze, d);
  drawRoute(SmallMaze, d);
  drawSolution(SmallMaze, d);
  drawBeginEnd(SmallMaze, d);
  glTranslatef(-5, -5, 0);
  glFlush();
}

void reshape(int width, int height) {
  glViewport(0, 0, width, height);
  float aspect = width / float(height);
  glLoadIdentity();
//if (width >= height)
//  gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
//else
//  gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
  gluOrtho2D(0, width, 0, height);
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27: exit(0);
             break;
    case 32: SmallMaze.initialize();
             break;
  }
  glutPostRedisplay();
}


int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(500, 300);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("Green Window");
  glutDisplayFunc(draw);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glClearColor(0, 0, 0, 1);
  glutMainLoop();
  return 0;
}
