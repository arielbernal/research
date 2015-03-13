#ifndef ACTIONWORLD_H
#define ACTIONWORLD_H

#include <gl/rgGLCamera.h>
#include <gl/rgGLLight.h>
#include <gl/rgGLCuboid.h>
#include <gl/rgGLShaderProgram.h>
#include <gl/rgGLWorldScene.h>
#include <gl/rgGLMouseHandler.h>

using namespace rg;
class ActionWorld : public GLWorldScene {
 public:
  void init() {
    attchObjectShader("./shaders/light1.vs","./shaders/light1.fs");

    add(new GLCamera("FirstCamera"));
    GLCamera* Cam = new GLCamera("SecondCamera");
    Cam->setPerspective(50.0f / 180.0f * M_PI, 4.0f / 3.0f, 0.1f, 200.0f);
    Cam->setPosition(20, 0, 0);
    add(Cam);

    GLLight* L1 = GLLight::Point("FirstLight", -5, 1, 1);
    add(L1);
    GLLight* L2 = GLLight::Point("SecondLight", 5, -1, 5);
    add(L2);

    GLMaterial M1 = GLMaterial::Red();
    M1.Ks = glm::vec3(4);
    M1.Ns = 64;
    GLCuboid* cube =
        new GLCuboid("Cube", 2, 2, 2, GLCuboid::GLCUBOID_REFINED, M1);
    cube->translate(0, -2, 3);
    add(cube);

    GLCuboid* cube1 =
        new GLCuboid("Cube1", 2, 2, 2, GLCuboid::GLCUBOID_MULTICOLOR);
    cube1->translate(0, 0, 1);
    add(cube1);

    GLCuboid* cube2 = new GLCuboid("Cube2", 0.5f, 0.5f, 0.5f);
    cube2->translate(5, -1, 1);
    add(cube2);

    GLMaterial M = GLMaterial::Blue();
    M.Ks = glm::vec3(4);
    GLCuboid* cube3 =
        new GLCuboid("Cube3", 2, 2, 2, GLCuboid::GLCUBOID_STANDARD, M);
    cube3->translate(-2, 2, 1);
    add(cube3);

    GLMaterial M3 = GLMaterial::Green();
    M3.Ks = glm::vec3(2);
    GLCuboid* fl =
        new GLCuboid("Floor", 20, 20, 0.1, GLCuboid::GLCUBOID_STANDARD, M3);
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