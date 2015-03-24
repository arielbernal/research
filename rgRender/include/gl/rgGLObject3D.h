#ifndef RGGLOBJECT3D_H
#define RGGLOBJECT3D_H

#include <sstream>
#include <iostream>
#include <vector>
#include <gl/rgGLHeaders.h>
#include <gl/rgGLCamera.h>
#include <gl/rgGLShaderProgram.h>
#include <gl/rgGLMaterial.h>
#include <gl/rgGLGroupFaces.h>

namespace rg {

struct GLObject3DCommon {
  GLObject3DCommon() { 
    glGenVertexArrays(1, &VAO); 
  }

  ~GLObject3DCommon() {
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

class GLObject3D : public GLObject {
 public:
  enum { CUBOID, SPHERE, CYLINDER };

  GLObject3D(const std::string& Name, size_t Object3DType,
             GLObject* Parent = nullptr)
      : GLObject(Name, OBJECT3D, Parent),
        Object3DType(Object3DType),
        Enabled(true),
        ShowMesh(false),
        MMatrix(glm::mat4(1.0f)),
        Common3DPtr(0) {
    Common3DPtr = std::make_shared<GLObject3DCommon>();
  }

  GLObject3D(GLObject3D& obj, const std::string& Name)
      : GLObject(Name, OBJECT3D, obj.getParent()),
        Object3DType(obj.getType()),
        Enabled(true),
        ShowMesh(false),
        MMatrix(glm::mat4(1.0f)),
        Common3DPtr(obj.getSharedData()) {}

  size_t getType() { return Object3DType; }
  std::string getTypeString() {
    switch (Object3DType) {
      case CUBOID:
        return "Object3D::Cuboid";
      case SPHERE:
        return "Object3D::Sphere";
      case CYLINDER:
        return "Object3D::Cylinder";
      default:
        return "Object3D::Unknown";
    }
    return "Object3D::Unknown";
  }

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
    for (auto e : Common3DPtr->Groups) e->scaleVertices(k);
  }

  GLuint getVAO() { return Common3DPtr->VAO; }

  void updateBindings() { Common3DPtr->updateBindings(); }

  void render(const GLObjectHandlers& OH) {
    glBindVertexArray(Common3DPtr->VAO);
    glUniformMatrix4fv(OH.MMatrixHandler, 1, GL_FALSE, &MMatrix[0][0]);

    for (auto e : Common3DPtr->Groups) {
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

  std::shared_ptr<GLObject3DCommon> getSharedData() { return Common3DPtr; }

 protected:
  size_t Object3DType;
  bool Enabled;
  bool ShowMesh;
  bool CastShadows;
  bool ReceiveShadows;
  glm::mat4 MMatrix;

  std::shared_ptr<GLObject3DCommon> Common3DPtr;

  void clearGroups() {
    Common3DPtr->clearGroups();
  }

  void pushBackGroupFaces(GroupFaces* F) {
    Common3DPtr->Groups.push_back(F);
  }

};

typedef std::shared_ptr<GLObject3D> GLObject3DPtr;

}  // namespace rg

#endif  // RGGLOBJECT3D_H