#ifndef RGGLCAMERA_H
#define RGGLCAMERA_H

#include <gl/rgGLHeaders.h>
#include <glm/gtc/quaternion.hpp>
#include <math/rgSvector.h>

namespace rg {

class GLCamera {
 public:
  GLCamera(const std::string& CameraName)
      : Enabled(true),
        HasChanged(true),
        CameraName(CameraName),
        pos(10, 10, 10),
        origin(0, 0, 0),
        orientation(0, 1, 0),
        rot(glm::mat4(1)),
        qRotation(glm::quat(1, 0, 0, 0)) {
    setPerspective(3.1415926f / 4.0f, 4.0f / 3.0f, 0.1f, 100.0f);
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
    float xe2 = euler.x / 2;  // roll
    float ye2 = euler.y / 2;  // pitch
    float ze2 = euler.z / 2;  // yaw
    float cr = cos(xe2);
    float cp = cos(ye2);
    float cy = cos(ze2);
    float sr = sin(xe2);
    float sp = sin(ye2);
    float sy = sin(ze2);
    float cpcy = cp * cy;
    float spsy = sp * sy;
    float spcy = sp * cy;
    float cpsy = cp * sy;
    float tw = cr * cpcy + sr * spsy;
    float tx = sr * cpcy - cr * spsy;
    float ty = cr * spcy + sr * cpsy;
    float tz = cr * cpsy - sr * spcy;
    glm::quat q(tw, tx, ty, tz);
    return q;
  }

  glm::quat axis(const glm::quat& q) {
    glm::quat qt = glm::normalize(q);
    float temp_angle = acos(q.w) * 2;
    float vnorm = std::sqrt(1 - q.w * q.w);
    if (vnorm < 0.001)
      qt = glm::quat(0, 0, 0, 1);
    else
      qt = qt / vnorm;
    qt.w = temp_angle;
    return qt;
  }

  void rotationMatrix(const glm::quat& q, float* Matrix) {
    float xx = q.x * q.x;
    float xy = q.x * q.y;
    float xz = q.x * q.z;
    float xw = q.w * q.x;
    float yy = q.y * q.y;
    float yz = q.y * q.z;
    float yw = q.w * q.y;
    float zz = q.z * q.z;
    float zw = q.w * q.z;

    Matrix[0] = 1 - 2 * (yy + zz);
    Matrix[1] = 2 * (xy - zw);
    Matrix[2] = 2 * (xz + yw);

    Matrix[4] = 2 * (xy + zw);
    Matrix[5] = 1 - 2 * (xx + zz);
    Matrix[6] = 2 * (yz - xw);

    Matrix[8] = 2 * (xz - yw);
    Matrix[9] = 2 * (yz + xw);
    Matrix[10] = 1 - 2 * (xx + yy);

    Matrix[3] = Matrix[7] = Matrix[11] = Matrix[12] = Matrix[13] = Matrix[14] =
        0;
    Matrix[15] = 1;
  }

  void printQuat(const std::string& text, const glm::quat& q) {
    std::cout << text << " [" << q.x << ", " << q.y << ", " << q.z << ", "
              << q.w << "]\n";
  }
  void rotate(float dx, float dy) {
    float yaw = dy;
    float pitch = -dx;
    float roll = 0;
    glm::quat fromEuler = eulerToQuat(glm::vec3(0, pitch, yaw));
    qRotation = qRotation * fromEuler;
    rotationMatrix(qRotation, &rot[0][0]);
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