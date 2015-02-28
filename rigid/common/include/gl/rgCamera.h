#ifndef RGCAMERA_H
#define RGCAMERA_H

#include <gl/rgGLHeaders.h>

namespace rg {

class Camera {
 public:
  Camera() : pos(10, 10, 10), origin(0, 0, 0), orientation(0, 0, 1) {
    setPerspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    updateView();
  }

  void setPosition(float x, float y, float z) {
    pos = glm::vec3(x, y, z);
    updateView();
  }
  glm::vec3 getPosition() { return pos; }

  void setOrigin(float x, float y, float z) {
    origin = glm::vec3(x, y, z);
    updateView();
  }
  glm::vec3 getOrigin() { return origin; }

  void setOrientation(float x, float y, float z) {
    orientation = glm::vec3(x, y, z);
    updateView();
  }
  glm::vec3 getOrientation() { return orientation; }

  void setPerspective(float fov, float aspect, float vnear, float vfar) {
    PMatrix = glm::perspective(fov, aspect, vnear, vfar);
  }

  void setPMatrix(const glm::mat4& Projection) { PMatrix = Projection; }

  void setVMatrix(const glm::mat4& View) { VMatrix = View; }

  glm::mat4 getPMatrix() const { return PMatrix; }
  glm::mat4 getVMatrix() const { return VMatrix; }

 protected:
  void updateView() { VMatrix = glm::lookAt(pos, origin, orientation); }

 private:
  glm::vec3 pos;
  glm::vec3 origin;
  glm::vec3 orientation;
  glm::mat4 VMatrix;
  glm::mat4 PMatrix;
};

}  // namespace rg

#endif  // RGCAMERA_H