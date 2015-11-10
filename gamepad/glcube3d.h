#ifndef GLCUBE3D_H
#define GLCUBE3D_H

#include <svector.h>
#include "include\gl3dmodel.h"

class GLCube3D : public GL3DModel {
public:
  GLCube3D (float Scale, bool DrawAxes = false, bool EnableLighting = false)
    : GL3DModel(Scale, DrawAxes, EnableLighting) {}


  float A[3][3][3];

  void render3D(float Scale) {
    float dcube = 20;
    glTranslatef(-dcube / 2, -dcube / 2, -dcube / 2);
    glColor3f(1, 0, 0);
    //drawWireframeCube(dcube, dcube, dcube);
    A[0][1][1] = 1;
    A[0][0][1] = 1;
    glColor3f(0, 1, 0);
    float gap = dcube / 480;
    float stride = dcube / 3;
    float dscube = stride - 2 * gap;
    for (size_t z = 0; z < 3; ++z){
      for (size_t y = 0; y < 3; ++y) {
        for (size_t x = 0; x < 3; ++x) {
          glPushMatrix();
          glTranslatef(x * stride + gap, y * stride + gap, z * stride + gap);
          glColor3f(0, 1, 0);
          drawWireframeCube(dscube, dscube, dscube);
          if (A[z][y][x] == 1) {
            glColor4f(1, 0, 0, 0.5f);
            drawCube(dscube, dscube, dscube);
          }
          glPopMatrix();

        }
      }
    }

     
  }
};

#endif