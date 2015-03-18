#ifndef RGGLMATERIAL_H
#define RGGLMATERIAL_H

#include <gl/rgGLHeaders.h>
#include <io/lodepng.h>

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

  GLuint TexKd_ID;
  size_t TexKd_width;
  size_t TexKd_height;

  GLMaterial(const std::string& Name = "")
      : Name(Name), Ka(0), Kd(0), Ks(0), Ns(0) {}

  const bool hasTextureFiles() const {
    return map_Ka.length() > 0 || map_Kd.length() > 0 || map_Ks.length() > 0;
  }

  ~GLMaterial() {
    glDeleteTextures(1, &TexKd_ID);
  }

  void setColor(const glm::vec3& ambient, const glm::vec3& diffuse,
                const glm::vec3& specular, float spec_exp) {
    Ka = ambient;
    Kd = diffuse;
    Ks = specular;
    Ns = spec_exp;
  }

  void loadTexture() {
    unsigned int width = 0;
    unsigned int height = 0;
    std::vector<unsigned char> img;
    if (!map_Kd.empty()) lodepng::decode(img, width, height, map_Kd);
    glGenTextures(1, &TexKd_ID);

    glBindTexture(GL_TEXTURE_2D, TexKd_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, &img[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  }

  static GLMaterial* Default() {
    GLMaterial* Mat = new GLMaterial("Default");
    Mat->Kd = glm::vec3(1, 1, 1);
    Mat->Ka = glm::vec3(0.1f);
    Mat->Ks = glm::vec3(0.2f);
    Mat->Ns = 20;
    return Mat;
  }

  static GLMaterial* Red() {
    GLMaterial* Mat = new GLMaterial("Red");
    Mat->Kd = glm::vec3(1, 0, 0);
    Mat->Ka = glm::vec3(0.1f, 0, 0);
    Mat->Ks = glm::vec3(0.2f);
    Mat->Ns = 20;
    return Mat;
  }

  static GLMaterial* Green() {
    GLMaterial* Mat = new GLMaterial("Green");
    Mat->Kd = glm::vec3(0, 1, 0);
    Mat->Ka = glm::vec3(0, 0.1f, 0);
    Mat->Ks = glm::vec3(0.2f);
    Mat->Ns = 20;
    return Mat;
  }

  static GLMaterial* Blue() {
    GLMaterial* Mat = new GLMaterial("Blue");
    Mat->Kd = glm::vec3(0, 0, 1);
    Mat->Ka = glm::vec3(0, 0, 0.1f);
    Mat->Ks = glm::vec3(0.2f);
    Mat->Ns = 20;
    return Mat;
  }
};

}  // namespace rg

#endif  // RGGLMATERIAL_H
