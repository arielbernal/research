#ifndef RGGLMATERIAL_H
#define RGGLMATERIAL_H

#include <gl/rgGLHeaders.h>

namespace rg {

struct GLMaterial {
  std::string Name;
  glm::vec3 Ka;        // Ambient color
  glm::vec3 Kd;        // Diffuse color
  glm::vec3 Ks;        // Specular color
  float Ns;            // Specular exponent
  glm::vec3 Tf;        // Transmision filter
  int illum;           // Illumination model
  float d;             // Dissolve factor
  float Ni;            // Index of refraction
  std::string map_Ka;  // Ambient texture
  std::string map_Kd;  // Diffuse texture
  std::string map_Ks;  // Specular texture

  GLMaterial(const std::string& Name)
      : Name(Name), Kd(0.5), Ka(0.1f), Ks(0.3f), Ns(20) {}
  const bool hasTextureFiles() const {
    return map_Ka.length() > 0 || map_Kd.length() > 0 || map_Ks.length() > 0;
  }

  static GLMaterial Default() {
    GLMaterial Mat("Default");
    Mat.Kd = glm::vec3(1, 1, 1);
    Mat.Ka = glm::vec3(0.1f);
    Mat.Ks = glm::vec3(0.2f);
    Mat.Ns = 20;
    return Mat;
  }

  static GLMaterial Red() {
    GLMaterial Mat("Red");
    Mat.Kd = glm::vec3(1, 0, 0);
    Mat.Ka = glm::vec3(0.1f, 0, 0);
    Mat.Ks = glm::vec3(0.2f);
    Mat.Ns = 20;
    return Mat;
  }

  static GLMaterial Green() {
    GLMaterial Mat("Green");
    Mat.Kd = glm::vec3(0, 1, 0);
    Mat.Ka = glm::vec3(0, 0.1f, 0);
    Mat.Ks = glm::vec3(0.2f);
    Mat.Ns = 20;
    return Mat;
  }

  static GLMaterial Blue() {
    GLMaterial Mat("Blue");
    Mat.Kd = glm::vec3(0, 0, 1);
    Mat.Ka = glm::vec3(0, 0, 0.1f);
    Mat.Ks = glm::vec3(0.2f);
    Mat.Ns = 20;
    return Mat;
  }
};

}  // namespace rg

#endif  // RGGLMATERIAL_H
