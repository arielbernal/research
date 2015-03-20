#ifndef RGWAVEFRONTOBJ_H
#define RGWAVEFRONTOBJ_H

#include <iostream>
#include <vector>
#include <map>

#include <gl/rgGLMaterial.h>

namespace rg {

struct WavefrontFaceVertex {
  WavefrontFaceVertex(int16_t v, int16_t n, int16_t t) : v(v), n(n), t(t) {}
  int16_t v;
  int16_t n;
  int16_t t;
};

inline bool operator<(const WavefrontFaceVertex& lhs,
                      const WavefrontFaceVertex& rhs) {
  if (lhs.v != rhs.v)
    return lhs.v < rhs.v;
  else if (lhs.n != rhs.n)
    return lhs.n < rhs.n;
  return lhs.t < rhs.t;
}

struct WavefrontFace {
  std::vector<WavefrontFaceVertex> V;
  void addPoint(int16_t v, int16_t n, int16_t t) {
    V.push_back(WavefrontFaceVertex(v, n, t));
  }
};

struct WavefrontGroupFace {
  WavefrontGroupFace(GLMaterialPtr& Material)
      : Material(Material), CurrentFace(0) {}

  GLMaterialPtr Material;
  void addFace() {
    WavefrontFace Face;
    Faces.push_back(Face);
    CurrentFace = &Faces.back();
  }

  void addPoint(int16_t v, int16_t n, int16_t t) {
    if (!CurrentFace) addFace();
    CurrentFace->addPoint(v, n, t);
  }
  std::vector<WavefrontFace> Faces;
  WavefrontFace* CurrentFace;
};

class WavefrontObj {
 public:
  WavefrontObj(const std::string& Name) : Name(Name), CurrentGroupFace(0) {}
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

  void addGroupFace(GLMaterialPtr& Material) {
    GroupFaces.push_back(WavefrontGroupFace(Material));
    CurrentGroupFace = &GroupFaces.back();
  }

  void addFace() {
    if (!CurrentGroupFace) addGroupFace(GLMaterialDefault);
    CurrentGroupFace->addFace();
  }

  void addFacePoint(int16_t v, int16_t n, int16_t t) {
    CurrentGroupFace->addPoint(v, n, t);
  }

  std::vector<WavefrontGroupFace>* getGroupFaces() { return &GroupFaces; }

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
  std::vector<WavefrontGroupFace> GroupFaces;
  WavefrontGroupFace* CurrentGroupFace;
};

typedef std::shared_ptr<WavefrontObj> WavefrontObjPtr;

class WavefrontObjFile {
 public:
  typedef std::map<std::string, WavefrontObjPtr> ObjectMap;
  typedef std::map<std::string, GLMaterialPtr> MaterialMap;
  typedef MaterialMap::iterator MaterialIterator;
  typedef MaterialMap::const_iterator ConstMaterialIterator;
  typedef std::pair<std::string, GLMaterialPtr> MaterialPair;

  WavefrontObjFile() : CurrentObject(0), CurrentMaterial(0) {}
  bool loadObjFile(const std::string& Filename);
  bool loadMtlFile(const std::string& Filename);
  void dump();

  WavefrontObjPtr getCurrentObject() { return CurrentObject; }

  WavefrontObjPtr getObject(const std::string& Name) { return Objects[Name]; }

 private:
  std::string ObjFilename;
  std::string MtlFilename;

  ObjectMap Objects;
  MaterialMap Materials;
  WavefrontObjPtr CurrentObject;
  GLMaterialPtr CurrentMaterial;
};
}
#endif  // RGWAVEFRONTOBJ_H