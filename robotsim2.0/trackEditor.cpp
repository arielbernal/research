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
std::string m_window_title = "TrackEditor";
RobotGA robot(5);
Track track;
enum { MODE_NONE, MODE_EDGE, MODE_LANDMARK };
int editMode = MODE_NONE;
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



float mousex, mousey;
int rmouseb, lmouseb;

bool newEdgeP0 = false;
Edge2d newEdge;
Point2d newPoint;

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
  lmouseb = GLUT_UP;
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
  if (button == GLUT_LEFT_BUTTON) {
    if (status == GLUT_DOWN) {
      lmouseb = GLUT_DOWN;
      mousex = x;
      mousey = y;
      if (editMode == MODE_EDGE) {
        if (!newEdgeP0) {
          newEdge.p0.x = x / 1000.0f * mouse_vz - mouse_vx;
          newEdge.p0.y = y / 1000.0f * mouse_vz - mouse_vy;
          newEdgeP0 = true;
        } else {
          newEdge.p1.x = x / 1000.0f * mouse_vz - mouse_vx;
          newEdge.p1.y = y / 1000.0f * mouse_vz - mouse_vy;
          track.addEdge(newEdge);
          newEdgeP0 = false;
          editMode = MODE_NONE;
        }
      }
      if (editMode == MODE_LANDMARK) {
        newPoint.x = x / 1000.0f * mouse_vz - mouse_vx;
        newPoint.y = y / 1000.0f * mouse_vz - mouse_vy;
        track.addLandmark(newPoint);
        editMode = MODE_NONE;
      }
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



void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  set2DMode(mouse_vz, mouse_vz);
  glTranslatef(mouse_vx, mouse_vy, 0);
  robot.render();
  track.render();
  
  if (editMode == MODE_EDGE && newEdgeP0) {
    float xp = mousex / 1000.0f * mouse_vz - mouse_vx;
    float yp = mousey / 1000.0f * mouse_vz - mouse_vy;
    glColor3f(0, 0.5, 0.5);
    glBegin(GL_LINES);
    glVertex2f(newEdge.p0.x, newEdge.p0.y);
    glVertex2f(xp, yp);
    glEnd();
  }

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
    case '1': {
      std::cout << "Edge Mode Selected" << std::endl;
      editMode = MODE_EDGE;
      break;
    }
    case '2': {
      std::cout << "Landmark Mode Selected" << std::endl;
      editMode = MODE_LANDMARK;
      break;
    }
    case 'a':
      break;
    case 's':
      track.save("tracks/track3.trk");
      break;
    case 'l':
      track.load("tracks/track3.trk");
      break;      
    case 32:
      break;
    case 27: {
      if (editMode == MODE_NONE)  glutLeaveMainLoop();
      if (editMode == MODE_EDGE) { 
        std::cout << "Edge Mode Cancelled" << std::endl;
        editMode = MODE_NONE;
        newEdgeP0 = false;
      }
      if (editMode == MODE_LANDMARK) { 
        std::cout << "Landmark Mode Cancelled" << std::endl;
        editMode = MODE_NONE;
      }      
      break;
    }
    default:
      break;
  }
  glutPostRedisplay();
}

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

  robot.setPos(Point2d(0, 0), 0);

  glutMainLoop();
}

int main(int argc, char** argv) {
  init_glut_window(argc, argv);
  return 0;
}

