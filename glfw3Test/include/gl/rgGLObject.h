#ifndef RGGLOBJECT_H
#define RGGLOBJECT_H

#include <gl/rgGLHeaders.h>
#include <gl/rgGLCamera.h>
#include <gl/rgGLShaderProgram.h>
#include <gl/rgGLMaterial.h>
#include <gl/rgGLLight.h>
#include <sstream>

#include <iostream>
#include <vector>

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

namespace rg {

#ifndef _WIN32
#define ATTRALIGN __attribute__((aligned(16)))
#else
#define ATTRALIGN __declspec(align(16))
#endif

struct GLVertex {
  GLVertex(float x, float y, float z)
      : vertex(x, y, z), normal(0, 0, 0), uv(0, 0, 0) {}
  GLVertex(const glm::vec3& vertex, const glm::vec3& normal = glm::vec3(0),
           const glm::vec3& uv = glm::vec3(0))
      : vertex(vertex), normal(normal), uv(uv) {}
  ATTRALIGN glm::vec3 vertex;
  ATTRALIGN glm::vec3 normal;
  ATTRALIGN glm::vec3 uv;
};

struct GroupFaces {
  GLMaterial Material;
  std::vector<GLVertex> Vertices;
  std::vector<uint16_t> Indices;
  GLuint VBO;
  GLuint IBO;

  GroupFaces(const GLMaterial& Material) : Material(Material) {
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
  }

  ~GroupFaces() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
  }

  void addVertex(const glm::vec3& vertex,
                 const glm::vec3& normal = glm::vec3(0),
                 const glm::vec3& uv = glm::vec3(0)) {
    GLVertex v(vertex, normal, uv);
    Vertices.push_back(v);
  }

  void addTriangle(uint16_t i0, uint16_t i1, uint16_t i2) {
    Indices.push_back(i0);
    Indices.push_back(i1);
    Indices.push_back(i2);
  }

  void addQuad(uint16_t i0, uint16_t i1, uint16_t i2, uint16_t i3) {
    addTriangle(i0, i1, i2);
    addTriangle(i2, i3, i0);
  }

  void addTriangleFan(uint16_t ic, const std::vector<uint16_t>& fan) {
    size_t N = fan.size();
    for (size_t i = 0; i < N; ++i) addTriangle(fan[i], ic, fan[(i + 1) % N]);
  }

  void updateNormals() {
    for (size_t i = 0; i < Indices.size() / 3; ++i) {
      size_t i0 = Indices[3 * i];
      size_t i1 = Indices[3 * i + 1];
      size_t i2 = Indices[3 * i + 2];
      glm::vec3 p1 = Vertices[i0].vertex;
      glm::vec3 p2 = Vertices[i1].vertex;
      glm::vec3 p3 = Vertices[i2].vertex;
      glm::vec3 c1 = glm::cross(p2 - p1, p3 - p1);
      glm::vec3 c2 = glm::cross(p3 - p2, p1 - p2);
      glm::vec3 c3 = glm::cross(p1 - p3, p2 - p3);
      if (glm::length(c1) > 1e-3) c1 = glm::normalize(c1); else c1 = glm::vec3(0);
      if (glm::length(c2) > 1e-3) c2 = glm::normalize(c2); else c2 = glm::vec3(0);
      if (glm::length(c3) > 1e-3) c3 = glm::normalize(c3); else c3 = glm::vec3(0);
      Vertices[i0].normal += c1;
      Vertices[i1].normal += c2;
      Vertices[i2].normal += c3;
    }
    for (size_t i = 0; i < Vertices.size(); ++i) {
      if (glm::length(Vertices[i].normal) > 1e-3)
        Vertices[i].normal = glm::normalize(Vertices[i].normal);
    }
  }
  void updateBindings(const GLuint& VAO) {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(GLVertex),
                 &Vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(uint16_t),
                 &Indices[0], GL_STATIC_DRAW);
    glBindVertexArray(0);
  }
};

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

  void enable() { Enabled = true; }
  void disable() { Enabled = false; }
  bool isEnabled() { return Enabled; }

  void showMesh() { ShowMesh = true; }
  void hideMesh() { ShowMesh = false; }
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

  GLuint VAO;

  glm::mat4 MMatrix;

  std::vector<GroupFaces*> Groups;
};

}  // namespace rg

#endif  // RGGLOBJECT_H