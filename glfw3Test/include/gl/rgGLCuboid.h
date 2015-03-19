#ifndef RGGLCUBOID_H
#define RGGLCUBOID_H

#include <gl/rgGLObject.h>

namespace rg {

class GLCuboid : public GLObject {
 public:
  enum { GLCUBOID_STANDARD, GLCUBOID_MULTICOLOR };

  GLCuboid(const std::string& ObjectName, size_t type = GLCUBOID_STANDARD,
           GLMaterialPtr Material = GLMaterialDefault)
      : GLObject(ObjectName),
        Dx(1),
        Dy(1),
        Dz(1),
        type(type),
        Material(Material) {
    rebuild();
  }

  GLCuboid(const std::string& ObjectName, float dx, float dy, float dz,
           size_t type = GLCUBOID_STANDARD,
           GLMaterialPtr Material = GLMaterialDefault)
      : GLObject(ObjectName),
        Dx(dx),
        Dy(dy),
        Dz(dz),
        type(type),
        Material(Material) {
    rebuild();
  }

  glm::vec3 getSize() { return glm::vec3(Dx, Dy, Dz); }
  void setSize(float dx, float dy, float dz) {
    Dx = dx;
    Dy = dy;
    Dz = dz;
    rebuild();
  }

  GLMaterialPtr getMaterial() { return Material; }
  void setMaterial(GLMaterialPtr& Mat) {
    Material = Mat;
    rebuild();
  }

  size_t getType() { return type; }
  void setType(size_t Type) {
    type = Type;
    rebuild();
  }

 protected:
  void rebuild() {
    clearGroups();
    switch (type) {
      case GLCUBOID_MULTICOLOR:
        multicolor();
        break;
      case GLCUBOID_STANDARD:
        standard();
        break;
      default:
        standard();
        break;
    }
  }

  void multicolor() {
    float dx2 = Dx / 2;
    float dy2 = Dy / 2;
    float dz2 = Dz / 2;
    GLMaterialPtr MatRed = std::make_shared<GLMaterial>("Red");
    MatRed->Kd = glm::vec3(1, 0.3, 0.2);
    GLMaterialPtr MatGreen = std::make_shared<GLMaterial>("Green");
    MatGreen->Kd = glm::vec3(0.3, 1, 0.2);
    GLMaterialPtr MatBlue = std::make_shared<GLMaterial>("Blue");
    MatBlue->Kd = glm::vec3(0.2, 0.3, 1);
    GLMaterialPtr MatYellow = std::make_shared<GLMaterial>("Yellow");
    MatYellow->Kd = glm::vec3(1, 1, 0.3);
    GLMaterialPtr MatMagenta = std::make_shared<GLMaterial>("Magenta");
    MatMagenta->Kd = glm::vec3(1, 0.2, 1);
    GLMaterialPtr MatCyan = std::make_shared<GLMaterial>("Cyan");
    MatCyan->Kd = glm::vec3(0.2, 1, 1);

    GroupFaces* F = new GroupFaces(MatRed);  // bottom
    F->addVertex(glm::vec3(-dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(dx2, dy2, -dz2));
    F->addVertex(glm::vec3(-dx2, dy2, -dz2));
    F->addQuad(0, 3, 2, 1);
    F->updateNormals();
    Groups.push_back(F);

    F = new GroupFaces(MatGreen);  // top
    F->addVertex(glm::vec3(-dx2, -dy2, dz2));
    F->addVertex(glm::vec3(dx2, -dy2, dz2));
    F->addVertex(glm::vec3(dx2, dy2, dz2));
    F->addVertex(glm::vec3(-dx2, dy2, dz2));
    F->addQuad(0, 1, 2, 3);
    F->updateNormals();
    Groups.push_back(F);

    F = new GroupFaces(MatBlue);  // front
    F->addVertex(glm::vec3(dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(dx2, dy2, -dz2));
    F->addVertex(glm::vec3(dx2, dy2, dz2));
    F->addVertex(glm::vec3(dx2, -dy2, dz2));
    F->addQuad(0, 1, 2, 3);
    F->updateNormals();
    Groups.push_back(F);

    F = new GroupFaces(MatYellow);  // back
    F->addVertex(glm::vec3(-dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(-dx2, dy2, -dz2));
    F->addVertex(glm::vec3(-dx2, dy2, dz2));
    F->addVertex(glm::vec3(-dx2, -dy2, dz2));
    F->addQuad(0, 3, 2, 1);
    F->updateNormals();
    Groups.push_back(F);

    F = new GroupFaces(MatMagenta);  // left
    F->addVertex(glm::vec3(-dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(dx2, -dy2, dz2));
    F->addVertex(glm::vec3(-dx2, -dy2, dz2));
    F->addQuad(0, 1, 2, 3);
    F->updateNormals();
    Groups.push_back(F);

    F = new GroupFaces(MatCyan);  // right
    F->addVertex(glm::vec3(-dx2, dy2, -dz2));
    F->addVertex(glm::vec3(dx2, dy2, -dz2));
    F->addVertex(glm::vec3(dx2, dy2, dz2));
    F->addVertex(glm::vec3(-dx2, dy2, dz2));
    F->addQuad(0, 3, 2, 1);
    F->updateNormals();
    Groups.push_back(F);
  }

  void standard() {
    float dx2 = Dx / 2;
    float dy2 = Dy / 2;
    float dz2 = Dz / 2;

    GroupFaces* F = new GroupFaces(Material);  // bottom
    F->addVertex(glm::vec3(-dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(dx2, dy2, -dz2));
    F->addVertex(glm::vec3(-dx2, dy2, -dz2));
    F->addQuad(0, 3, 2, 1);
    F->updateNormals();
    Groups.push_back(F);

    F = new GroupFaces(Material);  // top
    F->addVertex(glm::vec3(-dx2, -dy2, dz2));
    F->addVertex(glm::vec3(dx2, -dy2, dz2));
    F->addVertex(glm::vec3(dx2, dy2, dz2));
    F->addVertex(glm::vec3(-dx2, dy2, dz2));
    F->addQuad(0, 1, 2, 3);
    F->updateNormals();
    Groups.push_back(F);

    F = new GroupFaces(Material);  // front
    F->addVertex(glm::vec3(dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(dx2, dy2, -dz2));
    F->addVertex(glm::vec3(dx2, dy2, dz2));
    F->addVertex(glm::vec3(dx2, -dy2, dz2));
    F->addQuad(0, 1, 2, 3);
    F->updateNormals();
    Groups.push_back(F);

    F = new GroupFaces(Material);  // back
    F->addVertex(glm::vec3(-dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(-dx2, dy2, -dz2));
    F->addVertex(glm::vec3(-dx2, dy2, dz2));
    F->addVertex(glm::vec3(-dx2, -dy2, dz2));
    F->addQuad(0, 3, 2, 1);
    F->updateNormals();
    Groups.push_back(F);

    F = new GroupFaces(Material);  // left
    F->addVertex(glm::vec3(-dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(dx2, -dy2, dz2));
    F->addVertex(glm::vec3(-dx2, -dy2, dz2));
    F->addQuad(0, 1, 2, 3);
    F->updateNormals();
    Groups.push_back(F);

    F = new GroupFaces(Material);  // right
    F->addVertex(glm::vec3(-dx2, dy2, -dz2));
    F->addVertex(glm::vec3(dx2, dy2, -dz2));
    F->addVertex(glm::vec3(dx2, dy2, dz2));
    F->addVertex(glm::vec3(-dx2, dy2, dz2));
    F->addQuad(0, 3, 2, 1);
    F->updateNormals();
    Groups.push_back(F);
  }

 private:
  float Dx, Dy, Dz;
  size_t type;
  GLMaterialPtr Material;
};

}  // namespace rg

#endif  // RGGLCUBOID_H
