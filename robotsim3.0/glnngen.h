#ifndef GLNNGEN_H
#define GLNNGEN_H

#include <svector.h>
#include "include/glprimitives.h"

class GLNGENNN {
public:
  GENNeuralNet *NN;

  GLNGENNN(GENNeuralNet *NN) : NN(NN) {
    qCamera(0, 0, 0, 1);
    mouse_vx = 0;
    mouse_vy = 0;
    mouse_vz = -20;
    al = 0;
  }

  float al;
  void enableLight() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    //ColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    GLfloat position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat diffuse[] = { 8.0f, 8.0f, 8.0f, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glPushMatrix();
    // glRotatef(al, 0, 0, 1);
    al += 1;
    if (al >= 360)
      al = 0;

    glTranslatef(20, 20, 40);
    glColor3f(1, 1, 1);
    glutSolidSphere(0.2, 20, 20);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-20, -20, 40);
    glColor3f(1, 1, 1);
    glutSolidSphere(0.2, 20, 20);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.01f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0008f);
    glPopMatrix();
  }

  void drawNN(float k) {
    glPushMatrix();
    glScalef(k, k, k);
    glColor4f(0.5, 0.0, 0.0, 1.0);
    // glutWireCube(1);
    glutWireSphere(1, 20, 20);
    // glTranslatef(-1 / 2.0, -1 / 2.0, -1 / 2.0);
    float rn = 0.015;
    float rnr = 0.016;
    std::vector<GENNeuron *> &Neurons = NN->getNeurons();
    for (auto &e : Neurons) {
      glPushMatrix();

      if (true || e->Ap > 0)
        for (auto &h : e->PosSynapses) {
          GENNeuron *p = h.second->PosNeuron;
          float khw = h.second->W / 10;
          glColor3f(khw, khw, khw);
          glBegin(GL_LINES);
          glVertex3f(e->x, e->y, e->z);
          glVertex3f(p->x, p->y, p->z);
          glEnd();
          if (e->nntype == GENNeuron::INPUT)
            glColor3f(1, 1, 0);
          if (e->nntype == GENNeuron::OUTPUT)
            glColor3f(0, 1, 1);
          if (e->nntype == GENNeuron::INHIBITORY)
            glColor3f(1, 0, 0);
          if (e->nntype == GENNeuron::EXCITATORY)
            glColor3f(0, 1, 0);

          glPushMatrix();
          svector::float4 v1(e->x, e->y, e->z);
          svector::float4 v2(p->x, p->y, p->z);
          svector::float4 d = v2 - v1;
          d.normalize();
          svector::float4 r = v2 - d * (rn + rn / 6);
          glTranslatef(r.x, r.y, r.z);
          glutSolidSphere(rn / 4, 6, 6);
          glPopMatrix();
        }

      float kc = 0.3f;
      if (e->Ap > 0)
        kc = 1.0f;
      if (e->nntype == GENNeuron::INPUT)
        glColor3f(kc, kc, 0);
      if (e->nntype == GENNeuron::OUTPUT)
        glColor3f(0, kc, kc);
      if (e->nntype == GENNeuron::INHIBITORY)
        glColor3f(kc, 0, 0);
      if (e->nntype == GENNeuron::EXCITATORY)
        glColor3f(0, kc, 0);

      glTranslatef(e->x, e->y, e->z);
      glutSolidSphere(rn, 9, 9);
      glColor4f(0, 0, 0, 1);
      glutWireSphere(rnr, 9, 9);

      // if (e->Ap > 0) {
      //   glColor4f(0.5, 0.3, 0.3, 0.5);
      //   glutWireSphere(0.04, 9, 9);
      // }
      glPopMatrix();
    }
    glPopMatrix();
  }

  void render() {
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

//    glDisable(GL_LIGHTING);
//    draw_axes_arrow(25, 25, 25, 0.05);

//     enableLight();
    // glTranslatef(-10, -10, -10);
    drawNN(20);

    glPopMatrix();
  }

  void mouse_button(int button, int status, int x, int y) {
    left_button_status = GLUT_UP;
    right_button_status = GLUT_UP;
    if ((button == 3) || (button == 4)) {
      if (status == GLUT_DOWN) {
        mouse_vz += button == 3 ? 0.9 : -0.9;
        if (mouse_vz > 40)
          mouse_vz = 30;
        if (mouse_vz < -200)
          mouse_vz = -200;
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
      if (fabs(mouse_dx) < 2)
        mouse_dx = 0;
      if (fabs(mouse_dy) < 2)
        mouse_dy = 0;
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