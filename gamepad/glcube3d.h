#ifndef GLCUBE3D_H
#define GLCUBE3D_H

#include <svector.h>
#include "include/glheaders.h"
#include "include/gl3dmodel.h"
#include <GL/glu.h>

using namespace svector;

bool CheckLineBox(float4& B1, float4& B2, float4& L1, float4& L2, float4& Hit);

struct SmallCube {
  float4 p0;
  float4 p1;
  float type;
};

class GLCube3D : public GL3DModel {
public:
  GLCube3D(float Scale, bool DrawAxes = false, bool EnableLighting = false)
    : GL3DModel(Scale, DrawAxes, EnableLighting) {


    float f1[27] = {
      2, 2, 4,
      2, 1, 4,
      2, 1, 4,
      6, 5, 5,
      1, 1, 4,
      2, 3, 3,
      6, 6, 5,
      6, 3, 5,
      6, 3, 5
    };
    float f2[27] = { // // 5 5 5 5 4 3  
      1, 3, 3,
      1, 1, 3,
      2, 2, 2,
      3, 3, 4,
      5, 1, 4,
      2, 1, 2,
      4, 4, 4,
      5, 5, 6,
      5, 6, 6
    };
    float f3[27] = { // 6 6 6 5 4 
      2, 2, 2,
      2, 1, 1,
      4, 4, 1,
      5, 1, 2,
      2, 1, 4,
      3, 4, 4,
      5, 5, 5,
      3, 3, 3,
      3, 4, 3
  };

   loadMatrix(f3);


    frame[0] = float4(0.3, 0.3, 0.3, 1);
    frame[1] = float4(1, 0, 0, 1);
    frame[2] = float4(0, 1, 0, 1);
    frame[3] = float4(0, 0, 1, 1);
    frame[4] = float4(1, 1, 0, 1);
    frame[5] = float4(0, 1, 1, 1);
    frame[6] = float4(1, 0, 1, 1);
    frame[7] = float4(0.64, 0.46, 0.16, 1);

    alpha = 0.9;
    color[0] = float4(0.3, 0.3, 0.3, 1);
    color[1] = float4(1, 0, 0, alpha);
    color[2] = float4(0, 1, 0, alpha);
    color[3] = float4(0, 0, 1, alpha);
    color[4] = float4(1, 1, 0, alpha);
    color[5] = float4(0, 1, 1, alpha);
    color[6] = float4(1, 0, 1, alpha);
    color[7] = float4(0.64, 0.46, 0.16, alpha);

    createCubes(20);
    onlyOne = -1;
  }

  void loadMatrix(float* f) {
    size_t i = 0;
    for (size_t z = 0; z < 3; ++z) {
      for (size_t y = 0; y < 3; ++y) {
        for (size_t x = 0; x < 3; ++x) {
          cubes[z][y][x].type = f[i++];
        }
      }
    }
  }

  void createCubes(float dcube) {
    float gap = dcube / 480 * 2;
    float stride = dcube / 3;
    float dscube = stride - 2 * gap;
    for (size_t z = 0; z < 3; ++z) {
      for (size_t y = 0; y < 3; ++y) {
        for (size_t x = 0; x < 3; ++x) {
          cubes[z][y][x].p0 =
              float4(x * stride + gap, y * stride + gap, z * stride + gap);
          cubes[z][y][x].p1 =
              cubes[z][y][x].p0 + float4(dscube, dscube, dscube);
        }
      }
    }
  }

  void drawCubeTransparent(SmallCube &c, float4& color, float4& frame) {
    glPushMatrix();
    glTranslatef(c.p0.x, c.p0.y, c.p0.z);
    float4 d = c.p1 - c.p0;
    glColor4f(frame.x, frame.y, frame.z, frame.w);
    glLineWidth(3);
    drawWireframeCube(d.x, d.y, d.z);
    glColor4f(color.x, color.y, color.z, color.w);
    glLineWidth(1);
    //
  //  glDepthMask(GL_FALSE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);


    glTranslatef(d.x / 2, d.x / 2, d.x / 2);
    glutSolidCube(d.x);

    //drawCube(d.x, d.y, d.z);
    glCullFace(GL_BACK);
    //drawCube(d.x, d.y, d.z);

    glutSolidCube(d.x);

//    glDepthMask(GL_TRUE);
    glDisable(GL_CULL_FACE);

    glPopMatrix();
  }

  void render3D(float Scale) {
    glScalef(Scale, Scale, Scale);
    float dcube = 20;
    glTranslatef(-dcube / 2, -dcube / 2, -dcube / 2);
    float stride = dcube / 3;
    for (size_t z = 0; z < 3; ++z) {
      for (size_t y = 0; y < 3; ++y) {
        for (size_t x = 0; x < 3; ++x) {
          size_t st = cubes[z][y][x].type;

          if (st == 0) {
            glPushMatrix();
            glTranslatef(x * stride, y * stride, z * stride);
            glColor4f(frame[0].x, frame[0].y, frame[0].z, frame[0].w);
            drawWireframeCube(dcube / 3, dcube / 3, dcube / 3);
            glPopMatrix();
          }
        }
      }
    }
    for (size_t z = 0; z < 3; ++z) {
      for (size_t y = 0; y < 3; ++y) {
        for (size_t x = 0; x < 3; ++x) {
          size_t st = cubes[z][y][x].type;
          if (st != 0) {
            if (onlyOne > 0) {
              if (st == onlyOne)
                drawCubeTransparent(cubes[z][y][x], color[st], frame[st]);
            }
            else 
              drawCubeTransparent(cubes[z][y][x], color[st], frame[st]);
          }
        }
      }
    }
    glGetDoublev(GL_MODELVIEW_MATRIX, modelViewMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, porjectionMatrix);
    glGetIntegerv(GL_VIEWPORT, viewport);
  }

  void mouse_button(int button, int status, int x, int y) {
    GL3DModel::mouse_button(button, status, x, y);
    if (button == GLUT_MIDDLE_BUTTON) {
      if (status == GLUT_DOWN) {
        y = WinHeight - y;
        double x1, y1, z1;
        double x2, y2, z2;
        gluUnProject(x, y, 0, modelViewMatrix, porjectionMatrix, viewport, &x1, &y1,
          &z1);
        gluUnProject(x, y, 1, modelViewMatrix, porjectionMatrix, viewport, &x2, &y2,
          &z2);
        float4 L1(x1, y1, z1);
        float4 L2(x2, y2, z2);
        float4 Hit;
        float dist = 10e20;
        bool hitted = false;
        size_t xmin, ymin, zmin;
        for (size_t z = 0; z < 3; ++z) {
          for (size_t y = 0; y < 3; ++y) {
            for (size_t x = 0; x < 3; ++x) {
              SmallCube &c = cubes[z][y][x];
              if (CheckLineBox(c.p0, c.p1, L1, L2, Hit)) {
                float d = distance(L1, Hit);
                if (d < dist) {
                  dist = d;
                  xmin = x;
                  ymin = y;
                  zmin = z;
                }
                hitted = true;
              }
            }
          }
        }
        if (hitted) {
          cubes[zmin][ymin][xmin].type = int(cubes[zmin][ymin][xmin].type + 1) % 8;
        }
      }
    }
  }

  void printMatrix() {
    for (size_t z = 0; z < 3; ++z) {
      for (size_t y = 0; y < 3; ++y) {
        for (size_t x = 0; x < 3; ++x) {
          std::cout << cubes[z][y][x].type << ", ";
        }
        std::cout << std::endl;
      }
    }
    std::cout << std::endl;
  }

  SmallCube cubes[3][3][3];
  float4 frame[8];
  float4 color[8];
  float alpha;
  double modelViewMatrix[16];
  double porjectionMatrix[16];
  int viewport[4];
  int onlyOne;
};

bool GetIntersection(float fDst1, float fDst2, float4& P1, float4& P2,
                     float4 &Hit) {
  if ((fDst1 * fDst2) >= 0.0f)
    return false;
  if (fDst1 == fDst2)
    return false;
  Hit = P1 + (P2 - P1) * (-fDst1 / (fDst2 - fDst1));
  return true;
}

bool InBox(float4& Hit, float4& B1, float4& B2, int Axis) {
  if (Axis == 1 && Hit.z > B1.z && Hit.z < B2.z && Hit.y > B1.y && Hit.y < B2.y)
    return true;
  if (Axis == 2 && Hit.z > B1.z && Hit.z < B2.z && Hit.x > B1.x && Hit.x < B2.x)
    return true;
  if (Axis == 3 && Hit.x > B1.x && Hit.x < B2.x && Hit.y > B1.y && Hit.y < B2.y)
    return true;
  return false;
}

bool CheckLineBox(float4& B1, float4& B2, float4& L1, float4& L2, float4& Hit) {
  if (L2.x < B1.x && L1.x < B1.x)
    return false;
  if (L2.x > B2.x && L1.x > B2.x)
    return false;
  if (L2.y < B1.y && L1.y < B1.y)
    return false;
  if (L2.y > B2.y && L1.y > B2.y)
    return false;
  if (L2.z < B1.z && L1.z < B1.z)
    return false;
  if (L2.z > B2.z && L1.z > B2.z)
    return false;
  if (L1.x > B1.x && L1.x < B2.x && L1.y > B1.y && L1.y < B2.y && L1.z > B1.z &&
      L1.z < B2.z) {
    Hit = L1;
    return true;
  }
  if ((GetIntersection(L1.x - B1.x, L2.x - B1.x, L1, L2, Hit) &&
       InBox(Hit, B1, B2, 1)) ||
      (GetIntersection(L1.y - B1.y, L2.y - B1.y, L1, L2, Hit) &&
       InBox(Hit, B1, B2, 2)) ||
      (GetIntersection(L1.z - B1.z, L2.z - B1.z, L1, L2, Hit) &&
       InBox(Hit, B1, B2, 3)) ||
      (GetIntersection(L1.x - B2.x, L2.x - B2.x, L1, L2, Hit) &&
       InBox(Hit, B1, B2, 1)) ||
      (GetIntersection(L1.y - B2.y, L2.y - B2.y, L1, L2, Hit) &&
       InBox(Hit, B1, B2, 2)) ||
      (GetIntersection(L1.z - B2.z, L2.z - B2.z, L1, L2, Hit) &&
       InBox(Hit, B1, B2, 3)))
    return true;

  return false;
}

#endif