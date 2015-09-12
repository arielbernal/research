#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>
#include "include/glheaders.h"
#include "include/glprimitives.h"
#include "robot_unit.h"
#include "track.h"
#include "ga.h"


namespace {
int WinWidth = 1200;
int WinHeight = 1000;
float WinRatio = WinHeight / float(WinWidth);
float ViewWidth = 10 ;
float ViewHeight = ViewWidth * WinRatio;
float ViewX0 = ViewWidth / 2;
float ViewY0 = ViewHeight / 2;
std::string WinTitle = "RobotSim";
GA ga(1000);
std::vector<Track> tracks;
size_t itrack = 0;
}

void set2DMode(float Width, float Height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, Width, 0, Height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

float MouseX, MouseY;
bool MouseButtonRight;
float Angle = 0;
float Speed = 0;

void drawRect(float angle) {
  glPushMatrix();
  glRotatef(angle, 0, 0, 1);
  glBegin(GL_QUADS);
  glColor3f(1, 0, 0);
  glVertex2d(-1, -1);
  glColor3f(0, 1, 0);
  glVertex2d(1, -1);
  glColor3f(0, 0, 1);
  glVertex2d(1, 1);
  glColor3f(1, 1, 0);
  glVertex2d(-1, 1);
  glEnd();
  glPopMatrix();
}


void makeCircle(float x, float y, float r) {
  glPushMatrix();
  glTranslatef(x, y, 0);

  glBegin(GL_LINES);
  //.......

  glEnd();
  glPopMatrix();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  set2DMode(ViewWidth, ViewHeight);
  glTranslatef(ViewX0, ViewY0 ,0);
  draw_axes(50, 50, 0);
  
  Angle += Speed;
  if (Angle > 360)  Angle = Angle - 360;

  //drawRect(0);
  //drawRect(Angle);
  
  makeCircle(3, 3, 2);
 

 
  //ga.render();
  //tracks[itrack].render();
  //float t = ga.getTime();
  //set2DMode(1000, 1000);
  /*printFloat(5, 1000 - 20, "ViewWidth = ",ViewWidth, 3, 2);
  printFloat(5, 1000 - 40, "Time = ", ga.getTime(), 3, 2);
  printFloat(100, 1000 - 40, "dt = ", ga.getDt(), 3, 2);
  Sleep(33);*/
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
  WinWidth = w;
  WinHeight = h;
  WinRatio = WinHeight / float(WinWidth);

  float kx = ViewX0 / ViewWidth;
  float ky = ViewY0 / ViewHeight;
  ViewHeight = ViewWidth * WinRatio;
  ViewX0 = kx * ViewWidth;
  ViewY0 = ky * ViewHeight;

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  init_display();
  display();
}


void mouse_wheel(int wheel, int direction, int x, int y) {
  y = WinHeight - y;
  float k = ViewWidth / WinWidth;
  float xp = x * k - ViewX0;
  float yp = y * k - ViewY0;
  float factor = 1.3;
  float ViewZoom = direction > 0 ? factor : 1 / factor;
  ViewWidth *= ViewZoom;
  ViewHeight *= ViewZoom;
  k = ViewWidth / WinWidth;
  ViewX0 = x * k - xp;
  ViewY0 = y * k - yp;
}

void mouse_button(int button, int status, int x, int y) {
#ifndef WIN32
  if ((button == 3) || (button == 4)) {
    mouse_wheel(0, button == 3 ? 1 : -1, x, y);
  }
#endif  
  y = WinHeight - y;
  MouseButtonRight = false;
  if (button == GLUT_RIGHT_BUTTON){
    if (status == GLUT_DOWN){
      MouseButtonRight = true;
      MouseX = x;
      MouseY = y;
    }
  }
}

void mouse_active_motion(int x, int y) {
  y = WinHeight - y;
  if (MouseButtonRight){
    float k = ViewWidth / WinWidth;
    ViewX0 += (x - MouseX) * k;
    ViewY0 += (y - MouseY) * k;
  }
  MouseX = x;
  MouseY = y;
}

void mouse_passive_motion(int x, int y) {
  y = WinHeight - y;
}

void special_keys(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      ga.slowDown(-1);
      break;
    case GLUT_KEY_DOWN:
      ga.slowDown(+1);
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
      itrack = (itrack + 1) % tracks.size();
      ga.setTrack(&tracks[itrack]);
      break;
    case 's':
      ga.saveMostFit("nn/best01.nn");
      break;
    case 'l':
      ga.loadMostFit("nn/best01.nn");
      break;
    case 't':
      ga.stopSimulation();
      break;
    case 32:
      ga.startSimulation(500, 0.08f);
      break;
    case 27:
      glutLeaveMainLoop();
      break;
    case 'f':
      Speed += 0.1;
      break;
    case 'd':
      Speed = Speed - 0.1;
      break;
    default:
      break;
  }
}


void init_glut_window(int argc, char* argv[]) {
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

  Maze a(8, 8);
  tracks.resize(7);
  tracks[0].load("tracks/track1.trk");
  tracks[1].load("tracks/track2.trk");
  tracks[2].load("tracks/track3.trk");
  tracks[3].load("tracks/track4.trk");
  tracks[4].getEdgesFromMaze(a, 25);
  a.generate(8, 8);
  tracks[5].getEdgesFromMaze(a, 25);
  a.generate(15, 15);
  tracks[6].getEdgesFromMaze(a, 25);

  ga.setTrack(&tracks[0]);

  glutMainLoop();
}

int main(int argc, char** argv) {
  init_glut_window(argc, argv);
  return 0;
}