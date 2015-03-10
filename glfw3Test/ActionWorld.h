#ifndef ACTIONWORLD_H
#define ACTIONWORLD_H

#include <gl/rgGLCamera.h>
#include <gl/rgGLLight.h>
#include <gl/rgGLBasicCuboid.h>
#include <gl/rgGLShaderProgram.h>
#include <gl/rgGLWorldScene.h>

using namespace rg;
class ActionWorld : public GLWorldScene {
 public:
  void init() {
    // add(new GLCamera("FirstCamera"));
    GLCamera* Cam = new GLCamera("SecondCamera");
    Cam->setPerspective(50.0f / 180.0f * M_PI, 4.0f / 3.0f, 0.1f, 200.0f);
    Cam->setPosition(20, 0, 0);
    add(Cam);

    GLLight* L1 = new GLLight("FirstLight");
    add(L1);

    GLShaderProgram* Shader = new GLShaderProgram(
        "Light1", "./shaders/light1.vs", "./shaders/light1.fs");

    GLBasicCuboid* cube =
        new GLBasicCuboid("Cube", 2, 2, 2);
    cube->attachShader(Shader);
    cube->translate(0, -2, 3);
    add(cube);

    GLBasicCuboid* cube1 =
        new GLBasicCuboid("Cube1", 2, 2, 2);
    cube1->attachShader(Shader);
    cube1->translate(0, 0, 1);
    add(cube1);

    GLBasicCuboid* cube2 =
        new GLBasicCuboid("Cube2", 0.5f, 0.5f, 0.5f);
    cube2->attachShader(Shader);
    cube2->translate(1 + 0.25, 0, 0.25);
    add(cube2);

    GLBasicCuboid* fl =
        new GLBasicCuboid("Floor", 20, 20, 0.1);
    fl->attachShader(Shader);
    fl->translate(0, 0, -0.05);
    add(fl);
  }

  float alpha;
  bool EventKey(int key, int action) {
    if (key == 'A' && action == 0) nextCamera();
    if (key == 'B' && (action == 0 || action == 2)) {
      GLCamera* cam = getCurrentCamera();
      cam->setPosition(10 * cos(alpha), 10 * sin(alpha), 5);
      alpha += 0.1f;
    }
    if (key == 'C' && (action == 0 || action == 2)) {
      GLCamera* cam = getCurrentCamera();
      float dx = -2;
      float dy = 0;
      cam->rotate(dx / 320.0f, dy / 320.0f);
    }

    return false;
  }

  bool EventMouseButton(int button, int action) {
    Mouse.set(button, action);
    // if camera changes then
    // update()
    return false;
  }

  bool EventMousePos(double xpos, double ypos) {
    Mouse.position(xpos, ypos);
    if (Mouse.isLeftButtonPressed()) {
      float dx = Mouse.dx();
      float dy = Mouse.dy();
      if (fabs(dx) < 2) dx = 0;
      if (fabs(dy) < 2) dy = 0;
      GLCamera* cam = getCurrentCamera();
      cam->rotate(dx / 320.0f, dy / 320.0f);
    }
    return false;
  }

  bool EventMouseWheel(double yoffset) {
    GLCamera* cam = getCurrentCamera();
    glm::vec3 pos = cam->getPosition();
    float mouse_vx = pos.x;
    mouse_vx += yoffset > 0 ? 0.9 : -0.9;
    if (mouse_vx > 100) mouse_vx = 100;
    if (mouse_vx < 2) mouse_vx = 2;
    cam->setPosition(mouse_vx, pos.y, pos.z);
    return false;
  }

 private:
  GLMouseHandler Mouse;
};

#endif  // ACTIONWORLD_H