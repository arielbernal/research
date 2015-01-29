#ifndef WORLDSYSTEM_H
#define WORLDSYSTEM_H

#include <vector>
#include <svector.h>

using namespace svector;

class ConvexObject;

struct Collision {
  float d;            // distance from triangle plane
  float4 N;           // normal to plane
  size_t i;           // Object face
  ConvexObject *obj;  // object
  Collision() : d(-1), N(0), i(0), obj(0) {}
  void clear() {
    d = -1;
    N = 0;
    i = 0;
    obj = 0;
  }
};

class ConvexObject {
 public:
  typedef std::vector<float4>::iterator Iterator;
  ConvexObject() : triangleCounter(0), friction(0) {}

  bool getCollision(const float4 &x, Collision &c) {
    c.d = 1E10;
    for (size_t i = 0; i < f.size(); ++i) {
      float4 v0 = v[t[f[i]]];
      float d = dot3d(x - v0, N[i]);
      // std::cout << "i = " << i << "  d = " << d << std::endl;
      if (d > 0) {
        c.clear();
        return false;
      }
      if (fabs(d) < c.d) {
        c.d = fabs(d);
        c.N = N[i];
        c.i = i;
      }
    }
    c.obj = this;
    return true;
  }

  bool getCollision(const float4 &p0, const float4 &p1, float &d) {
    float4 dp = p1 - p0;
    for (size_t i = 0; i < f.size(); ++i) {
      float4 dv = v[t[f[i]]] - p0;
      float tnum = dot3d(dv, N[i]);
      float tden = dot3d(dp, N[i]);
      if (tden == 0) {
        d = 0;
        return true;
      }
      float t = tnum / tden;
      if (t <= 0 || t > 1) continue;


    }
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

  float4 calculateNormal(float4 p0, float4 p1, float4 p2) {
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
  CubeObject() : CubeObject(1, 1, 1) {}
  CubeObject(float w, float d, float h) {
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
  TriangularPrismObject() : TriangularPrismObject(1, 1, 1) {}
  TriangularPrismObject(float w, float d, float h) {
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

class WorldSystem {
 public:
  typedef std::vector<ConvexObject *>::iterator Iterator;
  WorldSystem() {}

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

  bool checkCollision(const float4 &x) {
    for (Iterator I = begin(), E = end(); I != E; ++I)
      if ((*I)->getCollision(x, c)) return true;
    c.clear();
    return false;
  }

  bool checkCollision(const float4 &x, Collision &c) {
    for (Iterator I = begin(), E = end(); I != E; ++I)
      if ((*I)->getCollision(x, c)) return true;
    c.clear();
    return false;
  }

  void push_back(ConvexObject *obj) { ob.push_back(obj); }

  Iterator begin() { return ob.begin(); }

  Iterator end() { return ob.end(); }

  Collision &getLastCollision() { return c; }
  float4 &getLastCollisionNormal() { return c.N; }
  float getLastCollisionDistance() { return c.d; }

 private:
  std::vector<ConvexObject *> ob;
  Collision c;
};

#endif