#ifndef SCENE_H
#define SCENE_H

#include <map>

#include <gl/rgglcamera.h>
#include <gl/rgglobject.h>
#include <gl/rggllight.h>
#include <gl/rgglobject3d.h>

namespace rg {

class Scene {
 public:
  Scene() : Root(new GLObject("ROOT", GLObject::ROOT)), CurrentObject(Root) {
    addObjectMap(Root);
  }

  ~Scene() {
    for (auto& e : Objects)
      delete e.second;
    Objects.clear();
  }

  bool addCamera(const std::string& Name, const std::string& Parent = "ROOT") {
    auto itp = Objects.find(Parent);
    auto it = Objects.find(Name);
    if (itp != Objects.end() && it == Objects.end()) {
      GLCamera* Obj = new GLCamera(Name, itp->second);
      return addObjectMap(Obj);
    }
    return false;
  }

  bool addLight(const std::string& Name, const std::string& Parent = "ROOT") {
    auto itp = Objects.find(Parent);
    auto it = Objects.find(Name);
    if (itp != Objects.end() && it == Objects.end()) {
      GLLight* Obj = new GLLight(Name, GLLight::DIRECTIONAL, itp->second);
      return addObjectMap(Obj);
    }
    return false;
  }

  bool addObject3D(const std::string& Name,
                   size_t Object3dType,
                   const std::string& Parent = "ROOT") {
    auto itp = Objects.find(Parent);
    auto it = Objects.find(Name);
    if (itp != Objects.end() && it == Objects.end()) {
      GLObject3D* Obj = new GLObject3D(Name, Object3dType, itp->second);
      return addObjectMap(Obj);
    }
    return false;
  }

  bool setCurrent(const std::string& Name) {
    auto it = Objects.find(Name);
    if (Objects.find(Name) != Objects.end()) {
      CurrentObject = it->second;
      return true;
    }
    return false;
  }

  void setCurrentToRoot() { CurrentObject = Root; }

  bool deleteObject(const std::string& Name) {
    // Need to delete all children
    //    auto it = Objects.find(Name);
    //    if (it != Objects.end()) {
    //      Objects.erase(it);
    //      return true;
    //    }
    return false;
  }

  bool renameObject(const std::string& Name, const std::string& NewName) {
    auto it0 = Objects.find(Name);
    auto it1 = Objects.find(NewName);
    if (it0 != Objects.end() && it1 == Objects.end()) {
      GLObject* O = it0->second;
      O->setName(NewName);
      Objects.erase(it0);
      Objects[NewName] = O;
      return true;
    }
    return false;
  }

  GLObject* getFirstObject() {
    if (Root->getChildrenSize() > 0)
      return Root->getChildren().begin()->second;
    else
      return nullptr;
  }

  GLObject* getObject(const std::string& Name) {
    auto it = Objects.find(Name);
    if (it != Objects.end()) {
      return it->second;
    }
    return nullptr;
  }

  GLObject* getRoot() { return Root; }

 protected:
  bool addObjectMap(GLObject* O) {
    if (Objects.find(O->getName()) == Objects.end()) {
      std::cout << "Adding " << O->getName() << std::endl;
      Objects[O->getName()] = O;
      return true;
    }
    return false;
  }

 private:
  GLObject* Root;
  GLObject* CurrentObject;
  std::map<std::string, GLObject*> Objects;
};

}  // namespace rg
#endif  // SCENE_H
