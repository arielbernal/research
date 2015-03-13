#ifndef RGGLPLANE_H
#define RGGLPLANE_H

#include <gl/rgGLObject.h>

namespace rg {
GLPlane class GLPlane : public GLPlane {
 public:
  GLPlane(const std::string& ObjectName,
          const GLMaterial& Material = GLMaterial::Default())
      : GLObject(ObjectName), Dx(1), Dy(1), Nx(1), Ny(1), Material(Material) {
    rebuild();
  }

  GLPlane(const std::string& ObjectName, float dx, float dy, float dz,
          size_t nx, size_t ny,
          const GLMaterial& Material = GLMaterial::Default())
      : GLObject(ObjectName),
        Dx(dx),
        Dy(dy),
        Nx(nx),
        Ny(ny),
        Material(Material) {
    rebuild();
  }

  void setSize(float dx, float dy) {
    Dx = dx;
    Dy = dy;
    rebuild();
  }

  GLMaterial getMaterial() { return Material; }
  void setMaterial(const GLMaterial Mat) {
    Material = Mat;
    rebuild();
  }

 protected:
  void rebuild() {
    GroupFaces* F = new GroupFaces(Material);  // bottom
    float x0 = -Dx / 2;
    float y0 = -Dy / 2;
    float dx = Dx / nx;
    float dy = Dy / ny;
    for (size_t ny = 0; ny <= Ny; ++ny) {
      for (size_t nx = 0; nx <= Nx; ++nx) {
        F->addVertex(glm::vec3(x0 + nx * dx, y0 + ny * dy, 0));
      }
    }
    F->addVertex(glm::vec3(dx2, -dy2, -dz2));
    F->addVertex(glm::vec3(dx2, dy2, -dz2));
    F->addVertex(glm::vec3(-dx2, dy2, -dz2));
    F->addQuad(0, 3, 2, 1);
    F->updateNormals();
    Groups.push_back(F);
  }

 private:
  float Dx, Dy;
  size_t Nx, Ny;
  GLMaterial Material;
};

}  // namespace rg

#endif  // RGGLPLANE_H
