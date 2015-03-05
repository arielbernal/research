#ifndef RGGLCAMERA_H
#define RGGLCAMERA_H

#include <gl/rgGLHeaders.h>
#include <glm/gtc/quaternion.hpp>

namespace rg {

class GLCamera {
 public:
  GLCamera(const std::string& CameraName)
      : Enabled(true),
        HasChanged(true),
        CameraName(CameraName),
        pos(10, 10, 10),
        origin(0, 0, 0),
        orientation(0, 0, 1),
        rot(glm::mat4(1)) {
    setPerspective(3.1415926f/4.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    updateView();
  }

  GLCamera(const std::string& CameraName, const glm::vec3& p,
           const glm::vec3& o, const glm::vec3& orient)
           : Enabled(true), CameraName(CameraName), rot(glm::mat4(1)) {
    pos = p;
    origin = o;
    orientation = orient;
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



  glm::quat eulerToQuat(const glm::vec3& euler) {

  }
  void rotate(float dx, float dy) {
      glm::quat qx(1.0f, 0.0f, 0.0f, dx);
      glm::quat qy(0.0f, 1.0f, 0.0f, dy);
      glm::quat qz(0.0f, 0.0f, 1.0f, 0.0f);
      glm::quat fromEuler = (qx * qy) * qz;
      qRotation = qRotation * fromEuler;
      rot = glm::mat4_cast(qRotation);
      updateView();
  }


  void setPerspective(float fov, float aspect, float vnear, float vfar) {
    PMatrix = glm::perspective(fov, aspect, vnear, vfar);
    HasChanged = true;
  }

  void setPMatrix(const glm::mat4& Projection) {
    PMatrix = Projection;
    HasChanged = true;
  }
  void setVMatrix(const glm::mat4& View) {
    VMatrix = View;
    HasChanged = true;
  }
  glm::mat4 getPMatrix() const { return PMatrix; }
  glm::mat4 getVMatrix() const { return VMatrix; }

  std::string getName() { return CameraName; }

  void enable() { Enabled = true; }
  void disable() { Enabled = false; }
  bool isEnabled() { return Enabled; }

  void changeCommited() { HasChanged = false; }
  bool hasChanged() { return HasChanged; }

 protected:
  void updateView() {
    VMatrix = glm::lookAt(pos, origin, orientation) * rot;
    HasChanged = true;
  }

 private:
  bool Enabled;
  bool HasChanged;
  std::string CameraName;
  glm::vec3 pos;
  glm::vec3 origin;
  glm::vec3 orientation;
  glm::mat4 VMatrix;
  glm::mat4 PMatrix;

  glm::quat qRotation;
  glm::mat4 rot;
};

}  // namespace rg

#endif  // RGGLCAMERA_H