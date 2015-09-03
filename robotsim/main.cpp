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
#include "robot_ga.h"

namespace {
int m_window_width = 1000;
int m_window_height = 1000;
std::string m_window_title = "RobotSim";
// RobotGA robot(5);
// FFNN3L nn(3, 8, 2);
GA ga(1000);
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

float mouse_vz, mouse_vx, mouse_vy;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  set2DMode(mouse_vz, mouse_vz);
  glTranslatef(mouse_vx, mouse_vy, 0);
  for (int i = 0; i < 100; ++i) ga.update(0.01f, track);
  ga.render();
  track.render();
  glutSwapBuffers();
}

void init_display() {
  mouse_vz = 300;
  mouse_vx = 150;
  mouse_vy = 150;
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

float mousex, mousey;
int rmouseb;

void mouse_wheel(int wheel, int direction, int x, int y) {
  y = 1000 - y;
  float xp = x / 1000.0f * mouse_vz - mouse_vx;
  float yp = y / 1000.0f * mouse_vz - mouse_vy;
  mouse_vz += direction > 0 ? 20 : -20;
  if (mouse_vz > 2000) mouse_vz = 2000;
  if (mouse_vz < 1) mouse_vz = 1;
  mouse_vx = x / 1000.0f * mouse_vz - xp;
  mouse_vy = y / 1000.0f * mouse_vz - yp;
  mousex = x;
  mousey = y;
}

void mouse_button(int button, int status, int x, int y) {
  y = 1000 - y;
  rmouseb = GLUT_UP;
  if ((button == 3) || (button == 4)) {
    if (status == GLUT_DOWN) {
      float xp = x / 1000.0f * mouse_vz - mouse_vx;
      float yp = y / 1000.0f * mouse_vz - mouse_vy;
      mouse_vz += button == 3 ? 20 : -20;
      if (mouse_vz > 2000) mouse_vz = 2000;
      if (mouse_vz < 1) mouse_vz = 1;
      mouse_vx = x / 1000.0f * mouse_vz - xp;
      mouse_vy = y / 1000.0f * mouse_vz - yp;
      mousex = x;
      mousey = y;     
    }
  }
  if (button == GLUT_RIGHT_BUTTON) {
    if (status == GLUT_DOWN) {
      rmouseb = GLUT_DOWN;
      mousex = x;
      mousey = y;
    }
  }
}

void mouse_active_motion(int x, int y) {
  y = 1000 - y;
  if (rmouseb == GLUT_DOWN) {
    float dx = (x - mousex) * mouse_vz / 1000;
    float dy = (y - mousey) * mouse_vz / 1000;
    mouse_vy += dy;
    mouse_vx += dx;
  }

  mousex = x;
  mousey = y;
}

void mouse_passive_motion(int x, int y) {
  y = 1000 - y;
  mousex = x;
  mousey = y;
  float xp = x / 1000.0f * mouse_vz - mouse_vx;
  float yp = y / 1000.0f * mouse_vz - mouse_vy;
}

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
    case GLUT_KEY_F10:
      mouse_vz = 300;
      mouse_vx = 150;
      mouse_vy = 150;
      glutPostRedisplay();
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
      ga.startSimulation(50);
      glutPostRedisplay();
      break;
    case 27:
      glutLeaveMainLoop();
      break;
    default:
      break;
  }
}

// void createSet(const std::string& FileName, size_t N) {
//   std::vector<double> In(3);
//   std::vector<double> Out(2);
//   unsigned seed =
//   std::chrono::system_clock::now().time_since_epoch().count();
//   std::default_random_engine generator(seed);
//   std::uniform_int_distribution<int> uniform(-100, 100);

//   NNDataset<double> DataSet(3, 2);
//   float dt = 0.1f;
//   float dx, dy, dtheta;
//   size_t in = 0;
//   while (in < N)  {
//     float Vl = uniform(generator);
//     float Vr = uniform(generator);
//     if (Vl + Vr < 0) continue;
//     robot.setMotors(Vl, Vr);
//     robot.relativeMove(dt, dx, dy, dtheta);
//     In[0] = dx;
//     In[1] = dy;
//     In[2] = dtheta;

//     Out[0] = robot.getMotorLeft() / 100.0f;
//     Out[1] = robot.getMotorRight() / 100.0f;
//     DataSet.addSample(In, Out);
//     in++;
//   }

//   In[0] = 2.17403e-5;
//   In[1] = 0.651979;
//   In[2] = -9.38887e-05;
//   Out[0] = 0.333694;
//   Out[1] = 0.332999;

//   NNSample<double> a(In, Out);
//   DataSet.meanCancellation(a);

//   DataSet.save(FileName);
//   NNSample<double> avg = DataSet.averageSample();

//   std::cout << "Average-------------------" << std::endl;
//   std::cout << "dx = " << avg.Input[0] << " dy = " << avg.Input[1] << "
//   dtheta = " << avg.Input[2] << std::endl;
//   std::cout << "Vl = " << avg.Output[0] << " Vr = " << avg.Output[1] <<
//   std::endl;

//   //dt = 0.1f;
//   //dx = 2.17403e-05 dy = 0.651979 dtheta = -9.38887e-05
//   //Vl = 0.333694 Vr = 0.332999

//   //DataSet.print();
// }

void init_glut_window(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(800, 100);
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
  // NNDataset<double> test(3, 2);
  // NNDataset<double> train(3, 2);
  // train.load(500, "tr500.dat");
  // test.load(500, "test500.dat");

  // FFNN3L NN(3, 8, 2);
  ////NN.train(train, 100000, 0.05, 0.8);
  // NN.test(train);
  // NN.test(test);
  ////NN.save("NN382.nn");
  // NN.load("NN382.nn");
  // NN.test(train);
  // NN.test(test);

  // track.addEdge(0, 15, 30, 15);
  // track.addEdge(0, -15, 30, -15);

  // track 1
  // track.makePolygon(0, 50, 50, 10);
  // track.makePolygon(0, 50, 80, 10);
  // track.addEdge(-15.5, 3, -25, -26);
  // track.makePoygonLandmarks(0, 50, 65, 20, -M_PI / 2, 2 * M_PI / 21);

  #if 0
   track.makePolygon(0, 50, 50, 10);
   track.makePolygon(0, 50, 80, 10);
   track.addEdge(-15.5, 3, -25, -26);
   track.makePoygonLandmarks(0, 50, 65, 20, -M_PI / 2, 2 * M_PI / 21);
   ga.setInitialPos(Point2d(0, -12), 0);
  #endif

  #if 1
  track.addEdge(-15, 15, 15, 15);
  track.addEdge(15, 15, 30, 30);
  track.addEdge(30, 30, 30, 60);
  track.addEdge(30, 60, 60, 60);
  track.addEdge(60, 60, 60, 90);
  track.addEdge(60, 90, -60, 90);
  track.addEdge(-60, 90, -60, 15);
  track.addEdge(-60, 15, -15, 15);

  track.addEdge(-15, -15, 20, -15);
  track.addEdge(20, -15, 55, 15);
  track.addEdge(55, 15, 55, 35);
  track.addEdge(55, 35, 85, 35);
  track.addEdge(85, 35, 85, 120);
  track.addEdge(85, 120, -90, 120);
  track.addEdge(-90, 120, -90, -15);
  track.addEdge(-90, -15, -15, -15);

  track.addEdge(-15, 15, -15, -15);

  track.addLandmark(0, 0);
  track.addLandmark(15, 0);
  track.addLandmark(30, 10);
  track.addLandmark(40, 20);
  track.addLandmark(40, 40);
  track.addLandmark(55, 48);
  track.addLandmark(70, 50);
  track.addLandmark(70, 70);
  track.addLandmark(70, 90);
  track.addLandmark(70, 105);
  track.addLandmark(50, 105);
  track.addLandmark(30, 105);
  track.addLandmark(10, 105);
  track.addLandmark(-10, 105);
  track.addLandmark(-30, 105);
  track.addLandmark(-50, 105);
  track.addLandmark(-75, 105);
  track.addLandmark(-75, 85);
  track.addLandmark(-75, 65);
  track.addLandmark(-75, 45);
  track.addLandmark(-75, 25);
  track.addLandmark(-75, 0);  
  track.addLandmark(-55, 0);  
  track.addLandmark(-35, 0);  

  track.updateMarkDistances();
  ga.setInitialPos(Point2d(0, 0), 0);
#endif

  
  //
   //robot.setPos(Point2d(0, -12), 0);
  // robot.setPos(Point2d(18, -14), 0);
  // if(robot.checkCollision(track))
  //   robot.setGlow(true);
  // else
  //   robot.setGlow(false);
  // robot.updateSensorDistances(track);

  glutMainLoop();
}

int main(int argc, char** argv) {
  init_glut_window(argc, argv);
  return 0;
}

