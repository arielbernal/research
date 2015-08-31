#define _USE_MATH_DEFINES

#include <iostream>
#include "include/glheaders.h"
#include <cmath>
#include "include/glprimitives.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <chrono>

#include "ga.h"
#include "robot_path.h"
#include "point2d.h"
#include "robot.h"
#include "robot_unit.h"
#include "ffnn3l.h"
#include "maze.h"
#include "track.h"
#include "nndataset.h"

namespace {
int m_window_width = 1000;
int m_window_height = 1000;
std::string m_window_title = "RobotSim";
Robot robot;
FFNN3L nn(3, 8, 2);
Track track;
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
  robot.render();
  track.render();
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
      glutPostRedisplay();
      break;
    case 27:
      glutLeaveMainLoop();
      break;
    default:
      break;
  }
}

void createSet(const std::string& FileName, size_t N) {
  std::vector<double> In(3);
  std::vector<double> Out(2);
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> uniform(-100, 100);

  NNDataset<double> DataSet(3, 2);
  float dt = 0.1f;
  float dx, dy, dtheta;
  size_t in = 0;
  while (in < N)  {
    float Vl = uniform(generator);
    float Vr = uniform(generator);
    if (Vl + Vr < 0) continue;
    robot.setMotors(Vl, Vr);
    robot.relativeMove(dt, dx, dy, dtheta);
    In[0] = dx;
    In[1] = dy;
    In[2] = dtheta;

    Out[0] = robot.getMotorLeft() / 100.0f;
    Out[1] = robot.getMotorRight() / 100.0f;
    DataSet.addSample(In, Out);
    in++;
  }


  In[0] = 2.17403e-5;
  In[1] = 0.651979;
  In[2] = -9.38887e-05;
  Out[0] = 0.333694;
  Out[1] = 0.332999;

  NNSample<double> a(In, Out);
  DataSet.meanCancellation(a);

  DataSet.save(FileName);
  NNSample<double> avg = DataSet.averageSample();

  std::cout << "Average-------------------" << std::endl;
  std::cout << "dx = " << avg.Input[0] << " dy = " << avg.Input[1] << " dtheta = " << avg.Input[2] << std::endl;
  std::cout << "Vl = " << avg.Output[0] << " Vr = " << avg.Output[1] << std::endl;

  //dt = 0.1f;
  //dx = 2.17403e-05 dy = 0.651979 dtheta = -9.38887e-05
  //Vl = 0.333694 Vr = 0.332999


  //DataSet.print();
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

  ////createSet("test500.dat", 500);
  //NNDataset<double> test(3, 2);
  //NNDataset<double> train(3, 2);
  //train.load(500, "tr500.dat");
  //test.load(500, "test500.dat");

  //FFNN3L NN(3, 8, 2);
  ////NN.train(train, 100000, 0.05, 0.8);
  //NN.test(train);
  //NN.test(test);
  ////NN.save("NN382.nn");
  //NN.load("NN382.nn");
  //NN.test(train);
  //NN.test(test);


  //track.addEdge(0, 15, 30, 15);
  //track.addEdge(0, -15, 30, -15);
  track.makePolygon(0, 50, 50, 10);
  track.makePolygon(0, 50, 80, 10);
  
  glutMainLoop();
}



float dot(const Point2d& a, const Point2d& b) {
  return a.x *b.x + a.y *b.y;
}

bool lineSegmentIntersection(const Point2d& e, const Point2d& d, const Edge2d& a, const Point2d& I) {
  return false;
}

int main(int argc, char** argv) {
  init_glut_window(argc, argv);
  return 0;
}
