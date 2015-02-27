#ifndef RGWORLDSCENE_H
#define RGWORLDSCENE_H

#include <gl/rgGLHeaders.h>
#include <gl/rgCamera.h>
#include <gl/rgLight.h>
#include <gl/rgBasicObject.h>

namespace rg {


class WorldScene {
 public:
  void create() {
    GLProgramManager::addProgram("Basic3d", "./shaders/basic3d.vs",
                                 "./shaders/basic3d.fs");

    bo.setShader("Basic3d");
    bo.createModel();
    b1.setShader("Basic3d");
    b1.createModel();
    b1.translate(1, 0, -1);

    Cameras.push_back(Camera());
    CurrentCamera = Cameras[0];

    Lights.push_back(Light());

    bo.updateVPMatrix(CurrentCamera.getVPMatrix());
    b1.updateVPMatrix(CurrentCamera.getVPMatrix());
  }

  void updateCamera() {
    CurrentCamera.setPosition(4, 3, 3);
    bo.updateVPMatrix(CurrentCamera.getVPMatrix());
    b1.updateVPMatrix(CurrentCamera.getVPMatrix());
  }

  void render() {
    bo.render();
    b1.render();
  }

 private:
  BasicObject bo, b1;
  Camera CurrentCamera;
  std::vector<Camera> Cameras;
  std::vector<Light> Lights;
  // cameras
  // ligths
  // particles
  // static objects
  // objects
};

}  // namespace rg

#endif // RGWORLDSCENE_H