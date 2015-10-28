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
      : GL2DModel(ViewWidth, WinWidth, WinHeight), NN(NN) {}

  void drawNeuron(float x, float y, float r, GENNeuron* e) {
    float4 color;
    if (e->nntype == GENNeuron::EXCITATORY) color(0, 1, 0, 1);
    if (e->nntype == GENNeuron::INHIBITORY) color(1, 0.1, 0, 1);
    if (e->nntype == GENNeuron::OUTPUT) color(0, 0.4, 1, 1);
    if (e->nntype == GENNeuron::INPUT) color(1, 1, 0, 1);
    if (e->Ap < 1) color *= 0.6;
    setColor(color);
    drawDisk(x, y, r, 10);
    printText(x, y - 5 * r, format("ID=%d", e->id));
    printText(x, y - 4 * r, format("v[0]=%4.2f", e->v[0]));
    printText(x, y - 3 * r, format("v[1]=%4.2f", e->v[1]));
    printText(x, y - 2 * r, format("v[2]=%4.2f", e->v[2]));
  }

  void render() {
    float dr = 40;
    float r = 3;
    float y = 0;
    float x = 0;
    for (auto &e : NN->getInputs()) {
      drawNeuron(x, y, r, e);  
      y += dr;
    }
    x += dr;
    y = 0;
    for (auto &e : NN->getHidden()) {
      drawNeuron(x, y, r, e);      
      y += dr;
    }
    x += dr;
    y = 0;
    for (auto &e : NN->getOutputs()) {
      drawNeuron(x, y, r, e);      
      y += dr;
    }

  }

  void mouse_button(int button, int status, int x, int y) {
    GL2DModel::mouse_button(button, status, x, y);
  }

};

#endif