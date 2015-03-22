#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <list>

#include <gl/rgGLObject.h>
#include <gl/rgGLCamera.h>

namespace rg {
//------------------------------------------
class GLLight : public GLObject {
 public:
  enum { DIRECTIONAL, POINT, SPOT };
  GLLight(const std::string& Name, size_t LightType, GLObject* Parent = nullptr)
      : GLObject(Name, LIGHT, Parent), LightType(LightType) {}

 private:
  size_t LightType;
};
//------------------------------------------
class GLObject3D : public GLObject {
 public:
  enum { CUBOID, SPHERE, CYLINDER };
  GLObject3D(const std::string& Name, size_t Object3DType,
             GLObject* Parent = nullptr)
      : GLObject(Name, OBJECT3D, Parent), Object3DType(Object3DType) {}

 private:
  size_t Object3DType;
};

class GLCuboid : public GLObject3D {
 public:
  GLCuboid(const std::string& Name, GLObject* Parent = nullptr)
      : GLObject3D(Name, CUBOID, Parent) {}
};

class GLSphere : public GLObject3D {
 public:
  GLSphere(const std::string& Name, GLObject* Parent = nullptr)
      : GLObject3D(Name, SPHERE, Parent) {}
};
//------------------------------------------

class GLScene {
 public:
  GLScene() { Root = new GLObject("Root", GLObject::ROOT); }

  ~GLScene() { deleteObjects(); }

  void init() {
    auto MainCamera = new GLCamera("MainCamera", Root);
    add(MainCamera);
    auto L1 = new GLLight("Light_01", GLLight::DIRECTIONAL, Root);
    add(L1);
    auto O1 = new GLCuboid("Cube_01", Root);
    add(O1);
    auto O2 = new GLCuboid("Cube_02", Root);
    add(O2);
    O2->setParent(O1);
    auto O3 = new GLCuboid("Cube_03", Root);
    add(O3);
    auto O4 = new GLSphere("Sphere_01", O1);
  }

  void add(GLObject3D* O) {
    Objects3D[O->getName()] = O;
    Objects[O->getName()] = O;
  }

  void add(GLLight* O) {
    Lights[O->getName()] = O;
    Objects[O->getName()] = O;
  }

  void add(GLCamera* O) {
    Cameras[O->getName()] = O;
    Objects[O->getName()] = O;
  }


  void deleteObjects() {
    for (auto e : Objects) delete e.second;
  }

  void dump() {
    for (auto e : Objects) {
      std::cout << e.second->getName() << std::endl;
    }
  }

  void dumpTree(GLObject* Node, std::string& tab) {
    if (Node != nullptr) {
      std::cout << tab << Node->getName() << std::endl;
      for (auto e : Node->getChildren()) {
        dumpTree(e.second, tab + " ");
      }
    }
  }

  void dumpTree() {
    std::string tab = "";
    dumpTree(Root, tab);
  }

 private:
  GLObject* Root;
  std::map<std::string, GLCamera*> Cameras;
  std::map<std::string, GLLight*> Lights;
  std::map<std::string, GLObject3D*> Objects3D;
  std::map<std::string, GLObject*> Objects;
};
}

int main() {
  rg::GLScene S;

  S.init();
  S.dumpTree();

  return 0;
}