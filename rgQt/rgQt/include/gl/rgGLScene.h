#ifndef RGGLSCENE_H
#define RGGLSCENE_H

#include <gl/rgGLHeaders.h>
#include <gl/rgGLObject.h>
#include <gl/rgGLObject3D.h>
#include <gl/rgGLCuboid.h>
#include <gl/rgGLLight.h>
#include <gl/rgGLCamera.h>
#include <io/jsoncons/json.hpp>

namespace rg {

class GLSphere : public GLObject3D {
 public:
  GLSphere(const std::string& Name, GLObject* Parent = nullptr)
      : GLObject3D(Name, SPHERE, Parent) {}
};

class GLScene {
 public:
  GLScene() {
    Root = new GLObject("Root", GLObject::ROOT);
    Objects["Root"] = Root;
  }

  ~GLScene() { deleteObjects(); }

  void loadFromJsonFile(const std::string& JsonFileName) {
    jsoncons::json objects = jsoncons::json::parse_file("scene1.json");
    for (size_t i = 0; i < objects.size(); ++i) {
      std::string ObjType = objects[i].get("Object").as<std::string>();
      std::string Name = objects[i].get("Name").as<std::string>();
      std::string ParentName = objects[i].get("Parent").as<std::string>();
      if (ObjType == "CAMERA") {
        auto Camera = new GLCamera(Name);
        add(Camera, ParentName);
        continue;
      }
      if (ObjType == "LIGHT") {
        std::string Type = objects[i].get("Type").as<std::string>();
        size_t LightType = GLLight::DIRECTIONAL;
        if (Type == "DIRECTIONAL") LightType = GLLight::DIRECTIONAL;
        if (Type == "POINT") LightType = GLLight::POINT;
        if (Type == "SPOT") LightType = GLLight::SPOT;
        auto Light = new GLLight(Name, LightType);
        add(Light, ParentName);
      }
      if (ObjType == "OBJECT3D") {
        std::string Type = objects[i].get("Type").as<std::string>();
        if (Type == "CUBOID") {
          auto Cuboid = new GLCuboid(Name);
          add(Cuboid, ParentName);
        }
        if (Type == "SPHERE") {
          auto Sphere = new GLSphere(Name);
          add(Sphere, ParentName);
        }
      }
    }
  }
  
  void add(GLObject* O, const std::string& ParentName = "") {
    std::string Name = ParentName;
    if (Name.empty()) Name = "Root";
    GLObject* Parent = Objects[Name];
    O->setParent(Parent);
    Objects[O->getName()] = O;
    if (O->getType() == GLObject::OBJECT3D) Objects3D[O->getName()] = (GLObject3D*) O;
    if (O->getType() == GLObject::LIGHT) Lights[O->getName()] = (GLLight*) O;
    if (O->getType() == GLObject::CAMERA) Cameras[O->getName()] = (GLCamera*) O;
  }

  void deleteObjects() {
    for (auto e : Objects) delete e.second;
  }

  void dump() {
    for (auto e : Objects) {
      std::cout << e.second->getName() << std::endl;
    }
  }

  void dumpTree(GLObject* Node, const std::string& tab) {
    if (Node != nullptr) {
      std::cout << tab << Node->getName();
      if (Node->getType() == GLObject::OBJECT3D) std::cout << " -> " << ((GLObject3D*) Node)->getTypeString();
      if (Node->getType() == GLObject::LIGHT) std::cout << " -> " << ((GLLight*) Node)->getTypeString();
      if (Node->getType() == GLObject::CAMERA) std::cout << " -> Camera";
      std::cout << std::endl;
      for (auto e : Node->getChildren()) {
        dumpTree(e.second, tab + "   ");
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

}  // namespace rg

#endif  // RGGLSCENE_H
