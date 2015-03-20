#ifndef RGGLOBJECT_H
#define RGGLOBJECT_H

#include <sstream>
#include <iostream>
#include <vector>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include <gl/rgGLHeaders.h>
#include <gl/rgGLCamera.h>
#include <gl/rgGLShaderProgram.h>
#include <gl/rgGLMaterial.h>
#include <gl/rgGLGroupFaces.h>
#include <gl/rgGLLight.h>

namespace rg {

struct GLObjectCommon {
  GLObjectCommon() { glGenVertexArrays(1, &VAO); }

  ~GLObjectCommon() {
    clearGroups();
    glDeleteVertexArrays(1, &VAO);
  }

  void clearGroups() {
    for (auto e : Groups) delete e;
    Groups.clear();
  }

  void updateBindings() {
    for (auto e : Groups) e->updateBindings(VAO);
  }

  GLuint VAO;
  std::vector<GroupFaces*> Groups;
};

class GLObject {
 public:
  GLObject(const std::string& ObjectName)
      : ObjectName(ObjectName),
        Enabled(true),
        ShowMesh(false),
        MMatrix(glm::mat4(1.0f)),
        CommonPtr(0) {
    if (!CommonPtr) CommonPtr = std::make_shared<GLObjectCommon>();
  }

  GLObject(const std::string& ObjectName, GLObject& obj)
      : ObjectName(ObjectName),
        Enabled(true),
        ShowMesh(false),
        MMatrix(glm::mat4(1.0f)),
        CommonPtr(obj.getSharedData()) {}

  std::string getName() { return ObjectName; }

  void enable(bool val) { Enabled = val; }
  bool isEnabled() { return Enabled; }

  void showMesh(bool val) { ShowMesh = val; }
  bool isShowMesh() { return ShowMesh; }

  void translate(float dx, float dy, float dz) {
    MMatrix = glm::translate(glm::mat4(1), glm::vec3(dx, dy, dz)) * MMatrix;
  }

  void rotate(float angle, float x, float y, float z) {
    MMatrix = glm::rotate(glm::mat4(1), angle, glm::vec3(x, y, z)) * MMatrix;
  }

  void scaleVertices(float k) {
    for (auto e : CommonPtr->Groups) e->scaleVertices(k);
  }

  GLuint getVAO() { return CommonPtr->VAO; }

  void updateBindings() { CommonPtr->updateBindings(); }

  void render(const GLObjectHandlers& OH) {
    glBindVertexArray(CommonPtr->VAO);
    glUniformMatrix4fv(OH.MMatrixHandler, 1, GL_FALSE, &MMatrix[0][0]);

    for (auto e : CommonPtr->Groups) {
      glBindBuffer(GL_ARRAY_BUFFER, e->VBO);

      glEnableVertexAttribArray(OH.VertexHandler);
      glVertexAttribPointer(OH.VertexHandler, 3, GL_FLOAT, GL_FALSE,
                            sizeof(GLVertex), (void*)0);

      glEnableVertexAttribArray(OH.NormalHandler);
      glVertexAttribPointer(OH.NormalHandler, 3, GL_FLOAT, GL_FALSE,
                            sizeof(GLVertex), (void*)0x10);

      if (OH.UvHandler >= 0) {
        glEnableVertexAttribArray(OH.UvHandler);
        glVertexAttribPointer(OH.UvHandler, 3, GL_FLOAT, GL_FALSE,
                              sizeof(GLVertex), (void*)0x20);
      }

      glUniform3fv(OH.Material_Kd_Handler, 1, glm::value_ptr(e->Material->Kd));
      glUniform3fv(OH.Material_Ka_Handler, 1, glm::value_ptr(e->Material->Ka));
      glUniform3fv(OH.Material_Ks_Handler, 1, glm::value_ptr(e->Material->Ks));
      glUniform1f(OH.Material_Ns_Handler, e->Material->Ns);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e->IBO);
      glDrawElements(GL_TRIANGLES, e->Indices.size(), GL_UNSIGNED_INT,
                     (void*)0);

      glDisableVertexAttribArray(OH.VertexHandler);
      glDisableVertexAttribArray(OH.NormalHandler);
      glDisableVertexAttribArray(OH.UvHandler);
    }

    glBindVertexArray(0);
  }

  std::shared_ptr<GLObjectCommon> getSharedData() { return CommonPtr; }

 protected:
  std::string ObjectName;
  bool Enabled;
  bool ShowMesh;
  bool CastShadows;
  bool ReceiveShadows;
  glm::mat4 MMatrix;

  std::shared_ptr<GLObjectCommon> CommonPtr;
};

typedef std::unique_ptr<GLObject> GLObjectPtr;

}  // namespace rg

#endif  // RGGLOBJECT_H