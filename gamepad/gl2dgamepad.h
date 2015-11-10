#ifndef GL2DGamePad_H
#define GL2DGamePad_H

#include <svector.h>
#include "include/glprimitives.h"
#include "include/gl2dmodel.h"

using namespace svector;

class GL2DGamePad : public GL2DModel {
public:
  GL2DGamePad(float ViewWidth = 100, int WinWidth = 1200,
    int WinHeight = 1000)
    : GL2DModel(ViewWidth, WinWidth, WinHeight) {}


  void render() {
    glTranslatef(-50, -50, 0);
    glColor3f(1, 1, 1);
    drawDisk(0, 0, 100, 10);
  }

  void mouse_button(int button, int status, int x, int y) {
    GL2DModel::mouse_button(button, status, x, y);
  }

};

#endif