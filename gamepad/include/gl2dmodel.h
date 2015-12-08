#ifndef GL2DMODEL_H
#define GL2DMODEL_H

#include <svector.h>
#include "glprimitives.h"

class GL2DModel {
public:
  GL2DModel(float ViewWidth = 100, int WinWidth = 1200, int WinHeight = 1000)
      : WinWidth(WinWidth), WinHeight(WinHeight),
        WinRatio(WinHeight / float(WinWidth)), ViewWidth(ViewWidth),
        ViewHeight(ViewWidth * WinRatio), ViewX0(ViewWidth / 2),
        ViewY0(ViewHeight / 2) {}

  virtual void render() = 0;

  void init_display() {
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(1.5);
  }

  void display() {
    set2DMode(ViewWidth, ViewHeight);
    glPushMatrix();
    glTranslatef(ViewX0, ViewY0, 0);
    render();
    glPopMatrix();
  }

  void reshape(int w, int h) {
    WinWidth = w;
    WinHeight = h;
    WinRatio = WinHeight / float(WinWidth);

    float kx = ViewX0 / ViewWidth;
    float ky = ViewY0 / ViewHeight;
    ViewHeight = ViewWidth * WinRatio;
    ViewX0 = kx * ViewWidth;
    ViewY0 = ky * ViewHeight;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    init_display();
    display();
  }

  void mouse_button(int button, int status, int x, int y) {
#ifndef WIN32
    if ((button == 3) || (button == 4)) {
      mouse_wheel(0, button == 3 ? 1 : -1, x, y);
    }
#endif
    MouseButtonRight = false;
    if (button == GLUT_RIGHT_BUTTON) {
      if (status == GLUT_DOWN) {
        MouseButtonRight = true;
        MouseX = x;
        MouseY = y;
      }
    }
  }

  void mouse_wheel(int wheel, int direction, int x, int y) {
    float k = ViewWidth / WinWidth;
    float xp = x * k - ViewX0;
    float yp = y * k - ViewY0;
#ifndef WIN32
    float factor = 1.1;
#else
    float factor = 1.3;
#endif
    float ViewZoom = direction > 0 ? factor : 1 / factor;
    ViewWidth *= ViewZoom;
    ViewHeight *= ViewZoom;
    k = ViewWidth / WinWidth;
    ViewX0 = x * k - xp;
    ViewY0 = y * k - yp;
  }

  void mouse_active_motion(int x, int y) {
    if (MouseButtonRight) {
      float k = ViewWidth / WinWidth;
      ViewX0 += (x - MouseX) * k;
      ViewY0 += (y - MouseY) * k;
    }
    MouseX = x;
    MouseY = y;
  }

  void mouse_passive_motion(int x, int y) {}

  void convertScreenToWorldCoords(int x, int y, float &wx, float &wy) {
    int viewport[4];
    float modelViewMatrix[16];
    float projectionMatrix[16];

    glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMatrix);
    glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
    glGetIntegerv(GL_VIEWPORT, viewport);

    float vector[4];
    glhUnProjectf(x, viewport[3] - y, 0, modelViewMatrix, projectionMatrix, viewport, vector);
    
    wx = vector[0];
    wy = vector[1];
  }
protected:
  int WinWidth;
  int WinHeight;
  float WinRatio;
  float ViewWidth;
  float ViewHeight;
  float ViewX0;
  float ViewY0;

  float MouseX, MouseY;
  bool MouseButtonRight;
};

#endif