#define _USE_MATH_DEFINES

#include <iostream>
#include "include/glheaders.h"
#include <cmath>
#include "include/glprimitives.h"
#include <vector>
#include <queue>

#include "robot_path.h"
#include "point2d.h"
#include "robot.h"

namespace {
int m_window_width = 1000;
int m_window_height = 1000;
std::string m_window_title = "RobotSim";
Robot robot;
Path path;
Point2d dst(40, 40);
std::queue<RobotEvent> events;
float dt = 0.01f;
float t = 0;
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

void checkEvents() {
  if (!events.empty()) {
    RobotEvent e = events.front();
    if (t > e.time) {
      events.pop();
      switch (e.type) {
      case RobotEvent::STOP : 
          robot.stop(); 
          break;
      case RobotEvent::LEFT:
          robot.rotateLeft();
          break;
      case RobotEvent::RIGHT:
          robot.rotateRight();
          break;
      case RobotEvent::FORWARD:
        robot.moveForward();
        break;
      }
    }
  }
  t += dt;
}

void display() {
  checkEvents();
  robot.update(0.01f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  set2DMode(300, 300);
  glTranslatef(150, 150, 0);

  robot.render();
  path.render();

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
      if (!path.isLast()) {
        Point2d p = path.getNode();
        events.push(RobotEvent(RobotEvent::LEFT, t));
        events.push(RobotEvent(RobotEvent::STOP, t + 0.8f));
        events.push(RobotEvent(RobotEvent::FORWARD, t+ 0.9f));
        events.push(RobotEvent(RobotEvent::STOP, t + 1.8f));
        events.push(RobotEvent(RobotEvent::RIGHT, t + 2.0));
        events.push(RobotEvent(RobotEvent::STOP, t + 3.0f));
        events.push(RobotEvent(RobotEvent::FORWARD, t + 3.2f));
        events.push(RobotEvent(RobotEvent::STOP, t + 4.2f));
      }
      glutPostRedisplay();
      break;
    case 27:
      glutLeaveMainLoop();
      break;
    default:
      break;
  }
}

void setWorld() {}

void init_glut_window(int argc, char *argv[]) {
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
  // glewInit();
  setWorld();
  glutMainLoop();
}

int main(int argc, char **argv) {
  init_glut_window(argc, argv);
  return 0;
}
