#ifndef RGGLOBJECT
#define RGGLOBJECT

#include <iostream>
#include <map>

#include <gl/rgglheaders.h>

namespace rg {

class GLObject {
public:
  enum { ROOT, OBJECT3D, LIGHT, CAMERA };
  typedef std::map<size_t, GLObject*> ChildrenMap;

  GLObject(const std::string& Name, size_t Type, GLObject* Parent = nullptr)
      : Id(size_t(this)),
        Name(Name),
        Type(Type),
        Parent(Parent),
        pos(0, 0, 0),
        rot(0, 0, 0),
        scale(0, 0, 0),
        Enabled(true) {
    if (Parent)
      Parent->addChild(this);
  }

  size_t getId() { return Id; }

  std::string getName() { return Name; }
  void setName(const std::string& S) { Name = S; }

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
    if (Parent)
      Parent->removeChild(Id);
    Parent = NewParent;
    NewParent->addChild(this);
  }

  ChildrenMap& getChildren() { return Children; }

  size_t getChildrenSize() { return Children.size(); }

  glm::vec3 getPosition() const { return pos; }
  void setPosition(float x, float y, float z) { pos = glm::vec3(x, y, z); }
  void setPosition(float v, int idx) { pos[idx] = v; }

  glm::vec3 getRotation() const { return rot; }
  void setRotation(float x, float y, float z) { rot = glm::vec3(x, y, z); }
  void setRotation(float v, int idx) { rot[idx] = v; }

  glm::vec3 getScale() const { return scale; }
  void setScale(float x, float y, float z) { scale = glm::vec3(x, y, z); }
  void setScale(float v, int idx) { scale[idx] = v; }

protected:
  void addParent(GLObject* O) { Parent = O; }
  void addChild(GLObject* O) { Children[O->getId()] = O; }
  void removeChild(GLObject* O) { Children.erase(O->getId()); }
  void removeChild(size_t Id) { Children.erase(Id); }

  glm::vec3 pos;
  glm::vec3 rot;
  glm::vec3 scale;
  bool Enabled;

private:
  size_t Id;
  std::string Name;
  size_t Type;
  GLObject* Parent;
  ChildrenMap Children;
};

} // namespace rg

#endif // RGGLOBJECT
