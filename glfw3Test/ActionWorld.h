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
    add(new GLCamera("FirstCamera"));
    GLCamera* Cam = new GLCamera("SecondCamera");
    Cam->setPerspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    Cam->setPosition(-5, 5, 0);
    add(Cam);

    GLLight* L1 = new GLLight("FirstLight");
    add(L1);

    GLShaderProgram* Shader = new GLShaderProgram(
        "Basic3d", "./shaders/basic3d.vs", "./shaders/basic3d.fs");

    GLBasicCuboid* cube =
        new GLBasicCuboid("Cube", 2, 2, 2, glm::vec4(1, 1, 1, 1));
    cube->attachShader(Shader);
    cube->translate(0, -2, 2);
    add(cube);

    GLBasicCuboid* cube1 =
        new GLBasicCuboid("Cube1", 2, 2, 2, glm::vec4(1, 1, 1, 1));
    cube1->attachShader(Shader);
    // cube1->translate(0, 0, 3);
    add(cube1);
  }

  bool EventKey(int key, int action) {
    if (key == 'A' && action == 0) nextCamera();
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
    // if camera changes then
    // update()
    return false; 
  }
  bool EventMouseWheel(double yoffset) {
    //std::cout << yoffset << std::endl;
    // if camera changes then
    // update()
    return false; 
  }
private:
  GLMouseHandler Mouse;
};

#endif  // ACTIONWORLD_H