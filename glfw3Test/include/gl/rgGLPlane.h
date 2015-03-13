#ifndef RGGLPLANE_H
#define RGGLPLANE_H

#include <gl/rgGLObject.h>

namespace rg {

class GLPlane : public GLObject {
 public:
  GLPlane(const std::string& ObjectName,
          const GLMaterial& Material = GLMaterial::Default())
      : GLObject(ObjectName), Dx(1), Dy(1), Nx(1), Ny(1), Material(Material) {
    rebuild();
  }

  GLPlane(const std::string& ObjectName, float dx, float dy, size_t nx,
          size_t ny, const GLMaterial& Material = GLMaterial::Default())
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
    float dx = Dx / Nx;
    float dy = Dy / Ny;
    for (size_t ny = 0; ny <= Ny; ++ny) {
      for (size_t nx = 0; nx <= Nx; ++nx) {
        F->addVertex(glm::vec3(x0 + nx * dx, y0 + ny * dy, 0));
      }
    }

    for (size_t ny = 0; ny < Ny; ++ny) {
      for (size_t nx = 0; nx < Nx; ++nx) {
        size_t id00 = ny * (Nx+1) + nx;
        size_t id01 = id00 + 1;
        size_t id10 = id00 + Nx + 1;
        size_t id11 = id10 + 1; 
       // F->addQuad(id00, id10, id11, id01);
        F->addTriangle(id00, id01, id10);
        F->addTriangle(id10, id01, id11);
      }
    }
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
