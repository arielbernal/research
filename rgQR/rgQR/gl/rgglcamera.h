#ifndef RGGLCAMERA_H
#define RGGLCAMERA_H

#include <gl/rgglheaders.h>
#include <gl/rgglobject.h>

namespace rg {

struct GLCamera : public GLObject {
 public:
  GLCamera(const std::string& Name, GLObject* Parent = nullptr)
      : GLObject(Name, CAMERA, Parent),
        fov(0),
        near(0),
        far(0),
        view_x(0),
        view_y(0),
        view_w(0),
        view_h(0) {}

  size_t projection;
  float fov;
  float near;
  float far;
  float view_x;
  float view_y;
  float view_w;
  float view_h;
};

}  // namespace rg

#endif  // RGGLCAMERA_H
