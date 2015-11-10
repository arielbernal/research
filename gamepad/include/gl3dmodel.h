#ifndef GL3DMODEL_H
#define GL3DMODEL_H

#include <svector.h>
#include "glprimitives.h"

class GL3DModel {
public:
  GL3DModel(float Scale, bool DrawAxes = false, bool EnableLighting = false)
      : qCamera(0, 0, 0, 1), mouse_vx(0), mouse_vy(0), mouse_vz(-Scale),
        Scale(Scale), DrawAxes(DrawAxes), EnableLighting(EnableLighting) {}

  void enableLight() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    // ColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    GLfloat position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat diffuse[] = { 8.0f, 8.0f, 8.0f, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glPushMatrix();
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

  virtual void render3D(float Scale) = 0;

  void render(size_t width, size_t height) {
    set3DMode(width, height);
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

    if (DrawAxes)
      draw_axes_arrow(25, 25, 25, 0.05);
    if (EnableLighting)
      enableLight();

    render3D(Scale);
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
  float Scale;
  float mouse_dx;
  float mouse_dy;
  float mouse_vx;
  float mouse_vy;
  float mouse_vz;
  bool DrawAxes;
  bool EnableLighting;
};

#endif