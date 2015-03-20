#ifndef RGGLGROUPFACES_H
#define RGGLGROUPFACES_H

#include <memory>
#include <vector>

#include <gl/rgGLHeaders.h>
#include <gl/rgGLMaterial.h>

namespace rg {

struct GLVertex {
  GLVertex(float x, float y, float z)
      : vertex(x, y, z), normal(0, 0, 0), uv(0, 0) {}
  GLVertex(const glm::vec3& vertex, const glm::vec3& normal = glm::vec3(0),
           const glm::vec2& uv = glm::vec2(0))
      : vertex(vertex), normal(normal), uv(uv) {}
  ATTRALIGN glm::vec3 vertex;
  ATTRALIGN glm::vec3 normal;
  ATTRALIGN glm::vec2 uv;
};

struct GroupFaces {
  GLMaterialPtr Material;
  std::vector<GLVertex> Vertices;
  std::vector<uint32_t> Indices;
  
  GLuint VBO;
  GLuint IBO;

  GroupFaces(GLMaterialPtr& Material) : Material(Material) {
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
  }

  ~GroupFaces() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
  }

  void addVertex(const glm::vec3& vertex,
                 const glm::vec3& normal = glm::vec3(0),
                 const glm::vec2& uv = glm::vec2(0)) {
    GLVertex v(vertex, normal, uv);
    Vertices.push_back(v);
  }

  void addTriangle(uint32_t i0, uint32_t i1, uint32_t i2) {
    Indices.push_back(i0);
    Indices.push_back(i1);
    Indices.push_back(i2);
  }

  void addQuad(uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3) {
    addTriangle(i0, i1, i2);
    addTriangle(i2, i3, i0);
  }

  void addTriangleFan(uint32_t ic, const std::vector<uint32_t>& fan) {
    size_t N = fan.size();
    for (size_t i = 0; i < N; ++i) addTriangle(fan[i], ic, fan[(i + 1) % N]);
  }

  void scaleVertices(float k) {
    for (auto& e : Vertices) e.vertex *= k;
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
      if (glm::length(c1) > 1e-3)
        c1 = glm::normalize(c1);
      else
        c1 = glm::vec3(0);
      if (glm::length(c2) > 1e-3)
        c2 = glm::normalize(c2);
      else
        c2 = glm::vec3(0);
      if (glm::length(c3) > 1e-3)
        c3 = glm::normalize(c3);
      else
        c3 = glm::vec3(0);
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(uint32_t),
                 &Indices[0], GL_STATIC_DRAW);
    glBindVertexArray(0);
  }
};

}  // namespace rg

#endif  // RGGLGROUPFACES_H
