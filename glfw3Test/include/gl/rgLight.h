#ifndef RGLIGHT_H
#define RGLIGHT_H

#include <gl/rgGLHeaders.h>

namespace rg {

class Light {
 public:
  Light() : enable(true), pos(0, 0, 10) {}

  void setPosition(float x, float y, float z) { pos = glm::vec3(x, y, z); }
  glm::vec3 getPosition() { return pos; }

  void turnOff() { enable = false; }

  void turnOn() { enable = true; }
  void switchState() { enable = !enable; }

  bool isOn() { return enable; }

 protected:
 private:
  bool enable;
  glm::vec3 pos;
};

}  // namespace rg

#endif  // RGLIGHT_H