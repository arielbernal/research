#ifndef GLPRIMITIVES_H
#define GLPRIMITIVES_H

#include <GL/freeglut.h>

void draw_axes(float width, float height)
{
  glColor3f(1, 0, 0);
  glBegin(GL_LINES);
  glVertex2f(-width / 2, 0 );
  glVertex2f(width / 2, 0);
  glColor3f(0, 0, 1);
  glVertex2f(0, height / 2);
  glVertex2f(0, -height / 2);
  glEnd();
}


void set2DMode(size_t Width, size_t Height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, Width, 0, Height);
}


void set3DMode(size_t Width, size_t Height) {
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(60.0, float(Width) / Height, 0.01f, 1000);
  gluLookAt(0, 0, 40, 0, 0, 0, 0.0, 1.0, 0.0);
}


void drawPoints(float x[], float y[], int n) {
  glBegin(GL_POINTS);
  for (int i = 0; i < n; i++)
    glVertex2f(x[i], y[i]);
  glEnd();
}


#endif





