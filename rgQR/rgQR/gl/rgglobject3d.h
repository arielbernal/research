#ifndef RGGLOBJECT3D_H
#define RGGLOBJECT3D_H

namespace rg {

struct GLObject3D : public GLObject {
  enum { CUBOID, SPHERE, CYLINDER };
  GLObject3D(const std::string& Name, size_t Object3DType,
             GLObject* Parent = nullptr)
      : GLObject(Name, OBJECT3D, Parent), Object3DType(Object3DType) {}

  size_t Object3DType;
  bool CastShadows;
  bool ReceiveShadows;
};

} // namespace rg
#endif // RGGLOBJECT3D_H
