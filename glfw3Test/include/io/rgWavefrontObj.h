#ifndef RGWAVEFRONTOBJ_H
#define RGWAVEFRONTOBJ_H

#include <iostream>
#include <vector>
#include <map>

#include <gl/rgGLMaterial.h>

namespace rg {

struct WavefrontFace {
  WavefrontFace(GLMaterial* Material) : Material(Material) {}
  GLMaterial* Material;
  std::vector<uint16_t> Vertices;
  std::vector<uint16_t> Normals;
  std::vector<uint16_t> UVs;
};

class WavefrontObj {
 public:
  WavefrontObj(const std::string& Name) : Name(Name) {}
  ~WavefrontObj() {}

  void addVertex(float x, float y, float z) {
    Vertices.push_back(glm::vec3(x, y, z));
  }
  void addNormal(float x, float y, float z) {
    Normals.push_back(glm::vec3(x, y, z));
  }
  void addUv(float u, float v) { UVs.push_back(glm::vec2(u, v)); }

  bool hasNormals() { return Normals.size() > 0; }
  bool hasUVs() { return UVs.size() > 0; }

  void addFace(WavefrontFace* F) { Faces.push_back(F); }

  std::string getName() { return Name; }
  void dump();
  std::vector<glm::vec3>* getVertices() { return &Vertices; }
  std::vector<glm::vec3>* getNormals() { return &Normals; }
  std::vector<glm::vec2>* getUVs() { return &UVs; }

 private:
  std::string Name;
  std::vector<glm::vec3> Vertices;
  std::vector<glm::vec3> Normals;
  std::vector<glm::vec2> UVs;
  std::vector<WavefrontFace*> Faces;
};

class WavefrontObjFile {
 public:
  typedef typename std::map<std::string, GLMaterial> MaterialMap;
  typedef typename MaterialMap::iterator MaterialIterator;
  typedef typename MaterialMap::const_iterator ConstMaterialIterator;
  typedef typename std::pair<std::string, GLMaterial> MaterialPair;

  WavefrontObjFile() : CurrentObject(0), CurrentMaterial(0) {}
  bool loadObjFile(const std::string& Filename);
  bool loadMtlFile(const std::string& Filename);
  void dump();

  WavefrontObj* getCurrentObject() { return CurrentObject; }

 private:
  std::string ObjFilename;
  std::string MtlFilename;

  std::vector<WavefrontObj*> Objects;
  MaterialMap Materials;
  WavefrontObj* CurrentObject;
  GLMaterial* CurrentMaterial;
};
}
#endif  // RGWAVEFRONTOBJ_H