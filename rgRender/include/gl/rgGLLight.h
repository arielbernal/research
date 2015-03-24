#ifndef RGGLLIGHT_H
#define RGGLLIGHT_H

#include <gl/rgGLHeaders.h>
#include <gl/rgGLShaderProgram.h>

namespace rg {

struct GLLight : public GLObject {
  enum { DIRECTIONAL, POINT, SPOT, AREA };
  GLLight(const std::string& Name, size_t LightType = DIRECTIONAL,
          GLObject* Parent = nullptr)
      : GLObject(Name, LIGHT, Parent),
        LightType(LightType),
        Enabled(true),
        La(glm::vec3(0.1f, 0.1f, 0.1f)),
        Ld(glm::vec3(0.2f, 0.2f, 0.2f)),
        Ls(glm::vec3(0.3f, 0.3f, 0.3f)) {}

  // Light type: 0 Directional, 1 point, 2 Spot, 3 Area
  size_t LightType;
  bool Enabled;

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

  void setColor(const glm::vec3& ambient, const glm::vec3& diffuse,
                const glm::vec3& specular) {
    La = ambient;
    Ld = diffuse;
    Ls = specular;
  }

  std::string getTypeString() {
    switch (LightType) {
      case DIRECTIONAL:
        return "Light::Directional";
      case POINT:
        return "Light::Point";
      case SPOT:
        return "Light::Spot";
      case AREA:
        return "Light::Area";
      default:
        return "Light::Unknown";
    }
    return "Light::Unknown";
  }

};

}  // namespace rg

#endif  // RGGLLIGHT_H