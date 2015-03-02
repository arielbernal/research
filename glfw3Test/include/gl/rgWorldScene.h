#ifndef RGWORLDSCENE_H
#define RGWORLDSCENE_H

#include <gl/rgGLHeaders.h>
#include <gl/rgGLProgram.h>
#include <gl/rgGLObject.h>
#include <gl/rgCamera.h>
#include <gl/rgLight.h>
//#include <gl/rgBasicObject.h>

namespace rg {


class WorldScene {
 public:
  WorldScene() {
    CurrentCamera = Cameras.begin();
  }
  
  void create() {
    GLProgramManager::addProgram("Basic3d", "./shaders/basic3d.vs",
                                 "./shaders/basic3d.fs");

  }

  void updateCamera() {

  }

  void render() {

  }

  void addCamera(Camera* Cam) {
    Cameras.push_back(Cam);
    CurrentCamera = std::prev(Cameras.end());
  }

  void firstCamera() {
    CurrentCamera = Cameras.begin();
  }
  
  void nextCamera() {
    CurrentCamera++;
    if (CurrentCamera == Cameras.end()) 
      CurrentCamera = Cameras.begin();
  }

 private:
  typedef std::vector<Camera*>::iterator CameraIterator;
  typedef std::vector<Light*>::iterator LightIterator;
  typedef std::vector<GLObject*>::iterator GLObjectIterator;

  std::vector<GLObject*> Objects;
  std::vector<Camera*> Cameras;
  std::vector<Light*> Lights;
  CameraIterator CurrentCamera;
};

}  // namespace rg

#endif // RGWORLDSCENE_H