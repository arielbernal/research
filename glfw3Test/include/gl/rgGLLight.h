#ifndef RGGLLIGHT_H
#define RGGLLIGHT_H

#include <gl/rgGLHeaders.h>

namespace rg {

class GLLight {
 public:
  GLLight(const std::string& LightName)
      : LightName(LightName), enable(true), pos(0, 0, 10) {}

  void setPosition(float x, float y, float z) { pos = glm::vec3(x, y, z); }
  glm::vec3 getPosition() { return pos; }

  void turnOff() { enable = false; }

  void turnOn() { enable = true; }
  void switchState() { enable = !enable; }

  bool isOn() { return enable; }

  std::string getName() { return LightName; }

 protected:
 private:
  std::string LightName;
  bool enable;
  glm::vec3 pos;
};

}  // namespace rg

#endif  // RGGLLIGHT_H