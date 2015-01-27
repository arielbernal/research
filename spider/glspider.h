#ifndef GLSPIDER_H
#define GLSPIDER_H


#include <svector.h>
#include <glprimitives.h>
#include "spider.h"


#define PI 3.14159265358


class GLSpider {
 public:
  Spider *sp;
  float t;
  size_t ik;

  GLSpider(Spider *spider) {
    qCamera(0,0,0,1);
    mouse_vx = 0;
    mouse_vy = -10;
    mouse_vz = -20;
    t = 0;
    ik = 0;
    //kw = 500;
    sp = spider;
  }

  // int k2d[300000];
  // int kw;
  // void checkAngles() {
  //   float x0, y0, z0;
  //   x0 = sp.x[0]; y0 = sp.y[0]; z0 = sp.z[0];

  //   for (int u = 0; u < kw; ++u) {
  //     for (int z = 0; z < kw; ++z) {
  //       float zz = -30 + float(z) / kw * 60;
  //       float uu = 0 + float(u) / kw * 30;
  //       if(!sp.moveLegTo(0, uu, uu, zz))
  //         k2d[z * kw + u] = 0;
  //       else 
  //         k2d[z * kw + u] = 1;
  //     }
  //   }

  //   sp.moveLegTo(0, x0, y0, z0);
  //   sp.printAngles(0);
  // }
  // void drawAngles() {
  //   glDisable(GL_LIGHTING);
  //   glClearColor(0.0f, 76/255.0f, 153/255.0f, 0.0f);
  //   glEnable(GL_DEPTH_TEST);
  //   glDepthFunc(GL_LESS);

  //   glColor4f(0.3, 0.2, 0.8, 0.8);
  //   glBegin(GL_POINTS);
  //   for (int u = 0; u < kw; ++u) {
  //     for (int z = 0; z < kw; ++z) {        
  //       if (!k2d[z * kw + u])
  //         glColor4f(1, 0, 0, 0.5);
  //       else
  //         glColor4f(0, 1, 0, 0.5);
  //       if (u == kw / 2 && z == kw / 2) glColor4f(0, 0, 1, 1);
  //       glVertex2f(u, z);
  //     }
  //   }
  //   glEnd();
  // }

  // void update(float dt) {
  //   sp.pwm->update(dt);
  // }

  void drawBody() {
//    update(0.001);
    glPushMatrix();
    glTranslatef(0, 0, 0);
//    glRotatef(90, 1, 0, 0);
    glColor4f(0.3, 0.2, 0.8, 1.0);

    vec4 *coxa = sp->coxa;
    glBegin(GL_QUADS);
    glNormal3f(0.f, 1, 0.f);
    glVertex3f(coxa[0].x, coxa[0].y, coxa[0].z);
    glVertex3f(coxa[2].x, coxa[2].y, coxa[2].z);
    glVertex3f(coxa[3].x, coxa[3].y, coxa[3].z);
    glVertex3f(coxa[1].x, coxa[1].y, coxa[1].z);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(coxa[0].x , coxa[0].y, coxa[0].z);
    glVertex3f((coxa[0].x + coxa[1].x) / 2, 1.2f *coxa[0].y, (coxa[0].z + coxa[1].z) / 2);
    glVertex3f(coxa[1].x , coxa[1].y, coxa[1].z);
    glEnd();

    // for (int i = 0; i < 4; ++i) {
    //   glPushMatrix();

    //   float gamma = sp->pwm->getAngle(3 * i);
    //   float alpha = sp->pwm->getAngle(3 * i + 1);
    //   float beta = sp->pwm->getAngle(3 * i + 2);

    //   glTranslatef(coxa[i].x, coxa[i].y, coxa[i].z);
    //   glRotatef(coxa[i].w, 0, 0, 1);

    //   glRotatef(gamma, 0, 0, 1);
    //   glColor3f(1, 0, 0);
    //   glBegin(GL_QUADS);
    //   float dcoxa = sp->lcoxa / 20;
    //   glVertex3f(0, -dcoxa, 0);
    //   glVertex3f(sp->lcoxa, -dcoxa, 0);
    //   glVertex3f(sp->lcoxa, dcoxa, 0);
    //   glVertex3f(0, dcoxa, 0);
    //   glEnd();

    //   glTranslatef(sp.coxa, 0, 0);
    //   glRotatef(-alpha, 0, 1, 0);
    //   glColor3f(0, 1, 0);
    //   glBegin(GL_LINES);
    //   glVertex3f(0, 0, 0);
    //   glVertex3f(sp.femur, 0, 0);
    //   glEnd();

    //   glTranslatef(sp.femur, 0, 0);
    //   glRotatef(-beta, 0, 1, 0);
    //   glColor3f(0, 1, 0);
    //   glBegin(GL_LINES);
    //   glVertex3f(0, 0, 0);
    //   glVertex3f(sp.tibia, 0, 0);
    //   glEnd();

    //   glPopMatrix();
    // }

    // glColor3f(1, 0, 0);
    // glBegin(GL_QUADS);
    // glVertex3f(sp.x[0], sp.y[0], sp.z[0]);
    // glVertex3f(sp.x[2], sp.y[2], sp.z[2]);
    // glVertex3f(sp.x[3], sp.y[3], sp.z[3]);
    // glVertex3f(sp.x[1], sp.y[1], sp.z[1]);
    // glEnd();


    glPopMatrix();
  }


  void enableLight() {
    glPushMatrix();
    glTranslatef(0, 20, 20);
    glColor3f(1, 1, 1);
    glutSolidSphere(0.2, 20, 20);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    GLfloat position[] = {0, 0, 0, 1.0f};
    GLfloat ambient[] = { 0.3, 0.3, 0.3, 1.0f };
     //GLfloat diffuse[] = { 0.1, 0.1, 0.1, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);    
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 20, -20);
    glutSolidSphere(0.2, 20, 20);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    
    glPopMatrix();
  }


  void draw() {
    glClearColor(0.0f, 76/255.0f, 153/255.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glPushMatrix();
    glTranslatef(mouse_vx, -mouse_vy, mouse_vz);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    enableLight();    

    float pi = 3.14159265358;
    svector::float4 qNew(0,0,0,1);
    qNew.euler(mouse_dy / 320, mouse_dx / 320, 0.0);
  
    qCamera.quaternion_mult(qNew);
    svector::float4 qAxis = qCamera.axis();
    glRotatef(qAxis.w / pi * 180, qAxis.x, qAxis.y, qAxis.z);

    draw_axes_arrow(15, 15, 15, 0.1);

    drawBody();

    //glTranslatef(0, 0, 0);
//    glColor4f(0.8f, 0.8f, 0.4f, 1.0f); 
    // glBegin(GL_QUADS);
    // /* floor */
    // glNormal3f(0.f, 1, 0.f);
    // glVertex3f(-100.f, -10.1f, -100.f);
    // glVertex3f(-100.f, -10.1f, 100.f);
    // glVertex3f(100.f,  -10.1f, 100.f);
    // glVertex3f(100.f,  -10.1f, -100.f);
    // glEnd();

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

#endif  // GLSPIDER_H