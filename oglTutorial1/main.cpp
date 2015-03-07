#include <iostream>
#include <cmath>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glprimitives.h"

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(1, 1, 1);
  glBegin(GL_POINTS);
  glVertex2f(100, 100);
  glEnd();
    
  glutSwapBuffers();
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glClearColor(0, 0, 0.4, 1);
  set2DMode(w, h);
}

void normal_keys(unsigned char key, int x, int y) {
  switch (key) {     
    case 27:
      glutLeaveMainLoop();
      break;
    default:
      break;
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(1800, 10);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("Everything Is Awesome");

  glutDisplayFunc(display);
  //glutIdleFunc(display);
  glutKeyboardFunc(normal_keys);
  glutReshapeFunc(reshape);

  glutMainLoop();
  return 0;
}