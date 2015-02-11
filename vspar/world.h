#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <svector.h>

using namespace svector;

class ConvexObject;

struct Collision {
  float d;            // distance from face
  float4 N;           // normal to plane
  float4 p;           // collision point
  size_t i;           // face
  float t;            // time to collision
  bool contact;       // contact
  ConvexObject *obj;  // object
  Collision() : d(-1), N(0), i(0), t(0), contact(false), obj(0) {}
  void clear() {
    d = -1;
    N = 0;
    i = 0;
    t = 0;
    obj = 0;
    contact = false;
  }
};

class ConvexObject {
 public:
  typedef std::vector<float4>::iterator Iterator;
  ConvexObject() : triangleCounter(0), friction(0) {}

  bool getCollision(const float4 &x, const float4 &vel, Collision &c) {
    c.clear();
    c.obj = this;
    float epsilon = 0.01f;
    float dMin = 1E20;
    size_t iMin = 0;
    for (size_t i = 0; i < f.size(); ++i) {
      float4 xi = v[t[f[i]]];
      float d = dot3d(x - xi, N[i]);
      if (d > epsilon) return false;
      if (fabs(d) < dMin) {
        dMin = fabs(d);
        iMin = i;
      }
    }
    float dpV = dot3d(vel, N[iMin]);
    if (dpV > 0) return false;
    c.i = iMin;
    c.N = N[iMin];
    c.contact = (dMin < epsilon && fabs(dpV) < 10*epsilon);
//    std::cout << " dMIn = " << dMin << "  dpV = " << dpV << " v = " << vel.str() << std::endl;
    return true;
  }

  void scale(const float k) {
    for (Iterator I = v.begin(), E = v.end(); I != E; ++I) *I *= k;
  }

  void translate(const float dx, const float dy, const float dz) {
    translate(float4(dx, dy, dz));
  }

  void translate(const float4 &dp) {
    for (Iterator I = v.begin(), E = v.end(); I != E; ++I) *I += dp;
  }

  void setOrigin(float x, float y, float z) { origin(x, y, z, 0); }

  float4 calculateNormal(const float4 &p0, const float4 &p1, const float4 &p2) {
    return normal3d(p1 - p0, p2 - p0);
  }

  size_t getNumTriangles(size_t face_id) { return nt[face_id]; }

  float4 getNormal(size_t face_id) { return N[face_id]; }

  std::vector<size_t> &getFaces() { return f; }

  float4 &getFaceVertex(size_t face_id, size_t ntriangle, size_t nvertex) {
    return v[t[f[face_id] + 3 * ntriangle + nvertex]];
  }

  void printFaces() {
    std::cout << "Faces = " << f.size() << std::endl;
    for (size_t i = 0; i < f.size(); ++i) {
      size_t n = nt[i];
      std::cout << "Triangles = " << n << "  TId = " << f[i] << std::endl;
      for (size_t j = 0; j < n; ++j) {
        std::cout << "   " << t[f[i] + 3 * j + 0] << std::endl;
        std::cout << "   " << t[f[i] + 3 * j + 1] << std::endl;
        std::cout << "   " << t[f[i] + 3 * j + 2] << std::endl;
        std::cout << "   ----\n";
      }
    }
  }

  void addTriangleFace(size_t i0, size_t i1, size_t i2) {
    t.push_back(i0);
    t.push_back(i1);
    t.push_back(i2);
    nt.push_back(1);
    f.push_back(3 * triangleCounter);
    triangleCounter++;
    N.push_back(calculateNormal(v[i0], v[i1], v[i2]));
  }

  void addQuadFace(size_t i0, size_t i1, size_t i2, size_t i3) {
    t.push_back(i0);
    t.push_back(i1);
    t.push_back(i3);
    t.push_back(i1);
    t.push_back(i2);
    t.push_back(i3);
    nt.push_back(2);
    f.push_back(3 * triangleCounter);
    triangleCounter += 2;
    N.push_back(calculateNormal(v[i0], v[i1], v[i2]));
  }

  void setColor(const float4 &c) { color = c; }

  float4 &getColor() { return color; }

  void setName(const std::string &str) { name = str; }
  std::string &getName() { return name; }

  void setFriction(float f) { friction = f; }
  float getFriction() { return friction; }

 protected:
  std::vector<float4> v;   // vertices
  std::vector<size_t> t;   // triangles
  std::vector<size_t> nt;  // number of triangles per face
  std::vector<size_t> f;   // faces
  std::vector<float4> N;   // normals;
  size_t triangleCounter;
  float4 origin;
  float4 color;
  float friction;
  std::string name;
};

class CubeObject : public ConvexObject {
 public:
  CubeObject(float w = 1, float d = 1, float h = 1) {
    v.push_back(float4(0, 0, 0));
    v.push_back(float4(w, 0, 0));
    v.push_back(float4(w, d, 0));
    v.push_back(float4(0, d, 0));
    v.push_back(float4(0, 0, h));
    v.push_back(float4(w, 0, h));
    v.push_back(float4(w, d, h));
    v.push_back(float4(0, d, h));
    addQuadFace(3, 2, 1, 0);
    addQuadFace(4, 5, 6, 7);
    addQuadFace(0, 1, 5, 4);
    addQuadFace(2, 3, 7, 6);
    addQuadFace(3, 0, 4, 7);
    addQuadFace(1, 2, 6, 5);
    setOrigin(w / 2, d / 2, h / 2);
  }
};

class TriangularPrismObject : public ConvexObject {
 public:
  TriangularPrismObject(float w = 1, float d = 1, float h = 1) {
    v.push_back(float4(0, 0, 0));
    v.push_back(float4(w, 0, 0));
    v.push_back(float4(w, d, 0));
    v.push_back(float4(0, d, 0));
    v.push_back(float4(w, d, h));
    v.push_back(float4(0, d, h));
    addQuadFace(3, 2, 1, 0);   // bottom face
    addQuadFace(0, 1, 4, 5);   // top face
    addQuadFace(2, 3, 5, 4);   // back face
    addTriangleFace(0, 5, 3);  // left face
    addTriangleFace(1, 2, 4);  // right face
    setOrigin(w / 2, d, 0);
  }
};

class TetrahedronObject : public ConvexObject {
 public:
  TetrahedronObject() {
    v.push_back(float4(0, 0, 0));
    v.push_back(float4(1, 0, 0));
    v.push_back(float4(0.5f, sqrt(3) / 2.0f, 0));
    v.push_back(float4(0.5f, sqrt(3) / 6.0f, sqrt(2.0f / 3.0f)));
    addTriangleFace(0, 2, 1);  // bottom face
    addTriangleFace(0, 1, 3);
    addTriangleFace(1, 2, 3);
    addTriangleFace(2, 0, 3);
    setOrigin(0.5, sqrt(3) / 6.0f, sqrt(3) / 6.0f);
  }
};

class World {
 public:
  typedef std::vector<ConvexObject *>::iterator Iterator;
  World() {}

  void addCube(float w = 1, float d = 1, float h = 1) {
    CubeObject *c = new CubeObject(w, d, h);
    ob.push_back(c);
  }

  void addTetrahedron() {
    TetrahedronObject *t = new TetrahedronObject();
    ob.push_back(t);
  }

  void addTriangularPrism(float w = 1, float d = 1, float h = 1) {
    TriangularPrismObject *p = new TriangularPrismObject(w, d, h);
    ob.push_back(p);
  }

  bool checkCollision(const float4 &x, const float4 &vel, Collision &cmin) {
    for (Iterator I = begin(), E = end(); I != E; ++I) {
      if ((*I)->getCollision(x, vel, cmin)) return true;
    }
    return false;
  }

  void push_back(ConvexObject *obj) { ob.push_back(obj); }

  Iterator begin() { return ob.begin(); }

  Iterator end() { return ob.end(); }

 private:
  std::vector<ConvexObject *> ob;
};

#endif