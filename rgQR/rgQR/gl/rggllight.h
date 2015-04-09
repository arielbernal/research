#ifndef RGGLLIGHT_H
#define RGGLLIGHT_H

#include <gl/rgglheaders.h>

namespace rg {

struct GLLight : public GLObject {
  enum { DIRECTIONAL, POINT, SPOT, AREA };
  GLLight(const std::string& Name, size_t LightType = DIRECTIONAL,
          GLObject* Parent = nullptr)
      : GLObject(Name, LIGHT, Parent),
        LightType(LightType),
        La(glm::vec3(0.1f, 0.1f, 0.1f)),
        Ld(glm::vec3(0.2f, 0.2f, 0.2f)),
        Ls(glm::vec3(0.3f, 0.3f, 0.3f)) {}

  // Light type: 0 Directional, 1 point, 2 Spot, 3 Area
  size_t LightType;

  // Color of the light emitted
  glm::vec3 La; // Ambient color
  glm::vec3 Ld; // Diffuse color
  glm::vec3 Ls; // Specular color

  // Spot light only
  float SpotAngle;
  float SpotCosCutoff;
  float SpotExponent;

  // Point Light Only
  float Ac; // Constant Attenuation
  float Ab; // Linear Attenuation
  float Aa; // Quadratic Attenuation

  size_t getLightType() { return LightType; }

  std::string getLightTypeString() {
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

} // namespace rg

#endif // RGGLLIGHT_H
