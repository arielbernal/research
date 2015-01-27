#ifndef GLPARTICLES_H
#define GLPARTICLES_H

#include <svector.h>
#include "glprimitives.h"
#include "particles.h"
#include "worldsystem.h"



void GLDrawObject(ConvexObject &obj) {
  std::vector<Triangle> &t = obj.getTriangles();
  glBegin(GL_TRIANGLES);
  int i = 0;
  for (ConvexObject::Iterator I = t.begin(), E = t.end(); I != E; ++I) {
    float4 v1 = I->p[1] - I->p[0];
    float4 v2 = I->p[2] - I->p[0];
    float4 n = normal3d(v1, v2);
    glNormal3f(n.x, n.y, n.z);
    glVertex3f(I->p[0].x, I->p[0].y, I->p[0].z);
    glNormal3f(n.x, n.y, n.z);
    glVertex3f(I->p[1].x, I->p[1].y, I->p[1].z);
    glNormal3f(n.x, n.y, n.z);
    glVertex3f(I->p[2].x, I->p[2].y, I->p[2].z);
     // std::cout <<i++<< " " << I->p[0].str()<< " " << I->p[1].str() << " " <<
     // I->p[2].str() << " " << n.str() << std::endl;
  }
  glEnd();
}

class GLParticleSystem {
 public:
  ParticleSystem *ps;
  TriangularPrismObject cube;
  CubeObject ground;
  TetrahedronObject tetra;

  GLParticleSystem(ParticleSystem *ps) : ps(ps) , ground(40, 40, 0.5f) {
    qCamera(0, 0, 0, 1);
    mouse_vx = 0;
    mouse_vy = 0;
    mouse_vz = -20;
	
    cube.scale(5);
    cube.rotateZ(3.1415/6*0);
    tetra.scale(5);
    tetra.translate(10, 10, 0);
    ground.translate(-20, -20, -0.5f);
    al = 0;
  }

  float al;

  void enableLight() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    GLfloat position[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat ambient[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glPushMatrix();
    glRotatef(al, 0, 0, 1);
    al += 1;
    if (al >= 360) al = 0;

    glTranslatef(50, 50, 3);
    glColor3f(1, 1, 1);
    glutSolidSphere(0.2, 20, 20);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(10, 10, 10);
    glColor3f(1, 1, 1);
    glutSolidSphere(0.2, 20, 20);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.3f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.02f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.008f);
    glPopMatrix();
  }

  void drawParticles() {
    glColor3f(1, 1, 1);
    glPointSize(3);
    glBegin(GL_POINTS);
    for (size_t i = 0; i < ps->getNumParticles(); ++i) {
      float4 x = ps->getParticlePosition(i);
      glVertex3f(x.x, x.y, x.z);
    }
    glEnd();
    glPointSize(1);
  }

  void draw() {

    // glClearColor(0.0f, 76 / 255.0f, 153 / 255.0f, 0.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glPushMatrix();
    glTranslatef(mouse_vx, -mouse_vy, mouse_vz);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    float pi = 3.14159265358;
    svector::float4 qNew(0, 0, 0, 1);
    qNew.euler(mouse_dy / 320.0f, mouse_dx / 320.0f, 0.0);
    qCamera.quaternion_mult(qNew);
    svector::float4 qAxis = qCamera.axis();
    glRotatef(qAxis.w / pi * 180, qAxis.x, qAxis.y, qAxis.z);
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);

    draw_axes_arrow(15, 15, 15, 0.08);
    drawParticles();

    enableLight();
    glColor3f(0.3f, 0.2f, 0.7f);
    GLDrawObject(cube);

    glColor3f(0.6f, 0.2f, 0.3f);
    GLDrawObject(tetra);


    glColor3f(0.3f, 0.5f, 0.4f);
    GLDrawObject(ground);

    glPopMatrix();
  }

  void mouse_button(int button, int status, int x, int y) {
    left_button_status = GLUT_UP;
    right_button_status = GLUT_UP;
    if ((button == 3) || (button == 4)) {
      if (status == GLUT_DOWN) {
        mouse_vz += button == 3 ? 0.9 : -0.9;
        if (mouse_vz > 20) mouse_vz = 10;
        if (mouse_vz < -100) mouse_vz = -100;
      }
    } else {
      if (button == GLUT_LEFT_BUTTON) {
        if (status == GLUT_DOWN) {
          left_button_status = GLUT_DOWN;
          left_button_down_x = x;
          left_button_down_y = y;
        }
      }
      if (button == GLUT_RIGHT_BUTTON) {
        if (status == GLUT_DOWN) {
          right_button_status = GLUT_DOWN;
          left_button_down_x = x;
          left_button_down_y = y;
        }
      }
    }
  }

  void mouse_active_motion(int x, int y) {
    if (left_button_status == GLUT_DOWN) {
      mouse_dx = (x - left_button_down_x);
      mouse_dy = (y - left_button_down_y);
      if (fabs(mouse_dx) < 2) mouse_dx = 0;
      if (fabs(mouse_dy) < 2) mouse_dy = 0;
    }
    if (right_button_status == GLUT_DOWN) {
      float dx = (x - left_button_down_x) / float(50);
      float dy = (y - left_button_down_y) / float(50);
      mouse_vy += dy;
      mouse_vx += dx;
    }

    left_button_down_x = x;
    left_button_down_y = y;
  }

  void mouse_passive_motion(int x, int y) {
    left_button_down_y = y;
    left_button_down_x = x;
  }

 private:
  svector::float4 qCamera;
  int left_button_status;
  int right_button_status;
  int left_button_down_x;
  int left_button_down_y;
  float mouse_dx;
  float mouse_dy;
  float mouse_vx;
  float mouse_vy;
  float mouse_vz;
};

#endif