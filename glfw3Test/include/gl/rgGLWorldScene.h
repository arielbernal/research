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

  void update(bool force = false) {
    if (CurrentCamera->second->hasChanged() || force) {
      for (auto e : Objects) {
        e.second->updateCamera(*CurrentCamera->second);
        e.second->setLights(&Lights);
      }
      CurrentCamera->second->changeCommited();
    }
  }

  void render() {
    update(true);
    for (auto e : Objects) e.second->render();
  }

  // Camera Functions
  void add(GLCamera* Cam) {
    Cameras[Cam->getName()] = Cam;
    CurrentCamera = std::prev(Cameras.end());
  }

  void firstCamera() {
    CurrentCamera = Cameras.begin();
    update(true);
  }

  void nextCamera() {
    CurrentCamera++;
    if (CurrentCamera == Cameras.end()) CurrentCamera = Cameras.begin();
    std::cout << CurrentCamera->second->getName() << std::endl;
    update(true);
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
  void add(GLLight* Light) { Lights[Light->Name] = Light; }

  void removeLight(const std::string& LightName) {
    auto it = Lights.find(LightName);
    if (it != Lights.end()) Lights.erase(it);
  }

  void disableLight(const std::string& LightName) {
    auto it = Lights.find(LightName);
    if (it != Lights.end()) (it->second)->Enabled = false;
  }

  void enableLight(const std::string& LightName) {
    auto it = Lights.find(LightName);
    if (it != Lights.end()) (it->second)->Enabled = true;
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

class GLMouseHandler {
  enum { BUTTON_LEFT = 0, BUTTON_RIGHT = 1, BUTTON_MIDDLE = 2 };
  enum { BUTTON_PRESSED = 1, BUTTON_RELESED = 0 };

 public:
  void set(size_t btn, bool pressed) {
    Button = btn;
    Pressed = pressed;
  }

  void position(float x, float y) {
    x0 = x1;
    y0 = y1;
    x1 = x;
    y1 = y;
  }
  float getX() { return x1; }
  float getY() { return y1; }
  float getX0() { return x0; }
  float getY0() { return y0; }
  float dx() { return x1 - x0; }
  float dy() { return y1 - y0; }

  bool isMiddleButtonPressed() {
    return (Button == BUTTON_MIDDLE && Pressed == BUTTON_PRESSED);
  }
  bool isLeftButtonPressed() {
    return (Button == BUTTON_LEFT && Pressed == BUTTON_PRESSED);
  }
  bool isRightButtonPressed() {
    return (Button == BUTTON_RIGHT && Pressed == BUTTON_PRESSED);
  }

 private:
  bool Pressed;
  size_t Button;
  float x0, y0;
  float x1, y1;
};

}  // namespace rg

#endif  // RGGLWORLDSCENE_H