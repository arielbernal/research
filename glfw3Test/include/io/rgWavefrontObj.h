#ifndef RGWAVEFRONTOBJ_H
#define RGWAVEFRONTOBJ_H

#include <vector>

namespace rg {

//struct Material {
//  std::string Name;
//  float Ka[3]; // Ambient color
//  float Kd[3]; // Diffuse color
//  float Ks[3]; // Specular color
//  float Ns;    // Specular exponent
//  float Tf[3]; // Transmision filter
//  int illum;   // Illumination model 
//  float d;     // Dissolve factor
//  float Ni;    // Index of refraction
//  std::string map_Ka; // Ambient texture
//  std::string map_Kd; // Diffuse texture
//  std::string map_Ks; // Specular texture
//
//  Material() {}
//  Material(const std::string& Name) : Name(Name) {}
//  const bool hasTextureFiles() const {
//    return map_Ka.length() > 0 || map_Kd.length() > 0 || map_Ks.length() > 0;
//  }
//};
//
//struct Face {
//  std::vector<float> Vertices;
//  std::vector<float> Normals;
//  std::vector<float> UVs;
//  Material *FaceMaterial;
//
//  Face(Material *FaceMaterial) : FaceMaterial(FaceMaterial) {}
//  Face(const Face& F) : Vertices(F.Vertices), Normals(F.Normals) , UVs(F.UVs), FaceMaterial(F.FaceMaterial) {}
//
//  void addVertex(float x, float y, float z) {
//    Vertices.push_back(x);
//    Vertices.push_back(y);
//    Vertices.push_back(z);
//  }
//
//  void addNormal(float x, float y, float z) {
//    Normals.push_back(x);
//    Normals.push_back(y);
//    Normals.push_back(z);
//  }
//
//  void addUV(float u, float v) {
//    UVs.push_back(u);
//    UVs.push_back(v);
//  }
//};
//
//class WavefrontObj {
//public: 
//  typedef typename std::vector<Face>::iterator Iterator;
//  typedef typename std::vector<Face>::const_iterator ConstIterator;
//
//  WavefrontObj(const std::string& Name, int VertexOffset) 
//  : Name(Name), HasNormals(false), HasUvs(false), VertexOffset(VertexOffset) {}
//
//  void addFace(const Face& F) { Faces.push_back(F); }
//
//  std::string getName() { return Name; }
//  std::string getName() const { return Name; }
//
//  void setVertexOffset(int Offset) { VertexOffset = Offset; }
//  void setVertexCount(int Count) { VertexCount = Count; }
//  int getVertexOffset() { return VertexOffset; }
//  int getVertexCount() { return VertexCount; }
//
//  Iterator begin() { return Faces.begin(); }
//  Iterator end() { return Faces.end(); }
//  ConstIterator begin() const { return Faces.begin(); }
//  ConstIterator end() const { return Faces.end(); }
//  size_t size() const { return Faces.size(); }
//  size_t size() { return Faces.size(); }
//
//
//  bool hasNormals() { return HasNormals; }
//  bool hasUVs() { return HasUvs; }
//  bool hasNormals() const { return HasNormals; }
//  bool hasUVs() const { return HasUvs; }
//
//  void hasNormals(bool Value) { HasNormals = Value; }
//  void hasUVs(bool Value) { HasUvs = Value; }
//private:  
//  std::string Name;
//  std::vector<Face> Faces;  
//  bool HasNormals;
//  bool HasUvs;
//  int VertexOffset;
//  int VertexCount;
//};
//


}
#endif // RGWAVEFRONTOBJ_H