#include <iostream>
#include <glheaders.h>
#include <cmath>
#include "spider.h"
#include "glspider.h"

#define PI 3.14159265358



namespace {
int m_window_width = 1000;
int m_window_height = 1000;
std::string m_window_title = "SpiderQuad";
Spider sp;
GLSpider glspider(&sp);
}

void projection2d(int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, w, 0, h, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_BLEND);
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
  gluLookAt(0, 0, 40, 0, 0, 0, 0.0, 1.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}



void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  int viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  int width = viewport[2];
  int height = viewport[3];
  set3DMode(width, height);
  glspider.draw();
  // set2DMode(width, height);
  // glspider.drawAngles();
  // projection2d(width, height);
  // glPushMatrix();
  // glTranslatef(width / 2, height / 2, 0);
  // Spider.draw();
  // glPopMatrix();
  glutSwapBuffers();
}

void init_display() {
  glspider.enableLight();
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, w, h, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
  display();
}

void mouse_wheel(int wheel, int direction, int x, int y) {}

void mouse_button(int button, int state, int x, int y) {
  glspider.mouse_button(button, state, x, y);
}

void mouse_active_motion(int x, int y) {
  glspider.mouse_active_motion(x, y);
}

void mouse_passive_motion(int x, int y) {
  glspider.mouse_passive_motion(x, y);
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
    default:
      break;
  }
}

int ii;
void normal_keys(unsigned char key, int x, int y) {
  switch (key) {
    case 'q':
      sp.rotate(1, 0, 0);
      break;
    case 'w':
      sp.rotate(-1, 0, 0);
      break;      
    case 'a':
      sp.rotate(0, 1, 0);
      break;
    case 's':
      sp.rotate(0, -1, 0);
      break;        
    case 'z':
      sp.rotate(0, 0, 1);
      break;
    case 'x':
      sp.rotate(0, 0, -1);
      break;                
    case '6':
      sp.translate(1, 0, 0);
      break;      
    case '4':
      sp.translate(-1, 0, 0);
      break;
    case '8':
      sp.translate(0, 1, 0);
      break;
    case '2':
      sp.translate(0, -1, 0);
      break;      
    case '+':
      sp.translate(0, 0, 1);
      break;
    case '-':
      sp.translate(0, 0, -1);
      break;      
    case 'c':
      ii = 0;
      sp.initPos();
      break;            
    case 'v': {
      float kt = 3; 
      float kl = 3 * kt / 2;
      float kz = 3;
      switch(ii) {
      case 0: sp.translate(0, kt, 0); ii++; break;
      case 1: sp.moveLeg(2, 0, kl, kz); ii++; break;
      case 2: sp.moveLeg(2, 0, kl, -kz); ii++; break;
      case 3: sp.moveLeg(0, 0, kl, kz); ii++; break;
      case 4: sp.moveLeg(0, 0, kl, -kz); ii++; break;
      case 5: sp.translate(0, kt, 0); ii++; break;
      case 6: sp.moveLeg(3, 0, kl, kz); ii++; break;
      case 7: sp.moveLeg(3, 0, kl, -kz); ii++; break;
      case 8: sp.moveLeg(1, 0, kl, kz); ii++; break;      
      case 9: sp.moveLeg(1, 0, kl, -kz); ii++; break;      
      case 10: sp.translate(0, kt, 0); ii++; break;
      }
      if (ii>10) ii = 0;
      break;   
      }         
    case 'b':
      sp.moveLeg(0, 0, 0, -1);
      break;
    case 'p':
      //checkAngles();
      break;
    case 'h':
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
  ii = 0;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(2800, 100);
  glutInitWindowSize(m_window_width, m_window_height);
  glutCreateWindow(m_window_title.c_str());

  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutKeyboardFunc(normal_keys);
  glutSpecialFunc(special_keys);
  glutMouseFunc(mouse_button);
  glutMotionFunc(mouse_active_motion);
  glutPassiveMotionFunc(mouse_passive_motion);
  //glutMouseWheelFunc(mouse_wheel);
  glutReshapeFunc(reshape);
  glewInit();
  init_display();
  glutMainLoop();
}

int main(int argc, char** argv) {
  init_glut_window(argc, argv);
  return 0;
}
