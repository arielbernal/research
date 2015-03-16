#ifndef RGGLCYLINDER_H
#define RGGLCYLINDER_H

#include <gl/rgGLObject.h>

namespace rg {

class GLCylinder : public GLObject {
 public:
  GLCylinder(const std::string& ObjectName,
             const GLMaterial& Material = GLMaterial::Default())
      : GLObject(ObjectName),
        Radius(1),
        Height(2),
        flat(false),
        Material(Material) {
    rebuild();
  }

  GLCylinder(const std::string& ObjectName, float Radius, float Height,
             size_t Div, bool flat = false,
             const GLMaterial& Material = GLMaterial::Default())
      : GLObject(ObjectName),
        Radius(Radius),
        Height(Height),
        Div(Div),
        Material(Material),
        flat(flat) {
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
    uint16_t idx = 0;
    // top
    {
      float z = Height / 2;
      glm::vec3 normal = glm::vec3(0, 0, 1);
      std::vector<uint16_t> Indices(Div);
      F->addVertex(glm::vec3(0, 0, z), normal);
      for (size_t np = 0; np < Div; ++np) {
        float x = Radius * cos(np * dtheta);
        float y = Radius * sin(np * dtheta);
        F->addVertex(glm::vec3(x, y, z), normal);
        Indices[Div - np - 1] = np + 1;
      }
      F->addTriangleFan(0, Indices);
      idx = F->Vertices.size();
    }
    // bottom
    {
      float z = -Height / 2;
      std::cout << Div << " " << idx << std::endl;
      glm::vec3 normal = glm::vec3(0, 0, -1);
      std::vector<uint16_t> Indices(Div);
      F->addVertex(glm::vec3(0, 0, z), normal);
      for (size_t np = 0; np < Div; ++np) {
        float x = Radius * cos(np * dtheta);
        float y = Radius * sin(np * dtheta);
        F->addVertex(glm::vec3(x, y, z), normal);
        Indices[np] = idx + np + 1;
      }
      F->addTriangleFan(idx, Indices);
      idx = F->Vertices.size();
    }
    // sides
    if (flat) {
      float z0 = -Height / 2;
      float z1 = Height / 2;
      for (size_t np = 0; np < Div; ++np) {
        float x0 = Radius * cos(np * dtheta);
        float y0 = Radius * sin(np * dtheta);
        float x1 = Radius * cos((np + 1) * dtheta);
        float y1 = Radius * sin((np + 1) * dtheta);
        glm::vec3 p0 = glm::vec3(x0, y0, z0);
        glm::vec3 p1 = glm::vec3(x1, y1, z0);
        glm::vec3 p2 = glm::vec3(x1, y1, z1);
        glm::vec3 p3 = glm::vec3(x0, y0, z1);
        glm::vec3 normal = glm::normalize(glm::cross(p1 - p0, p3 - p0));
        F->addVertex(p0, normal);
        F->addVertex(p1, normal);
        F->addVertex(p2, normal);
        F->addVertex(p3, normal);
        F->addQuad(idx, idx + 1, idx + 2, idx + 3);
        idx += 4;
      }
      Groups.push_back(F);
    } else {
      Groups.push_back(F);
      GroupFaces* F1 = new GroupFaces(Material);
      for (size_t i = 0; i < 2; ++i) {
        float z = -Height / 2 + i * Height;
        for (size_t np = 0; np < Div; ++np) {
          float x = Radius * cos(np * dtheta);
          float y = Radius * sin(np * dtheta);
          F1->addVertex(glm::vec3(x, y, z));
        }
      }
      for (size_t np = 0; np < Div; ++np) {
        uint16_t i0 = np;
        uint16_t i1 = (np + 1) % Div;
        uint16_t i2 = (np + 1) % Div + Div;
        uint16_t i3 = (np + Div);
        F1->addQuad(i0, i1, i2, i3);
      }
      F1->updateNormals();
      Groups.push_back(F1);
    }
  }

 private:
  float Radius, Height;
  size_t Div;
  bool flat;
  GLMaterial Material;
};

}  // namespace rg

#endif  // RGGLCYLINDER_H
