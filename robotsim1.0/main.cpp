#define _USE_MATH_DEFINES

#include <iostream>
#include "include/glheaders.h"
#include <cmath>
#include "include/glprimitives.h"

namespace {
int m_window_width = 1200;
int m_window_height = 700;
std::string m_window_title = "RobotSim";
}

void set2DMode(size_t Width, size_t Height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, Width, 0, Height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

float mouse_vz, mouse_vx, mouse_vy;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  set2DMode(12/7.0, 1);
    
  glBegin(GL_LINE_LOOP);
  glVertex2f(0.5, 0.5);
  glVertex2f(0.75, 0.5);
  glVertex2f(0.75, 0.75);
  glVertex2f(0.5, 0.75);

  glEnd();
  //glTranslatef(mouse_vx, mouse_vy, 0);

  //set2DMode(1000, 1000);
  //printFloat(10, 1000 - 20, "Time = ",4444, 3, 2);

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
  glViewport(0, 0, w/2, h);
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

void init_glut_window(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
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