#ifndef RGGLWAVEFRONTOBJ_H
#define RGGLWAVEFRONTOBJ_H

#include <gl/rgGLObject.h>
#include <io/rgWavefrontObj.h>

namespace rg {

class GLWavefrontObj : public GLObject {
 public:
  GLWavefrontObj(const std::string& ObjectName, WavefrontObj* WF)
      : GLObject(ObjectName), WF(WF) {
    std::cout << "------------------------" << WF->getName() << "\n";
    rebuild();
  }

 protected:
  void rebuild() {
    for (auto e : *WF->getGroupFaces()) {
      if (e.Material) std::cout << "    M: " << e.Material->Name << "\n";
      
      GroupFaces* F = new GroupFaces(*e.Material);

      std::vector<glm::vec3>* V = WF->getVertices();
      std::vector<glm::vec3>* N = WF->getNormals();
      std::vector<glm::vec2>* T = WF->getUVs();

      std::map<WavefrontFaceVertex, uint16_t> VMap;
      size_t i = 0;
      size_t idx = 0;
      for (auto e1 : e.Faces) {
        std::cout << "      Face " << i++ << "\n";
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
            std::cout << "V=" << glm::to_string(Vertex)
                      << " N=" << glm::to_string(Normal)
                      << " T=" << glm::to_string(Texture) << std::endl;
          }
        }
        uint16_t i0 = VMap[e1.V[0]];
        uint16_t i1 = VMap[e1.V[1]];
        uint16_t i2 = VMap[e1.V[2]];
        if (e1.V.size() == 4) {
            uint16_t i3 = VMap[e1.V[3]];
            F->addQuad(i0, i1, i2, i3);
        } 
        std::cout << "\n";
      }
      F->updateNormals();
      Groups.push_back(F);
    }
//     Groups.clear();

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
