#ifndef RGGLCAMERA_H
#define RGGLCAMERA_H

#include <gl/rgglheaders.h>
#include <gl/rgglobject.h>

namespace rg {

class GLCamera : public GLObject {
public:
  GLCamera(const std::string& Name, GLObject* Parent = nullptr)
      : GLObject(Name, CAMERA, Parent),
        Enable(true),
        center(0, 0, 0),
        up(0, 0, 1) {}

  glm::vec3 getCenter() const { return center; }
  void setCenter(float x, float y, float z) { center = glm::vec3(x, y, z); }
  void setCenter(float v, int idx) { center[idx] = v; }

  glm::vec3 getUp() const { return up; }
  void setUp(float x, float y, float z) { up = glm::vec3(x, y, z); }
  void setUp(float v, int idx) { up[idx] = v; }

private:
  bool Enable;
  glm::vec3 center;
  glm::vec3 up;
};

} // namespace rg

#endif // RGGLCAMERA_H
