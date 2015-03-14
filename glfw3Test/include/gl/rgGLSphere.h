#ifndef RGGLSPHERE_H
#define RGGLSPHERE_H

#include <gl/rgGLObject.h>

namespace rg {

class GLSphere : public GLObject {
 public:
  GLSphere(const std::string& ObjectName,
           const GLMaterial& Material = GLMaterial::Default())
      : GLObject(ObjectName), R(1), Div(10), Material(Material) {
    rebuild();
  }

  GLSphere(const std::string& ObjectName, float R, float Div,
           const GLMaterial& Material = GLMaterial::Default())
      : GLObject(ObjectName), R(R), Div(Div), Material(Material) {
    rebuild();
  }

  void setSize(float Radius, float Divisions) {
    R = Radius;
    Div = Divisions;
    rebuild();
  }

  GLMaterial getMaterial() { return Material; }
  void setMaterial(const GLMaterial Mat) {
    Material = Mat;
    rebuild();
  }

 protected:
  void rebuild() {
    Groups.clear();
    GroupFaces* F = new GroupFaces(Material);  // bottom
    size_t Nm = Div;
    size_t Np = Div;
    float dtheta = 2 * M_PI / Nm;
    float dphi = M_PI / (Np - 1);
    for (size_t np = 0; np < Np; ++np) {
      float r = R * cos(np * dphi - M_PI / 2);
      float z = R * sin(np * dphi - M_PI / 2);
      for (size_t nm = 0; nm < Nm; ++nm) {
        float x = r * cos(nm * dtheta);
        float y = r * sin(nm * dtheta);
        F->addVertex(glm::vec3(x, y, z));
      }
    }
    for (size_t np = 0; np < Np - 1; ++np) {
      for (size_t nm = 0; nm < Nm; ++nm) {
        size_t nm1 = (nm + 1) % Nm;
        size_t id00 = np * Nm + nm;
        size_t id01 = np * Nm + nm1;
        size_t id10 = (np + 1) * Nm + nm;
        size_t id11 = (np + 1) * Nm + nm1;
        F->addQuad(id00, id01, id11, id10);
      }
    }
    F->updateNormals();
    for (size_t nm = 0; nm < Nm; ++nm) {
      size_t id0 = nm;
      size_t id1 = (Np - 1) * Nm + nm;
      F->Vertices[id0].normal = glm::vec3(0, 0, -1);
      F->Vertices[id1].normal = glm::vec3(0, 0, 1);
    }
    Groups.push_back(F);
  }
 private:
  float R, Div;
  GLMaterial Material;
};

}  // namespace rg

#endif  // RGGLSPHERE_H
