#ifndef RGGLMATERIAL_H
#define RGGLMATERIAL_H

#include <memory>
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

  enum { MAT_NONE, MAT_DEFAULT, MAT_RED, MAT_GREEN, MAT_BLUE };

  GLMaterial(const std::string& Name)
      : Name(Name), Ka(0), Kd(0), Ks(0), Ns(0) {}

  GLMaterial(size_t Initializer = MAT_NONE) {
    switch (Initializer) {
      case MAT_NONE:
        return;
      case MAT_DEFAULT:
        mat_default();
        break;
      case MAT_RED:
        mat_red();
        break;
      case MAT_GREEN:
        mat_green();
        break;
      case MAT_BLUE:
        mat_blue();
        break;
    }
  }

  const bool hasTextureFiles() const {
    return map_Ka.length() > 0 || map_Kd.length() > 0 || map_Ks.length() > 0;
  }

  ~GLMaterial() {
    glDeleteTextures(1, &TexKd_ID);
    std::cout << "Destruct " + Name + " \n";
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

 private:
  void mat_default() {
    Name = "Default";
    Kd = glm::vec3(1, 1, 1);
    Ka = glm::vec3(0.1f);
    Ks = glm::vec3(0.2f);
    Ns = 20;
  }

  void mat_red() {
    Name = "Red";
    Kd = glm::vec3(1, 0, 0);
    Ka = glm::vec3(0.1f, 0, 0);
    Ks = glm::vec3(0.2f);
    Ns = 20;
  }

  void mat_green() {
    Name = "Green";
    Kd = glm::vec3(0, 1, 0);
    Ka = glm::vec3(0, 0.1f, 0);
    Ks = glm::vec3(0.2f);
    Ns = 20;
  }

  void mat_blue() {
    Name = "Blue";
    Kd = glm::vec3(0, 0, 1);
    Ka = glm::vec3(0, 0, 0.1f);
    Ks = glm::vec3(0.2f);
    Ns = 20;
  }
};

typedef std::shared_ptr<GLMaterial> GLMaterialPtr;
static GLMaterialPtr GLMaterialDefault =
    std::make_shared<GLMaterial>(GLMaterial::MAT_DEFAULT);
static GLMaterialPtr GLMaterialRed =
    std::make_shared<GLMaterial>(GLMaterial::MAT_RED);
static GLMaterialPtr GLMaterialGreen =
    std::make_shared<GLMaterial>(GLMaterial::MAT_GREEN);
static GLMaterialPtr GLMaterialBlue =
    std::make_shared<GLMaterial>(GLMaterial::MAT_BLUE);

}  // namespace rg

#endif  // RGGLMATERIAL_H
