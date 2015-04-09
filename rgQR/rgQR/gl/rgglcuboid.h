#ifndef RGGLCUBOID_H
#define RGGLCUBOID_H

#include <gl/rgglheaders.h>
#include <gl/rgglobject3d.h>

namespace rg {

struct GLCuboid : public GLObject3D {
public:
  GLCuboid(const std::string& Name, GLObject* Parent = nullptr)
      : GLObject3D(Name, CUBOID, Parent), Size(1, 1, 1) {}

  glm::vec3 Size;
};

} // namespace rg

#endif // RGGLCUBOID_H
