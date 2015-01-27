#ifndef WORLDSYSTEM_H
#define WORLDSYSTEM_H

#include <vector>

struct Triangle {
  Triangle() {}
  Triangle(float4 &p0, float4 &p1, float4 &p2) {
    p[0] = p0;
    p[1] = p1;
    p[2] = p2;
	calculateNormal();
  }

  bool isInside(float4 &x) {
    if (dot3d(x - p[0], N) <= 0)
      return true;
	  return false;
  }

  void calculateNormal() {
	float4 v1 = p[1] - p[0];
	float4 v2 = p[2] - p[0];
	N = normal3d(v1, v2);
  }
  void scale(float k) {
    p[0] *= k;
    p[1] *= k;
    p[2] *= k;
  }
  void translate(float4 &dp) {
    p[0] += dp;
    p[1] += dp;
    p[2] += dp;
  }

  void rotateZ(float angle) {
  	float cosa = cos(angle);
  	float sina = sin(angle);
    for (size_t i = 0; i < 3; ++i) {
      float xx = p[i].x;
      float yy = p[i].y;
      p[i].x = xx * cosa - yy * sina;
      p[i].y = xx * cosa + yy * sina;
    }
  }

  float4 p[3];
  float4 N;
};

class ConvexObject {
 public:
  typedef std::vector<Triangle>::iterator Iterator;

  void addTriangle(float4 &p0, float4 &p1, float4 &p2) {
    t.push_back(Triangle(p0, p1, p2));
  }
  void addQuad(float4 &p0, float4 &p1, float4 &p2, float4 &p3) {
    t.push_back(Triangle(p0, p1, p3));
    t.push_back(Triangle(p1, p2, p3));
  }

  void scale(float k) {
    for (Iterator I = t.begin(), E = t.end(); I != E; ++I) {
      I->scale(k);
    }
  }

  bool isInside(float4 &x) {
    int i = 0;
    for (Iterator I = t.begin(), E = t.end(); I != E; ++I)
      if (!I->isInside(x)) return false;
	  return true;
  }

  void translate(float dx, float dy, float dz) {
    translate(float4(dx, dy, dz));
  }

  void translate(float4 &dp) {
    for (Iterator I = t.begin(), E = t.end(); I != E; ++I) {
      I->translate(dp);
    }
  }

  void rotateZ(float angle) {
    for (Iterator I = t.begin(), E = t.end(); I != E; ++I) {
      I->translate(-origin);
      //I->rotateZ(angle);
      I->translate(origin);
    }
  }

  std::vector<Triangle> &getTriangles() { return t; }

  void setOrigin(float x, float y, float z) { origin(x, y, z, 0); }

 protected:
  std::vector<Triangle> t;
  float4 origin;
};

class CubeObject : public ConvexObject {
 public:
  CubeObject() : CubeObject(1, 1, 1) {}
  CubeObject(float w, float d, float h) {
    float4 v0(0, 0, 0);
    float4 v1(w, 0, 0);
    float4 v2(w, d, 0);
    float4 v3(0, d, 0);
    float4 v4(0, 0, h);
    float4 v5(w, 0, h);
    float4 v6(w, d, h);
    float4 v7(0, d, h);
    addQuad(v3, v2, v1, v0);  // bottom face
    addQuad(v4, v5, v6, v7);  // top face
    addQuad(v0, v1, v5, v4);  // front face
    addQuad(v2, v3, v7, v6);  // back face
    addQuad(v3, v0, v4, v7);  // left face
    addQuad(v1, v2, v6, v5);  // right face
    setOrigin(w / 2, d / 2, h / 2);
  }
};

class TriangularPrismObject : public ConvexObject {
 public:
  TriangularPrismObject() : TriangularPrismObject(1, 1, 1) {}
  TriangularPrismObject(float w, float d, float h) {
    float4 v0(0, 0, 0);
    float4 v1(w, 0, 0);
    float4 v2(w, d, 0);
    float4 v3(0, d, 0);
    float4 v6(w, d, h);
    float4 v7(0, d, h);
    addQuad(v3, v2, v1, v0);  // bottom face
    addQuad(v0, v1, v6, v7);  // top face
    addQuad(v2, v3, v7, v6);  // back face
    addTriangle(v0, v7, v3);  // left face
    addTriangle(v1, v2, v6);  // right face
    setOrigin(w / 2, d, 0);
  }
};

class PlaneObject : public ConvexObject {
 public:
  PlaneObject() {
    float4 v0(0, 0, 0);
    float4 v1(1, 0, 0);
    float4 v2(1, 1, 0);
    float4 v3(0, 1, 0);
    addQuad(v0, v1, v2, v3);
  }
};

class TetrahedronObject : public ConvexObject {
 public:
  TetrahedronObject(float size = 1) {
    float4 v0(0, 0, 0);
    float4 v1(1, 0, 0);
    float4 v2(0.5f, sqrt(3) / 2.0f, 0);
    float4 v3(0.5f, sqrt(3) / 6.0f, sqrt(2.0f / 3.0f));
    addTriangle(v0, v2, v1);  // bottom face
    addTriangle(v0, v1, v3);
    addTriangle(v1, v2, v3);
    addTriangle(v2, v0, v3);
    setOrigin(0.5, sqrt(3) / 6.0f, sqrt(3) / 6.0f);
  }
};

class WorldSystem {
 public:
  WorldSystem() {}
  void addObject(ConvexObject &obj) { ob.push_back(obj); }

 private:
  std::vector<ConvexObject> ob;
};

#endif