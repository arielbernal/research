#ifndef RGGLCAMERA_H
#define RGGLCAMERA_H

#include <gl/rgGLHeaders.h>

namespace rg {

class GLCamera {
 public:
  GLCamera(const std::string& CameraName)
      : Enabled(true),
        HasChanged(true),
        CameraName(CameraName),
        pos(10, 10, 10),
        origin(0, 0, 0),
        orientation(0, 0, 1) {
    setPerspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    updateView();
  }

  GLCamera(const std::string& CameraName, const glm::vec3& p,
           const glm::vec3& o, const glm::vec3& orient)
      : Enabled(true), CameraName(CameraName) {
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
    VMatrix = glm::lookAt(pos, origin, orientation);
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
};

}  // namespace rg

#endif  // RGGLCAMERA_H