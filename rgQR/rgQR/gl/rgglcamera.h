#ifndef RGGLCAMERA_H
#define RGGLCAMERA_H

#include <gl/rgglheaders.h>
#include <gl/rgglobject.h>

namespace rg {

struct GLCamera : public GLObject {
public:
  GLCamera(const std::string& Name, GLObject* Parent = nullptr)
      : GLObject(Name, CAMERA, Parent), center(0, 0, 0), up(0, 0, 1) {}

  glm::vec3 center;
  glm::vec3 up;
};

} // namespace rg

#endif // RGGLCAMERA_H
