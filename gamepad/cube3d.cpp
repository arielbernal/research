#if 0
#define _USE_MATH_DEFINES
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include "include/glheaders.h"
#include "include/glprimitives.h"
#include "glcube3d.h"


namespace {
  int WinWidth = 1100;
  int WinHeight = 1100;
  int ViewWidth = 100;
  float WinRatio = WinHeight / float(WinWidth);
  int ViewHeight = ViewWidth * WinRatio;
  std::string WinTitle = "Cube";
  GLCube3D cube3d(WinWidth, WinHeight, false);
}


void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  cube3d.render(1);
  glutSwapBuffers();
}

void reshape(int w, int h) {
  cube3d.reshape(w, h);
}

void mouse_wheel(int wheel, int direction, int x, int y) {
  cube3d.mouse_button(direction > 0 ? 3 : 4, GLUT_DOWN, x, y);
}

void mouse_button(int button, int status, int x, int y) {
  cube3d.mouse_button(button, status, x, y);
}

void mouse_active_motion(int x, int y) {
  cube3d.mouse_active_motion(x, y);
}

void mouse_passive_motion(int x, int y) {
  cube3d.mouse_passive_motion(x, y);
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
    glutPostRedisplay();
    break;
  default:
    break;
  }
}

void normal_keys(unsigned char key, int x, int y) {
  switch (key) {
  case 'a':
    cube3d.printMatrix();
    break;
  case '1':
    cube3d.onlyOne = 1;
    break;
  case '2':
    cube3d.onlyOne = 2;
    break;
  case '3':
    cube3d.onlyOne = 3;
    break;
  case '4':
    cube3d.onlyOne = 4;
    break;
  case '5':
    cube3d.onlyOne = 5;
    break;
  case '6':
    cube3d.onlyOne = 6;
    break;
  case '7':
    cube3d.onlyOne = 7;
    break;
  case '0':
    cube3d.onlyOne = -1;
    break;
  case 'l':
    break;
  case 't':
    break;
  case 32: {
    glutPostRedisplay();
    break;
  }
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

  glutMainLoop();
}

int main1(int argc, char **argv) {
  init_glut_window(argc, argv);

  return 0;
}
#endif