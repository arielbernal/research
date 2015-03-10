#ifndef RGGLBASICCUBOID_H
#define RGGLBASICCUBOID_H

#include <gl/rgGLObject.h>

namespace rg {

class GLBasicCuboid : public GLObject {
 public:
  GLBasicCuboid(const std::string& ObjectName)
      : GLObject(ObjectName), Dx(1), Dy(1), Dz(1) {
    resize(Dx, Dy, Dz);
  }
  GLBasicCuboid(const std::string& ObjectName, float Dx, float Dy, float Dz)
      : GLObject(ObjectName), Dx(Dx), Dy(Dy), Dz(Dz) {
    resize(Dx, Dy, Dz);
  }

  void resize(float dx, float dy, float dz) {
    Dx = dx;
    Dy = dy;
    Dz = dz;
    float dx2 = dx / 2;
    float dy2 = dy / 2;
    float dz2 = dz / 2;
    GLMaterial MatRed("Red");
    MatRed.Kd = glm::vec3(1, 0.3, 0.2);
    GLMaterial MatGreen("Green");
    MatGreen.Kd = glm::vec3(0.3, 1, 0.2);
    GLMaterial MatBlue("Blue");
    MatBlue.Kd = glm::vec3(0.2, 0.3, 1);
    GLMaterial MatYellow("Yellow");
    MatYellow.Kd = glm::vec3(1, 1, 0.3);
    GLMaterial MatMagenta("Magenta");
    MatMagenta.Kd = glm::vec3(1, 0.2, 1);
    GLMaterial MatCyan("Cyan");
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

    // GroupFaces *F = new GroupFaces(MatRed);
    // F->addVertex(glm::vec3(-dx2, -dy2, -dz2));  // 0 bottom
    // F->addVertex(glm::vec3(dx2, -dy2, -dz2));   // 1 bottom
    // F->addVertex(glm::vec3(dx2, dy2, -dz2));    // 2 bottom
    // F->addVertex(glm::vec3(-dx2, dy2, -dz2));   // 3 bottom
    // F->addVertex(glm::vec3(-dx2, -dy2, dz2));   // 4 top
    // F->addVertex(glm::vec3(dx2, -dy2, dz2));    // 5 top
    // F->addVertex(glm::vec3(dx2, dy2, dz2));     // 6 top
    // F->addVertex(glm::vec3(-dx2, dy2, dz2));    // 7 top
    // F->addVertex(glm::vec3(0, 0, -dz2));        // 8 bottom
    // F->addVertex(glm::vec3(0, 0, dz2));         // 9 top
    // F->addVertex(glm::vec3(dx2, 0, 0));         // 10 front
    // F->addVertex(glm::vec3(-dx2, 0, 0));        // 11 back
    // F->addVertex(glm::vec3(0, -dy2, 0));        // 12 left
    // F->addVertex(glm::vec3(0, dy2, 0));         // 13 right
    // F->addTriangleFan(8, {0, 1, 2, 3});         // bottom
    // F->addTriangleFan(9, {4, 7, 6, 5});         // top
    // F->addTriangleFan(10, {1, 5, 6, 2});        // front
    // F->addTriangleFan(11, {3, 7, 4, 0});        // back
    // F->addTriangleFan(12, {0, 4, 5, 1});        // left
    // F->addTriangleFan(13, {2, 6, 7, 3});        // right
    // F->updateNormals();
    // Groups.push_back(F);
  }

  glm::vec3 getSize() { return glm::vec3(Dx, Dy, Dz); }

 protected:
 private:
  float Dx, Dy, Dz;
};

}  // namespace rg

#endif  // RGGLBASICCUBOID_H
