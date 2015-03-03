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
    Vertices.push_back(BasicVertex(-dx2, -dy2, -dz2, color));  // 0 bottom
    Vertices.push_back(BasicVertex(dx2, -dy2, -dz2, color));   // 1 bottom
    Vertices.push_back(BasicVertex(dx2, dy2, -dz2, color));    // 2 bottom
    Vertices.push_back(BasicVertex(-dx2, dy2, -dz2, color));   // 3 bottom
    Vertices.push_back(BasicVertex(-dx2, -dy2, dz2, color));   // 4 top
    Vertices.push_back(BasicVertex(dx2, -dy2, dz2, color));    // 5 top
    Vertices.push_back(BasicVertex(dx2, dy2, dz2, color));     // 6 top
    Vertices.push_back(BasicVertex(-dx2, dy2, dz2, color));    // 7 top
    Vertices.push_back(BasicVertex(0, 0, -dz2, color));        // 8 bottom
    Vertices.push_back(BasicVertex(0, 0, dz2, color));         // 9 top
    Vertices.push_back(BasicVertex(dx2, 0, 0, color));         // 10 front
    Vertices.push_back(BasicVertex(-dx2, 0, 0, color));        // 11 back
    Vertices.push_back(BasicVertex(0, -dy2, 0, color));        // 12 left
    Vertices.push_back(BasicVertex(0, dy2, 0, color));         // 13 right
    triangleFan(8, { 0, 1, 2, 3 }, Indices);                   // bottom
    triangleFan(9, { 4, 7, 6, 5 }, Indices);                   // top
    triangleFan(10, { 1, 5, 6, 2 }, Indices);                  // front
    triangleFan(11, { 3, 7, 4, 0 }, Indices);                  // back
    triangleFan(12, { 0, 4, 5, 1 }, Indices);                  // left
    triangleFan(13, { 2, 6, 7, 3 }, Indices);                  // right
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
