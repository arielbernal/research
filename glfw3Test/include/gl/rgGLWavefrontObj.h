#ifndef RGGLWAVEFRONTOBJ_H
#define RGGLWAVEFRONTOBJ_H

#include <gl/rgGLObject.h>
#include <io/rgWavefrontObj.h>

namespace rg {

class GLWavefrontObj : public GLObject {
 public:
  GLWavefrontObj(const std::string& ObjectName, WavefrontObj* WF)
      : GLObject(ObjectName), WF(WF) {
    rebuild();
  }

 protected:
  void rebuild() {
    // Groups.clear();

    // GLMaterial MatRed("Red");
    // F = new GroupFaces(MatCyan);  // right
    // F->addVertex(glm::vec3(-dx2, dy2, -dz2));
    // F->addQuad(0, 3, 2, 1);
    // F->updateNormals();
    // Groups.push_back(F);
  }

 private:
  WavefrontObj* WF;
};

}  // namespace rg

#endif  // RGGLWAVEFRONTOBJ_H
