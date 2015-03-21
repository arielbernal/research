#ifndef RGGLWAVEFRONTOBJ_H
#define RGGLWAVEFRONTOBJ_H

#include <gl/rgGLObject.h>
#include <io/rgWavefrontObj.h>

namespace rg {

class GLWavefrontObj : public GLObject {
 public:
  GLWavefrontObj(const std::string& ObjectName, WavefrontObjPtr& WF)
      : GLObject(ObjectName) {
    rebuild(WF);
  }

 protected:
  void rebuild(WavefrontObjPtr& WF) {
    clearGroups();
    for (auto e : *WF->getGroupFaces()) {

      GLMaterialPtr Material = e.Material;
      if (!Material) Material = GLMaterialDefault;
      GroupFaces* F = new GroupFaces(Material);

      std::vector<glm::vec3>* V = WF->getVertices();
      std::vector<glm::vec3>* N = WF->getNormals();
      std::vector<glm::vec2>* T = WF->getUVs();

      std::map<WavefrontFaceVertex, uint32_t> VMap;
      size_t idx = 0;
      for (auto e1 : e.Faces) {
        for (auto e2 : e1.V) {
          if (!VMap[e2]) {
            VMap[e2] = idx++;
            glm::vec3 Vertex(0.0f);
            glm::vec3 Normal(0.0f);
            glm::vec2 Texture(0.0f);
            if (e2.v >= 0) Vertex = (*V)[e2.v];
            if (e2.n >= 0) Normal = (*N)[e2.n];
            if (e2.t >= 0) Texture = (*T)[e2.t];
            F->addVertex(Vertex, Normal, Texture);
          }
        }
        uint32_t i0 = VMap[e1.V[0]];
        uint32_t i1 = VMap[e1.V[1]];
        uint32_t i2 = VMap[e1.V[2]];
        if (e1.V.size() == 4) {
          uint32_t i3 = VMap[e1.V[3]];
          F->addQuad(i0, i1, i2, i3);
        } else {
          F->addTriangle(i0, i1, i2);
        }
      }
      F->updateNormals();
      Groups.push_back(F);
    }
  }
};

}  // namespace rg

#endif  // RGGLWAVEFRONTOBJ_H
