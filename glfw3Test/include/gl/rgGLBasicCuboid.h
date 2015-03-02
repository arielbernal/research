#ifndef RGGLBASICCUBOID_H
#define RGGLBASICCUBOID_H

#include <gl/rgGLBasicObject.h>

namespace rg {

class GLBasicCuboid : public GLBasicObject {
 public:
  GLBasicCuboid(const std::string& ObjectName)
      : GLBasicObject(ObjectName),
        Dx(1),
        Dy(1),
        Dz(1),
        Color(glm::vec4(1, 1, 1, 1)) {
    resize(Dx, Dy, Dz, Color);
  }
  GLBasicCuboid(const std::string& ObjectName, float Dx, float Dy, float Dz,
           const glm::vec4& Color)
      : GLBasicObject(ObjectName), Dx(Dx), Dy(Dy), Dz(Dz), Color(Color) {
    resize(Dx, Dy, Dz, Color);
  }

  void resize(float dx, float dy, float dz, const glm::vec4& color) {
    Dx = dx;
    Dy = dy;
    Dz = dz;
    Color = color;
    Vertices.clear();
    Indices.clear();
    float dx2 = dx / 2;
    float dy2 = dy / 2;
    float dz2 = dz / 2;
    Vertices.push_back(BasicVertex(-dx2, -dy2, -dz2, color));  // 0
    Vertices.push_back(BasicVertex(dx2, -dy2, -dz2, color));   // 1
    Vertices.push_back(BasicVertex(dx2, dy2, -dz2, color));    // 2
    Vertices.push_back(BasicVertex(-dx2, dy2, -dz2, color));   // 3
    Vertices.push_back(BasicVertex(-dx2, -dy2, dz2, color));   // 4
    Vertices.push_back(BasicVertex(dx2, -dy2, dz2, color));    // 5
    Vertices.push_back(BasicVertex(dx2, dy2, dz2, color));     // 6
    Vertices.push_back(BasicVertex(-dx2, dy2, dz2, color));    // 7
    addQuad(0, 3, 2, 1, Indices);                              // bottom
    addQuad(4, 5, 6, 7, Indices);                              // top
    addQuad(1, 2, 6, 5, Indices);                              // front
    addQuad(0, 4, 7, 3, Indices);                              // back
    addQuad(1, 5, 4, 0, Indices);                              // left
    addQuad(3, 7, 6, 2, Indices);                              // right
    updateNormals(Vertices, Indices);
    updateBindings();
  }

  glm::vec3 getSize() { return glm::vec3(Dx, Dy, Dz); }

  glm::vec4 getColor() { return Color; }

 protected:
 private:
  float Dx, Dy, Dz;
  glm::vec4 Color;
};

}  // namespace rg

#endif  // RGGLBASICCUBOID_H
