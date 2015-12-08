#define _USE_MATH_DEFINES
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include "../include/glheaders.h"
#include "../include/glprimitives.h"
#include "glRobotSim2d.h"

namespace {
  int WinWidth = 1100;
  int WinHeight = 1100;
  int ViewWidth = 100;
  float WinRatio = WinHeight / float(WinWidth);
  int ViewHeight = ViewWidth * WinRatio;
  std::string WinTitle = "GamePad";
  Robot2D robot(20, 4.5, 0, 0, M_PI/2);
  GLRobotSim2D glRobot(robot, 200);
}

bool stopped = true;
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //robot.setV(200, 255);
  if (!stopped) {
    robot.update(0.001f);
  }
  glRobot.display();
  printText(1, 10, format("Time = %5.5f", robot.T));
  printText(1, 20, format("X = %5.2f, y = %5.2f, theta = %5.2f", robot.x, robot.y, robot.theta /M_PI * 180));
  printText(1, 30, format("EncL = %5.2f, EncR = %5.2f", robot.EncL, robot.EncR));
  glutSwapBuffers();
}

void init_display() {
  glRobot.init_display();
}


void reshape(int w, int h) {
  glRobot.reshape(w, h);
}

void mouse_wheel(int wheel, int direction, int x, int y) {
  glRobot.mouse_wheel(wheel, direction, x, y);
}

void mouse_button(int button, int status, int x, int y) {
  glRobot.mouse_button(button, status, x, y);
}

void mouse_active_motion(int x, int y) {
  glRobot.mouse_active_motion(x, y);
}

void mouse_passive_motion(int x, int y) { 
  glRobot.mouse_passive_motion(x, y);
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
    robot.setTarget(-3, -10);
    break;
  case 32: {
    stopped = !stopped;
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

int main(int argc, char **argv) {
  init_glut_window(argc, argv);

  return 0;
}