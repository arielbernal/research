#ifndef RGGLLIGHT_H
#define RGGLLIGHT_H

#include <gl/rgGLHeaders.h>
#include <gl/rgGLShaderProgram.h>

namespace rg {

struct GLLight {
  enum { DIRECTIONAL = 0, POINT = 1, SPOT = 2, AREA = 3 };

  GLLight(const std::string& Name)
      : Name(Name), Enabled(true), type(DIRECTIONAL), Ac(1), Ab(0), Aa(0) {}

  std::string Name;
  bool Enabled;

  // Light type: 0 Directional, 1 point, 2 Spot, 3 Area
  size_t type;

  // Color of the light emitted
  glm::vec3 La;  // Ambient color
  glm::vec3 Ld;  // Diffuse color
  glm::vec3 Ls;  // Specular color

  // Spot and Point Lights
  glm::vec3 Pos;
  // Spot and Directional Lights
  glm::vec3 Direction;

  // Spot light only
  float SpotAngle;
  float SpotCosCutoff;
  float SpotExponent;

  // Point Light Only
  float Ac;  // Constant Attenuation
  float Ab;  // Linear Attenuation
  float Aa;  // Quadratic Attenuation

  static GLLight* Default(const std::string& Name = "Default") {
    GLLight* L = new GLLight(Name);
    L->type = DIRECTIONAL;
    L->La = glm::vec3(0.1f, 0.1f, 0.1f);
    L->Ld = glm::vec3(0.2f, 0.2f, 0.2f);
    L->Ls = glm::vec3(0.3f, 0.3f, 0.3f);
    L->Direction = glm::vec3(1, 1, 1);
    return L;
  }

  static GLLight* Directional(const std::string& Name = "Directional",
                              float x = 1, float y = 1, float z = 1) {
    GLLight* L = new GLLight(Name);
    L->type = DIRECTIONAL;
    L->La = glm::vec3(0.1f, 0.1f, 0.1f);
    L->Ld = glm::vec3(0.2f, 0.2f, 0.2f);
    L->Ls = glm::vec3(0.3f, 0.3f, 0.3f);
    L->Direction = glm::vec3(x, y, z);
    return L;
  }

  static GLLight* Point(const std::string& Name = "Point", float x = 10,
                        float y = 10, float z = 10) {
    GLLight* L = new GLLight(Name);
    L->type = POINT;
    L->La = glm::vec3(0.1f, 0.1f, 0.1f);
    L->Ld = glm::vec3(0.4f, 0.4f, 0.4f);
    L->Ls = glm::vec3(0.3f, 0.3f, 0.3f);
    L->Pos = glm::vec3(x, y, z);
    L->Ac = 1;
    L->Ab = 0;
    L->Aa = 0;
    return L;
  }
};

}  // namespace rg

#endif  // RGGLLIGHT_H