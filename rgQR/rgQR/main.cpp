#include "mainwindow.h"
#include <QApplication>
#include <gl/rgglobject.h>
#include <gl/rgglcamera.h>
#include <gl/rggllight.h>
#include <gl/rgglobject3d.h>
#include <map>

namespace rg {

class Scene {
public:
  Scene() : Root(new GLObject("ROOT", GLObject::ROOT)), CurrentObject(Root) {}
  bool addCamera(const std::string& Name) {
    GLCamera* O = new GLCamera(Name, CurrentObject);
    return addObjectMap(O);
  }

  bool addLight(const std::string& Name, size_t LightType = GLLight::DIRECTIONAL) {
    GLLight* O = new GLLight(Name, LightType, CurrentObject);
    return addObjectMap(O);
  }

  bool addObject3D(const std::string& Name, size_t Object3DType) {
    GLObject3D* O = new GLObject3D(Name, Object3DType, CurrentObject);
    return addObjectMap(O);
  }

protected:
  bool addObjectMap(GLObject* O) {
    if (Objects.find(O->getName()) != Objects.end()) {
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
}

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  rg::Scene *Sc = new rg::Scene();

  MainWindow w;
  w.show();

  return a.exec();
}
