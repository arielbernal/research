#ifndef RGGLOBJECT_H
#define RGGLOBJECT_H

#include <iostream>
#include <map>
#include <gl/rgGLHeaders.h>

namespace rg {

class GLObject {
 public:
  enum { ROOT, OBJECT3D, LIGHT, CAMERA };
  typedef std::map<std::string, GLObject*> ChildrenMap;

  GLObject(const std::string& Name, size_t Type, GLObject* Parent = nullptr)
      : Name(Name), Type(Type), Parent(Parent) {
    if (Parent) Parent->addChild(this);
  }

  std::string getName() { return Name; }

  size_t getType() { return Type; }

  std::string getTypeString() {
    switch (Type) {
      case ROOT:
        return "Root";
      case OBJECT3D:
        return "Object3D";
      case LIGHT:
        return "Light";
      case CAMERA:
        return "Camera";
      default:
        return "Unknown";
    }
    return "Unknown";
  }

  void setParent(GLObject* NewParent) {
    if (Parent) Parent->removeChild(Name);
    Parent = NewParent;
    NewParent->addChild(this);
  }

  ChildrenMap& getChildren() { return Children; }
  size_t getChildrenSize() { return Children.size(); }

 protected:
  void addParent(GLObject* O) { Parent = O; }
  void addChild(GLObject* O) { Children[O->getName()] = O; }
  void removeChild(const std::string& Name) { Children.erase(Name); }
  GLObject* getParent() { return Parent; }

 private:
  std::string Name;
  size_t Type;
  GLObject* Parent;
  ChildrenMap Children;
};

}  // namespace rg

#endif  // RGGLOBJECT_H