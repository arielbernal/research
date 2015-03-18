#ifndef RGGLCUBOID_H
#define RGGLCUBOID_H

#include <gl/rgGLObject.h>

namespace rg {

class GLCuboid : public GLObject {
 public:
  enum { GLCUBOID_STANDARD, GLCUBOID_REFINED, GLCUBOID_MULTICOLOR };

  GLCuboid(const std::string& ObjectName, size_t type = GLCUBOID_STANDARD,
           GLMaterial* Material = GLMaterial::Default())
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
           GLMaterial* Material = GLMaterial::Default())
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

  GLMaterial* getMaterial() { return Material; }
  void setMaterial(GLMaterial* Mat) {
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
    Groups.clear();
    switch (type) {
      case GLCUBOID_MULTICOLOR:
        multicolor();
        break;
      case GLCUBOID_STANDARD:
        standard();
        break;
      case GLCUBOID_REFINED:
        refined();
        break;
      default:
        standard();
        break;
    }
  }

  void multicolor() {
    type = GLCUBOID_MULTICOLOR;
    float dx2 = Dx / 2;
    float dy2 = Dy / 2;
    float dz2 = Dz / 2;
    GLMaterial* MatRed = new GLMaterial("Red");
    MatRed.Kd = glm::vec3(1, 0.3, 0.2);
    GLMaterial* MatGreen = new GLMaterial("Green");
    MatGreen.Kd = glm::vec3(0.3, 1, 0.2);
    GLMaterial* MatBlue = new GLMaterial("Blue");
    MatBlue.Kd = glm::vec3(0.2, 0.3, 1);
    GLMaterial* MatYellow = new GLMaterial("Yellow");
    MatYellow.Kd = glm::vec3(1, 1, 0.3);
    GLMaterial* MatMagenta = new GLMaterial("Magenta");
    MatMagenta.Kd = glm::vec3(1, 0.2, 1);
    GLMaterial* MatCyan = new GLMaterial("Cyan");
    MatCyan.Kd = glm::vec3(0.2, 1, 1);

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
    type = GLCUBOID_STANDARD;
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

  void refined() {
    type = GLCUBOID_REFINED;
    float dx2 = Dx / 2;
    float dy2 = Dy / 2;
    float dz2 = Dz / 2;

    GroupFaces* F = new GroupFaces(Material);
    F->addVertex(glm::vec3(-dx2, -dy2, -dz2));  // 0 bottom
    F->addVertex(glm::vec3(dx2, -dy2, -dz2));   // 1 bottom
    F->addVertex(glm::vec3(dx2, dy2, -dz2));    // 2 bottom
    F->addVertex(glm::vec3(-dx2, dy2, -dz2));   // 3 bottom
    F->addVertex(glm::vec3(-dx2, -dy2, dz2));   // 4 top
    F->addVertex(glm::vec3(dx2, -dy2, dz2));    // 5 top
    F->addVertex(glm::vec3(dx2, dy2, dz2));     // 6 top
    F->addVertex(glm::vec3(-dx2, dy2, dz2));    // 7 top
    F->addVertex(glm::vec3(0, 0, -dz2));        // 8 bottom
    F->addVertex(glm::vec3(0, 0, dz2));         // 9 top
    F->addVertex(glm::vec3(dx2, 0, 0));         // 10 front
    F->addVertex(glm::vec3(-dx2, 0, 0));        // 11 back
    F->addVertex(glm::vec3(0, -dy2, 0));        // 12 left
    F->addVertex(glm::vec3(0, dy2, 0));         // 13 right
    F->addTriangleFan(8, {0, 1, 2, 3});         // bottom
    F->addTriangleFan(9, {4, 7, 6, 5});         // top
    F->addTriangleFan(10, {1, 5, 6, 2});        // front
    F->addTriangleFan(11, {3, 7, 4, 0});        // back
    F->addTriangleFan(12, {0, 4, 5, 1});        // left
    F->addTriangleFan(13, {2, 6, 7, 3});        // right
    F->updateNormals();
    Groups.push_back(F);
  }

 private:
  float Dx, Dy, Dz;
  size_t type;
  GLMaterial* Material;
};

}  // namespace rg

#endif  // RGGLCUBOID_H
