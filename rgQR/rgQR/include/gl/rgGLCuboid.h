#ifndef RGGLCUBOID_H
#define RGGLCUBOID_H

#include <gl/rgGLObject.h>

namespace rg {

class GLCuboid : public GLObject3D {
 public:
  GLCuboid(const std::string& Name, GLObject* Parent = nullptr,
           GLMaterialPtr Material = nullptr)
      : GLObject3D(Name, CUBOID, Parent),
        Dx(1),
        Dy(1),
        Dz(1),
        Material(Material) {
    rebuild();
  }

  GLCuboid(const std::string& Name, float dx, float dy, float dz,
           GLObject* Parent = nullptr, GLMaterialPtr Material = nullptr)
      : GLObject3D(Name, CUBOID, Parent),
        Dx(dx),
        Dy(dy),
        Dz(dz),
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

 protected:
  void rebuild() {
    clearGroups();
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
    pushBackGroupFaces(F);

    F = new GroupFaces(Material);  // top
    F->addVertex(glm::vec3(-dx2, -dy2, dz2));
    F->addVertex(glm::vec3(dx2, -dy2, dz2));
    F->addVertex(glm::vec3(dx2, dy2, dz2));
    F->addVertex(glm::vec3(-dx2, dy2, dz2));
    F->addQuad(0, 1, 2, 3);
    F->updateNormals();
    pushBackGroupFaces(F);

    F = new GroupFaces(Material);  // front
    F->addVertex(glm::vec3(dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(dx2, dy2, -dz2));
    F->addVertex(glm::vec3(dx2, dy2, dz2));
    F->addVertex(glm::vec3(dx2, -dy2, dz2));
    F->addQuad(0, 1, 2, 3);
    F->updateNormals();
    pushBackGroupFaces(F);

    F = new GroupFaces(Material);  // back
    F->addVertex(glm::vec3(-dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(-dx2, dy2, -dz2));
    F->addVertex(glm::vec3(-dx2, dy2, dz2));
    F->addVertex(glm::vec3(-dx2, -dy2, dz2));
    F->addQuad(0, 3, 2, 1);
    F->updateNormals();
    pushBackGroupFaces(F);

    F = new GroupFaces(Material);  // left
    F->addVertex(glm::vec3(-dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(dx2, -dy2, dz2));
    F->addVertex(glm::vec3(-dx2, -dy2, dz2));
    F->addQuad(0, 1, 2, 3);
    F->updateNormals();
    pushBackGroupFaces(F);

    F = new GroupFaces(Material);  // right
    F->addVertex(glm::vec3(-dx2, dy2, -dz2));
    F->addVertex(glm::vec3(dx2, dy2, -dz2));
    F->addVertex(glm::vec3(dx2, dy2, dz2));
    F->addVertex(glm::vec3(-dx2, dy2, dz2));
    F->addQuad(0, 3, 2, 1);
    F->updateNormals();
    pushBackGroupFaces(F);
  }

 private:
  float Dx, Dy, Dz;
  GLMaterialPtr Material;
};

}  // namespace rg

#endif  // RGGLCUBOID_H
