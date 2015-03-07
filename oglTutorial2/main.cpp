#include <iostream>
#include <cmath>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glprimitives.h"
 


struct Point {
  float x, y;
  float x0, y0;
  float vx, vy;
};

const int N = 1000;
Point p[N];
float t = 0;

void fillPoints(Point A[], int n) {  
  float rmax = 20;
  float vmax = 10;
  for (int i = 0; i < n ; i++) {
    float x, y, r;
    do {
      x = rand() / float(RAND_MAX) * 2.0 * rmax - rmax;
      y = rand() / float(RAND_MAX) * 2.0 * rmax - rmax;
      r = sqrt(x * x + y * y);
    } while (r > rmax);
    p[i].x0 = x + 500;
    p[i].y0 = y + 500;

    float vx, vy, vr;
    do {
      vx = rand() / float(RAND_MAX) * vmax - vmax / 2;
      vy = rand() / float(RAND_MAX) * vmax - vmax / 2;
      vx = (rand() %3 - 1.0f) * vmax - vmax / 2;
      vy = (rand() %3 - 1.0f) * vmax - vmax / 2;
      //printf("%d\n", rand() % 3);

      vr = sqrt(vx * vx + vy * vy);
    } while (vr > vmax);
    //vx = (rand() %3 - 1.0f) * vmax - vmax / 2;
    //vy = (rand() %3 - 1.0f) * vmax - vmax / 2;
    p[i].vx = vx;
    p[i].vy = vy;
  } 
}

void calcPos(Point p[], int n, float t){
  for (int i = 0; i < n; i++) {
    p[i].x = p[i].x0 + p[i].vx * t;
    p[i].y = p[i].y0 + p[i].vy * t;
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  calcPos(p, N, t);
  t = t + 0.1;

  glColor3f(1, 1, 1);
  glBegin(GL_POINTS);
  for (int i = 0; i < N; i++) {
    glVertex2f(p[i].x, p[i].y);
  }
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
  glutIdleFunc(display);
  glutKeyboardFunc(normal_keys);
  glutReshapeFunc(reshape);

  fillPoints(p, N);
  glutMainLoop();
  return 0;
}