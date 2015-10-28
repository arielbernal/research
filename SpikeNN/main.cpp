#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>
#include "include/glheaders.h"
#include "include/glprimitives.h"
#include "gl2dgennn.h"

#include "nngen.h"

namespace {
int WinWidth = 1200;
int WinHeight = 1000;
int ViewWidth = 300;
std::string WinTitle = "SpikeNN";
GENNeuralNet NN(1, 1, 2, 1);
GL2DGENNN glNN(&NN, ViewWidth, WinWidth, WinHeight);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glNN.display();
  glutSwapBuffers();
}

void reshape(int w, int h) { glNN.reshape(w, h); }

void mouse_wheel(int wheel, int direction, int x, int y) {
  glNN.mouse_wheel(wheel, direction, x, y);
}

void mouse_button(int button, int status, int x, int y) {
  glNN.mouse_button(button, status, x, y);
}

void mouse_active_motion(int x, int y) { glNN.mouse_active_motion(x, y); }

void mouse_passive_motion(int x, int y) { glNN.mouse_passive_motion(x, y); }

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
  case 'l':
    break;
  case 't':
    break;
  case 32:
    break;
  case 27:
    glutLeaveMainLoop();
    break;
  default:
    break;
  }
}

void init_glut_window(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(WinWidth, WinHeight);
  glutCreateWindow(WinTitle.c_str());

  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);

  glutKeyboardFunc(normal_keys);
  glutSpecialFunc(special_keys);

  glutMouseFunc(mouse_button);
  glutMotionFunc(mouse_active_motion);
  glutPassiveMotionFunc(mouse_passive_motion);
#ifdef WIN32
  glutMouseWheelFunc(mouse_wheel);
#endif

  for (size_t i = 0; i < 15; ++i)
    NN.generateSynapses();

  glutMainLoop();
}

int main(int argc, char **argv) {
  init_glut_window(argc, argv);

  return 0;
}