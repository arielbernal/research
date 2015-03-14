#ifndef RGGLCYLINDER_H
#define RGGLCYLINDER_H

#include <gl/rgGLObject.h>

namespace rg {

class GLCylinder : public GLObject {
 public:
  GLCylinder(const std::string& ObjectName,
             const GLMaterial& Material = GLMaterial::Default())
      : GLObject(ObjectName), Radius(1), Height(2), Material(Material) {
    rebuild();
  }

  GLCylinder(const std::string& ObjectName, float Radius, float Height,
             float Div, const GLMaterial& Material = GLMaterial::Default())
      : GLObject(ObjectName),
        Radius(Radius),
        Height(Height),
        Div(Div),
        Material(Material) {
    rebuild();
  }

  void setSize(float radius, float height, float divisions) {
    Radius = radius;
    Height = height;
    Div = divisions;
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
    GroupFaces* F = new GroupFaces(Material);
    float dtheta = 2 * M_PI / Div;

    // top
    {
      float z = Height / 2;
      glm::vec3 nup = glm::vec3(0, 0, 1);
      std::vector<uint16_t> Indices(Div);
      F->addVertex(glm::vec3(0, 0, z), nup);
      for (size_t np = 0; np < Div; ++np) {
        float x = Radius * cos(np * dtheta);
        float y = Radius * sin(np * dtheta);
        F->addVertex(glm::vec3(x, y, z), nup);
        Indices[Div - np - 1] = np + 1;
      }
      F->addTriangleFan(0, Indices);
      Groups.push_back(F);
    }
    // bottom
    {
      GroupFaces* F = new GroupFaces(Material);
      float z = -Height / 2;
      glm::vec3 nup = glm::vec3(0, 0, -1);
      std::vector<uint16_t> Indices(Div);
      F->addVertex(glm::vec3(0, 0, z), nup);
      for (size_t np = 0; np < Div; ++np) {
        float x = Radius * cos(np * dtheta);
        float y = Radius * sin(np * dtheta);
        F->addVertex(glm::vec3(x, y, z), nup);
        Indices[np] = np + 1;
      }
      F->addTriangleFan(0, Indices);
      Groups.push_back(F);
    }

    // sides
    {
      GroupFaces* F = new GroupFaces(Material);
      float z0 = -Height / 2;
      float z1 = -Height / 2;
      glm::vec3 nup = glm::vec3(0, 0, -1);
      std::vector<uint16_t> Indices(Div);
      for (size_t np = 0; np < Div; ++np) {
        float x = Radius * cos(np * dtheta);
        float y = Radius * sin(np * dtheta);
        F->addVertex(glm::vec3(x, y, z), nup);
        F->addVertex(glm::vec3(x, y, z), nup);
        Indices[np] = np + 1;
      }
      F->addTriangleFan(0, Indices);
      Groups.push_back(F);
    }

  }

 private:
  float Radius, Height, Div;
  GLMaterial Material;
};

}  // namespace rg

#endif  // RGGLCYLINDER_H
