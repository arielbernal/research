#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <list>

namespace rg {

class GLObject : public std::enable_shared_from_this<GLObject> {
 public:
  enum { ROOT, OBJECT3D, LIGHT, CAMERA };
  GLObject(const std::string& Name, size_t Type) : Name(Name), Type(Type) {}
  std::string getName() { return Name; }

  void moveTo(std::shared_ptr<GLObject> NewParent) {
    if(Parent) Parent->removeChild(Name);
    Parent = NewParent;
    NewParent->addChild(shared_from_this());
  }
  std::map<std::string, std::weak_ptr<GLObject> >& getChildren() { return Children; }

 protected:
  void addParent(std::shared_ptr<GLObject>& O) { Parent = O; }
  void addChild(std::shared_ptr<GLObject>& O) { 
      Children[O->getName()] = O; 
  }
  void removeChild(const std::string& Name) { Children.erase(Name); }

 private:
  std::string Name;
  size_t Type;
  std::shared_ptr<GLObject> Parent;
  std::map<std::string, std::weak_ptr<GLObject> > Children;
};

class GLObject3D : public GLObject {
 public:
  enum { CUBOID, SPHERE, CYLINDER };
  GLObject3D(const std::string& Name, size_t Object3DType)
      : GLObject(Name, OBJECT3D), Object3DType(Object3DType) {}

 private:
  size_t Object3DType;
};

class GLCuboid : public GLObject3D {
 public:
  GLCuboid(const std::string& Name) : GLObject3D(Name, CUBOID) {}
};

class GLScene {
 public:
  typedef std::shared_ptr<GLObject3D> GLObject3DPtr;
  typedef std::shared_ptr<GLObject> GLObjectPtr;
  GLScene() { Root = std::make_shared<GLObject>("Root", GLObject::ROOT); }
  void init() {
    auto O1 = std::make_shared<GLCuboid>("Cube_01");
    add(O1);
    auto O2 = std::make_shared<GLCuboid>("Cube_02");
    add(O2);
    O2->moveTo(O1);
  }
  void add(GLObject3DPtr O) {
   
    Objects3D[O->getName()] = O;
    Objects[O->getName()] = O;
  }

  void dump() {
    for (auto e : Objects) {
      std::cout << e.second->getName() << std::endl;
    }
  }


  void dumpTree(std::shared_ptr<GLObject>& Node, std::string& tab) {
      if (Node != nullptr) {
          //std::shared_ptr<GLObject> N = Node.lock();
          std::cout << tab << Node->getName() << std::endl;
          tab += "  ";
          for (auto e : Node->getChildren()) {
              std::shared_ptr<GLObject> N = e.second.lock();
              dumpTree(N, tab);
          }

      }
  }
  void dumpTree() {
      std::string tab = "";
      dumpTree(Root, tab);
  }
 private:
  GLObjectPtr Root;
  std::map<std::string, std::shared_ptr<GLObject> > Cameras;
  std::map<std::string, std::shared_ptr<GLObject> > Lights;
  std::map<std::string, GLObject3DPtr> Objects3D;
  std::map<std::string, GLObjectPtr> Objects;
};
}

int main() {
  rg::GLScene S;

  S.init();
  S.dumpTree();

  return 0;
}