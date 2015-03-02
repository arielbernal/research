#ifndef RGGLWORLDSCENE_H
#define RGGLWORLDSCENE_H

#include <gl/rgGLHeaders.h>
#include <gl/rgGLObject.h>
#include <gl/rgGLCamera.h>
#include <gl/rgGLLight.h>
#include <map>
#include <vector>

namespace rg {

class GLWorldScene {
 public:
  GLWorldScene() { CurrentCamera = Cameras.begin(); }

  void update() {
    for (auto e : Objects) e.second->updateCamera(*CurrentCamera->second);
  }

  void render() {
    for (auto e : Objects) e.second->render();
  }

  // Camera Functions
  void add(GLCamera* Cam) {
    Cameras[Cam->getName()] = Cam;
    CurrentCamera = std::prev(Cameras.end());
  }

  void firstCamera() { CurrentCamera = Cameras.begin(); }

  void nextCamera() {
    CurrentCamera++;
    if (CurrentCamera == Cameras.end()) CurrentCamera = Cameras.begin();
  }

  void disableCamera(const std::string& CameraName) {
    auto it = Cameras.find(CameraName);
    if (it != Cameras.end()) (it->second)->disable();
  }

  void enableCamera(const std::string& CameraName) {
    auto it = Cameras.find(CameraName);
    if (it != Cameras.end()) (it->second)->enable();
  }

  void removeCamera(const std::string& CameraName) {
    auto it = Cameras.find(CameraName);
    if (it != Cameras.end()) Cameras.erase(it);
  }

  void setCamera(const std::string& CameraName) {
    auto it = Cameras.find(CameraName);
    if (it != Cameras.end()) CurrentCamera = it;
  }

  GLCamera* getCurrentCamera() { return CurrentCamera->second; }

  // Light functions
  void add(GLLight* Light) { Lights[Light->getName()] = Light; }

  void removeLight(const std::string& LightName) {
    auto it = Lights.find(LightName);
    if (it != Lights.end()) Lights.erase(it);
  }

  void disableLight(const std::string& LightName) {
    auto it = Lights.find(LightName);
    if (it != Lights.end()) (it->second)->turnOff();
  }

  void enableLight(const std::string& LightName) {
    auto it = Lights.find(LightName);
    if (it != Lights.end()) (it->second)->turnOn();
  }

  GLLight* getLight(const std::string& LightName) {
    auto it = Lights.find(LightName);
    if (it != Lights.end()) return (it->second);
    return NULL;
  }

  // Object functions
  void add(GLObject* Object) { Objects[Object->getName()] = Object; }

  void removeObject(const std::string& ObjectName) {
    auto it = Objects.find(ObjectName);
    if (it != Objects.end()) Objects.erase(it);
  }

  void disableObject(const std::string& ObjectName) {
    auto it = Objects.find(ObjectName);
    if (it != Objects.end()) (it->second)->disable();
  }

  void enableObject(const std::string& ObjectName) {
    auto it = Objects.find(ObjectName);
    if (it != Objects.end()) (it->second)->enable();
  }

  GLObject* getObject(const std::string& ObjectName) {
    auto it = Objects.find(ObjectName);
    if (it != Objects.end()) return (it->second);
    return NULL;
  }

 private:
  typedef std::map<std::string, GLCamera*>::iterator CameraIterator;

  std::map<std::string, GLCamera*> Cameras;
  std::map<std::string, GLLight*> Lights;
  std::map<std::string, GLObject*> Objects;

  CameraIterator CurrentCamera;
};

}  // namespace rg

#endif  // RGGLWORLDSCENE_H