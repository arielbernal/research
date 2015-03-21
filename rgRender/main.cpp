#include <iostream>
#include <memory>
#include <map>
#include <vector>

namespace rg {

class GLObject {
 public:
  GLObject(const std::string& Name) : Name(Name) {}
  std::string getName() { return Name; }

 private:
  std::string Name;
};

class GLScene {
 public:
  GLScene() {}
  void init() {
    auto O1 = std::make_unique<GLObject>("O1");
    Objects[O1->getName()] = std::move(O1);
  }

 private:
  std::map<std::string, std::unique_ptr<GLObject> > Cameras;
  std::map<std::string, std::unique_ptr<GLObject> > Lights;
  std::map<std::string, std::unique_ptr<GLObject> > Objects3D;
  std::map<std::string, std::unique_ptr<GLObject> > Objects;
};
}

int main() {
  rg::GLScene S;

  return 0;
}
