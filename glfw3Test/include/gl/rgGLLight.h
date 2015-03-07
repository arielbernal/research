#ifndef RGGLLIGHT_H
#define RGGLLIGHT_H

#include <gl/rgGLHeaders.h>

namespace rg {

class GLLight {
 public:
  enum { DIRECTIONAL, POINT, SPOT, AREA };
  enum { DIFFUSE, AMBIENT, SPECULAR, EMISSIVE };

  GLLight(const std::string& Name) : Name(Name), enable(true), pos(0, 0, 0) {}

  void setPosition(float x, float y, float z) { pos = glm::vec3(x, y, z); }
  glm::vec3 getPosition() { return pos; }

  void turnOff() { enable = false; }
  void turnOn() { enable = true; }
  void switchState() { enable = !enable; }
  bool isOn() { return enable; }

  std::string getName() { return Name; }

 protected:
 private:
  std::string Name;
  bool enable;
  
  glm::vec3 pos;
  // Color of the light emitted
  glm::vec3 Color;
  // Spot and Directional Lights
  glm::vec3 Direction;

  // Spot light only
  float SpotAngle;
  float SpotCosCutoff;
  float SpotExponent;

  // Point Light Only
  float ConstantAttenuation;
  float LinearAttenuation;
  float QuadraticAttenuation;
};



}  // namespace rg

#endif  // RGGLLIGHT_H