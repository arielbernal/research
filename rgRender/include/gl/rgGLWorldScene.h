#ifndef RGGLWORLDSCENE_H
#define RGGLWORLDSCENE_H

#include <gl/rgGLHeaders.h>
#include <gl/rgGLObject.h>
#include <gl/rgGLCamera.h>
#include <gl/rgGLLight.h>
#include <gl/rgGLShaderProgram.h>
#include <map>
#include <vector>

namespace rg {

class GLWorldScene {
 public:
  GLWorldScene() : ObjectShader(0) { CurrentCamera = Cameras.begin(); }

  ~GLWorldScene() {}

  void updateLights(const GLLightsHandlers& LH) {
    glUniform1i(LH.NLightsHandler, Lights.size());
    size_t i = 0;
    for (auto e : Lights) {
      if (e.second->Enabled) {
        glUniform1i(LH.Light_type_Handler[i], e.second->type);
        glUniform3fv(LH.Light_La_Handler[i], 1, glm::value_ptr(e.second->La));
        glUniform3fv(LH.Light_Ld_Handler[i], 1, glm::value_ptr(e.second->Ld));
        glUniform3fv(LH.Light_Ls_Handler[i], 1, glm::value_ptr(e.second->Ls));
        glUniform3fv(LH.Light_Pos_Handler[i], 1, glm::value_ptr(e.second->Pos));
        glUniform3fv(LH.Light_Direction_Handler[i], 1,
                     glm::value_ptr(e.second->Direction));
        glUniform1f(LH.Light_Ac_Handler[i], e.second->Ac);
        glUniform1f(LH.Light_Ab_Handler[i], e.second->Ab);
        glUniform1f(LH.Light_Aa_Handler[i], e.second->Aa);
        i++;
      }
    }
  }

  void render() {
    glUseProgram(ObjectShader->getProgramID());
    getCurrentCamera()->updateCamera(ObjectShader->getCameraHandlers());
    updateLights(ObjectShader->getLightsHandlers());
    for (auto e : Objects) e.second->render(ObjectShader->getObjectHandlers());
  }

  // Camera Functions
  void add(GLCamera* Cam) {
    Cameras[Cam->getName()] = Cam;
    CurrentCamera = std::prev(Cameras.end());
  }

  void firstCamera() { CurrentCamera = Cameras.begin(); }

  void nextCamera() {
    CurrentCamera++;
    if (CurrentCamera == Cameras.end()) CurrentCamera = Cameras.begin();
    std::cout << CurrentCamera->second->getName() << std::endl;
  }

  void disableCamera(const std::string& CameraName) {
    auto it = Cameras.find(CameraName);
    if (it != Cameras.end()) (it->second)->disable();
  }

  void enableCamera(const std::string& CameraName) {
    auto it = Cameras.find(CameraName);
    if (it != Cameras.end()) (it->second)->enable();
  }

  void removeCamera(const std::string& CameraName) {
    auto it = Cameras.find(CameraName);
    if (it != Cameras.end()) Cameras.erase(it);
  }

  void setCamera(const std::string& CameraName) {
    auto it = Cameras.find(CameraName);
    if (it != Cameras.end()) CurrentCamera = it;
  }

  GLCamera* getCurrentCamera() { return CurrentCamera->second; }

  // Light functions
  void add(GLLight* Light) { Lights[Light->Name] = Light; }

  void removeLight(const std::string& LightName) {
    auto it = Lights.find(LightName);
    if (it != Lights.end()) Lights.erase(it);
  }

  void disableLight(const std::string& LightName) {
    auto it = Lights.find(LightName);
    if (it != Lights.end()) (it->second)->Enabled = false;
  }

  void enableLight(const std::string& LightName) {
    auto it = Lights.find(LightName);
    if (it != Lights.end()) (it->second)->Enabled = true;
  }

  GLLight* getLight(const std::string& LightName) {
    auto it = Lights.find(LightName);
    if (it != Lights.end()) return (it->second);
    return NULL;
  }

  // Object functions
  void add(GLObjectPtr Object) {
    Object->updateBindings();
    Objects[Object->getName()] = Object;
  }

  void removeObject(const std::string& ObjectName) {
    auto it = Objects.find(ObjectName);
    if (it != Objects.end()) Objects.erase(it);
  }

  void enableObject(const std::string& ObjectName, bool val = true) {
    auto it = Objects.find(ObjectName);
    if (it != Objects.end()) (it->second)->enable(val);
  }

  GLObject* getObject(const std::string& ObjectName) {
    auto it = Objects.find(ObjectName);
    if (it != Objects.end()) return (it->second);
    return NULL;
  }

  void attchObjectShader(const std::string& VertexFileName,
                         const std::string& FragmentFileName) {
    ObjectShader = std::make_unique<GLShaderLight>(
        "LightShader", VertexFileName, FragmentFileName);
  }

 private:
  typedef std::map<std::string, GLCamera*>::iterator CameraIterator;

  std::unique_ptr<GLShaderLight> ObjectShader;
  std::map<std::string, GLCamera*> Cameras;
  std::map<std::string, GLLight*> Lights;
  std::map<std::string, GLObjectPtr> Objects;

  CameraIterator CurrentCamera;
};

}  // namespace rg

#endif  // RGGLWORLDSCENE_H