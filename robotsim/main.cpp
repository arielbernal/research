#define _USE_MATH_DEFINES

#include <iostream>
#include "include/glheaders.h"
#include <cmath>
#include "include/glprimitives.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

#include "robot_path.h"
#include "point2d.h"
#include "robot.h"
#include "robot_unit.h"
#include "ffnn3l.h"


class GA {
 public:
  GA(size_t N) : N(N), Population(N), TMax(0), t(0) {
    newRandomPopulation();
    started = false;
    generation = 0;
  }

  void print() {
    for (size_t i = 0; i < N; ++i) Population[i].print();
  }

  int generation;

  void update(float dt) {
    if (started) {
      if (t < TMax) {
        for (size_t i = 0; i < N; ++i) Population[i].update(dt);
        float vmax = 0;
        for (size_t i = 0; i < N; ++i) {
          float v = Population[i].getV();
          if (v > vmax) vmax = v;
        }
        t += dt;
      } else {
        float davg = 0;
        for (size_t i = 0; i < N; ++i)
          davg += sqrt(Population[i].getDistance2());
        davg /= N;
        std::cout << generation++ << "  d = " << davg << std::endl;
        nextGeneration();
        //started = false;
        t = 0;
      }
    }
  }

  void sortPopulation() {
    std::sort(Population.begin(), Population.end(),
              [](const RobotUnit& a, const RobotUnit& b)
                  -> bool { return (a.getDistance2() < b.getDistance2()); });
  }

  RobotUnit reproduce(RobotUnit& x, RobotUnit& y) {
    RobotUnit child;
    child.getParentsGenes(x.getBrain(), y.getBrain());
    return child;
  }

  void nextGeneration() {
    sortPopulation();
    Population[0].setGlow();
    std::vector<RobotUnit> NP(N);
    static std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, Population.size() / 2 - 1);
    for (size_t i = 0; i < N; ++i) {
      RobotUnit child;
      child.getParentGenes(Population[i % 10].getBrain());
      child.randomMutation();
      NP[i] = child;
    }
    /*
    for (size_t i = 0; i < Population.size() / 20; ++i) {
      size_t i0 = distribution(generator);
      size_t i1 = distribution(generator);
      RobotUnit x = Population[i0];
      RobotUnit y = Population[i1];
      for (int j = 0; j < 20; ++j) {
        RobotUnit child = reproduce(x, y);
        child.randomMutation();
        NP[20 * i + j] = child;
      }
    }*/
    Population = NP;
  }

  void startSimulation(float T) {
    TMax = T;
    started = true;
  }

  void render() {
    for (size_t i = 0; i < N; ++i) {
      Population[i].render();
      Point2d t = Population[i].getTarget();
      glColor3f(0, 1, 0);
      drawDisk(t.x, t.y, 0.5, 20);
    }
  }

 protected:
  void newRandomPopulation() {
    Population.clear();
    Population.resize(N);
    for (size_t i = 0; i < N; ++i) {
      Population[i] = RobotUnit();
    }
  }

 private:
  size_t N;
  std::vector<RobotUnit> Population;
  float TMax;
  float t = 0;
  bool started;
};

namespace {
int m_window_width = 1000;
int m_window_height = 1000;
std::string m_window_title = "RobotSim";
GA ga(200);
}

void set2DMode(size_t Width, size_t Height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, Width, 0, Height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void set3DMode(size_t Width, size_t Height) {
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, float(Width) / Height, 0.01f, 1000);
  gluLookAt(80, 0, 80, 0, 0, 0, 0.0, 1.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  set2DMode(300, 300);
  glTranslatef(150, 150, 0);
  ga.update(0.2f);
  ga.render();
  glutSwapBuffers();
}

void init_display() {
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glLineWidth(1.5);
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  init_display();
  display();
}

void mouse_wheel(int wheel, int direction, int x, int y) {}

void mouse_button(int button, int state, int x, int y) {}

void mouse_active_motion(int x, int y) {}

void mouse_passive_motion(int x, int y) {}

void special_keys(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      break;
    case GLUT_KEY_DOWN:
      break;
    case GLUT_KEY_RIGHT:
      break;
    case GLUT_KEY_LEFT:
      break;
    default:
      break;
  }
}

void normal_keys(unsigned char key, int x, int y) {
  switch (key) {
    case 'a':
      break;
    case 's':
      break;
    case 32:
      ga.startSimulation(8);
      glutPostRedisplay();
      break;
    case 27:
      glutLeaveMainLoop();
      break;
    default:
      break;
  }
}

void init_glut_window(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(1800, 100);
  glutInitWindowSize(m_window_width, m_window_height);
  glutCreateWindow(m_window_title.c_str());

  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutKeyboardFunc(normal_keys);
  glutSpecialFunc(special_keys);
  glutMouseFunc(mouse_button);
  glutMotionFunc(mouse_active_motion);
  glutPassiveMotionFunc(mouse_passive_motion);
  glutMouseWheelFunc(mouse_wheel);
  glutReshapeFunc(reshape);

  glutMainLoop();
}

int main(int argc, char** argv) {
  init_glut_window(argc, argv);
  return 0;
}
