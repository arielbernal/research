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
    ProjectionMatrix = glm::perspective(fov, aspect, vnear, vfar);
    VPMatrix = ProjectionMatrix * ViewMatrix;
  }

  void setProjectionMatrix(const glm::mat4& Projection) {
    ProjectionMatrix = Projection;
  }

  void setViewMatrix(const glm::mat4& View) { ViewMatrix = View; }

  glm::mat4 getProjection() { return ProjectionMatrix; }
  glm::mat4 getView() { return ViewMatrix; }
  glm::mat4 getVPMatrix() { return VPMatrix; }

 protected:
  void updateView() {
    ViewMatrix = glm::lookAt(pos, origin, orientation);
//    ViewMatrix = glm::rotate(ViewMatrix, -90.0f, glm::vec3(1, 0, 0));
//    ViewMatrix = glm::rotate(ViewMatrix, -90.0f, glm::vec3(0, 0, 1));
    VPMatrix = ProjectionMatrix * ViewMatrix;
  }

 private:
  glm::vec3 pos;
  glm::vec3 origin;
  glm::vec3 orientation;
  glm::mat4 ViewMatrix;
  glm::mat4 ProjectionMatrix;
  glm::mat4 VPMatrix;
};

}  // namespace rg

#endif  // RGCAMERA_H