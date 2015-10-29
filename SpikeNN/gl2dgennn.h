#ifndef GL2DGENNN_H
#define GL2DGENNN_H

#include <svector.h>
#include "include/glprimitives.h"
#include "include/gl2dmodel.h"
#include "nngen.h"

using namespace svector;

class GL2DGENNN : public GL2DModel {
public:
  GENNeuralNet *NN;

  GL2DGENNN(GENNeuralNet *NN, float ViewWidth = 100, int WinWidth = 1200,
            int WinHeight = 1000)
      : GL2DModel(ViewWidth, WinWidth, WinHeight), NN(NN),
        NeuronPos(NN->getNNeurons()) {
    for (auto &e : NN->getNeurons()) {
      bool notFound = true;
      while (notFound) {
        float x = rand() / float(RAND_MAX) * 200;
        float y = rand() / float(RAND_MAX) * 200;
        float4 p(x, y, 0, 0);
        notFound = false;
        for (size_t i = 0; i < NeuronPos.size(); ++i)
          if (i != e->id && distance(NeuronPos[i], p) < 100)
            notFound = true;
        if (!notFound)
          NeuronPos[e->id](x, y, 0, 0);
      }
    }
  }

  void drawSynapse(GENSynapse *S) {
    float4 pPre = NeuronPos[S->PreNeuron->id];
    float4 pPos = NeuronPos[S->PosNeuron->id];
    float4 pMed = pPos - (pPos - pPre) / 8.0f;
    glBegin(GL_LINES);
    glVertex2f(pPre.x, pPre.y);
    glVertex2f(pPos.x, pPos.y);
    glEnd();
    printText(pMed.x, pMed.y,
              format("W%d%d=%4.3f", S->PreNeuron->id, S->PosNeuron->id, S->W));
  }

  void drawNeuron(float x, float y, float r, GENNeuron *N) {
    float4 color;
    if (N->nntype == GENNeuron::EXCITATORY)
      color(0, 1, 0, 1);
    if (N->nntype == GENNeuron::INHIBITORY)
      color(1, 0.1, 0, 1);
    if (N->nntype == GENNeuron::OUTPUT)
      color(0, 0.4, 1, 1);
    if (N->nntype == GENNeuron::INPUT)
      color(1, 1, 0, 1);
    setColor(color);
    float xt = x - 8 * r;

    printText(xt, y - 6 * r, format("ID=%d", N->id));
    printText(xt, y - 5 * r, format("v[0]=%4.2f", N->v[0]));
    printText(xt, y - 4 * r, format("v[1]=%4.2f", N->v[1]));
    printText(xt, y - 3 * r, format("v[2]=%4.2f", N->v[2]));
    printText(xt, y - 2 * r, format("NS=%d", N->PosSynapses.size()));
    for (auto &e : N->PosSynapses) {
      drawSynapse(e.second);
    }
    if (N->Ap < 1)
      color *= 0.6;
    setColor(color);

    drawDisk(x, y, r, 10);
  }

  void render() {
    glTranslatef(-50, -50, 0);
    float dr = 60;
    float r = 3;
    float y = 0;
    float x = 0;

    for (auto &e : NN->getNeurons()) {
      x = NeuronPos[e->id].x;
      y = NeuronPos[e->id].y;
      drawNeuron(x, y, r, e);
    }
    // for (auto &e : NN->getInputs()) {
    //   drawNeuron(x, y, r, e);
    //   NeuronPos[e->id](x, y, 0, 0);
    //   y += dr;
    // }
    // x += dr;
    // y = 0;
    // for (auto &e : NN->getHidden()) {
    //   drawNeuron(x, y, r, e);
    //   NeuronPos[e->id](x, y, 0, 0);
    //   y += dr;
    // }
    // x += dr;
    // y = 0;
    // for (auto &e : NN->getOutputs()) {
    //   drawNeuron(x, y, r, e);
    //   NeuronPos[e->id](x, y, 0, 0);
    //   y += dr;
    // }
  }

  void mouse_button(int button, int status, int x, int y) {
    GL2DModel::mouse_button(button, status, x, y);
  }

  std::vector<float4> NeuronPos;
};

#endif