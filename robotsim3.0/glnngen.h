#ifndef GLNNGEN_H
#define GLNNGEN_H

#include <svector.h>
#include "include/glprimitives.h"
#include "include/gl3dmodel.h"

class GLNGENNN : public GL3DModel {
public:
  GENNeuralNet *NN;

  GLNGENNN(GENNeuralNet *NN) : GL3DModel(20), NN(NN) {
  }

  void render3D(float k) {
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
          float khw = h.second->W / (0.5f * 10 * 0.5f);
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
};

#endif