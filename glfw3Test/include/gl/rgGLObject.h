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



class GLObject {
 public:
  GLObject(const std::string& ObjectName)
      : ObjectName(ObjectName),
        Enabled(true),
        ShowMesh(false),
        MMatrix(glm::mat4(1.0f)) {
    glGenVertexArrays(1, &VAO);
  }

  ~GLObject() {
    Groups.clear();
    glDeleteVertexArrays(1, &VAO);
  }

  std::string getName() { return ObjectName; }

  void enable(bool val) { Enabled = val; }
  bool isEnabled() { return Enabled; }

  void showMesh(bool val) { ShowMesh = val; }
  bool isShowMesh() { return ShowMesh; }

  void translate(float dx, float dy, float dz) {
    MMatrix = glm::translate(MMatrix, glm::vec3(dx, dy, dz));
  }

  GLuint getVAO() { return VAO; }

  void updateBindings() {
    for (auto e : Groups) e->updateBindings(VAO);
  }

  void render(const GLObjectHandlers& OH) {
    glBindVertexArray(VAO);
    glUniformMatrix4fv(OH.MMatrixHandler, 1, GL_FALSE, &MMatrix[0][0]);

    for (auto e : Groups) {
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

      glUniform3fv(OH.Material_Kd_Handler, 1, glm::value_ptr(e->Material.Kd));
      glUniform3fv(OH.Material_Ka_Handler, 1, glm::value_ptr(e->Material.Ka));
      glUniform3fv(OH.Material_Ks_Handler, 1, glm::value_ptr(e->Material.Ks));
      glUniform1f(OH.Material_Ns_Handler, e->Material.Ns);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e->IBO);
      glDrawElements(GL_TRIANGLES, e->Indices.size(), GL_UNSIGNED_SHORT,
                     (void*)0);

      glDisableVertexAttribArray(OH.VertexHandler);
      glDisableVertexAttribArray(OH.NormalHandler);
      glDisableVertexAttribArray(OH.UvHandler);
    }

    glBindVertexArray(0);
  }

 protected:
  std::string ObjectName;
  bool Enabled;
  bool ShowMesh;
  bool CastShadows;
  bool ReceiveShadows;

  GLuint VAO;

  glm::mat4 MMatrix;

  std::vector<GroupFaces*> Groups;
};

}  // namespace rg

#endif  // RGGLOBJECT_H