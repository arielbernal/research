#ifndef RGGLBASICOBJECT_H
#define RGGLBASICOBJECT_H

#include <gl/rgGLObject.h>

namespace rg {

struct GLMaterial {
  GLMaterial(const std::string& Name) : Name(Name) {}
  std::string Name;
  glm::vec3 ka;  // ambient
  glm::vec3 kd;  // diffuse
  glm::vec3 ks;  // specular
  float tr;      // transparency
};

struct GLFaceGroup {
  GLMaterial Material;
  std::vector<uint16_t> Indices;
};

struct BasicVertex {
  BasicVertex(float x, float y, float z) : pos(x, y, z), normal(0, 0, 0) {}
  ATTRALIGN glm::vec3 pos;
  ATTRALIGN glm::vec3 normal;
};

class GLBasicObject : public GLObject {
 public:
  GLBasicObject(const std::string& ObjectName) : GLObject(ObjectName) {
    beta = 0;
  }

  float beta;
  void render() {
    glUseProgram(ProgramID);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glUniformMatrix4fv(MVPMatrixHandle, 1, GL_FALSE, &MVPMatrix[0][0]);
    glUniformMatrix4fv(VMatrixHandle, 1, GL_FALSE, &VMatrix[0][0]);
    glUniformMatrix4fv(MMatrixHandle, 1, GL_FALSE, &MMatrix[0][0]);

    glUniform3f(LightPositionHandler, cos(beta) * 300, sin(beta) * 520,
                500 * cos(beta) * sin(beta));

    beta += 0.001f;
    // glUniform3f(LightPositionHandler, 0, 4, 2);
    glEnableVertexAttribArray(PositionHandler);
    glVertexAttribPointer(PositionHandler, 3, GL_FLOAT, GL_FALSE,
                          sizeof(BasicVertex), (void*)0);
    glEnableVertexAttribArray(NormalHandler);
    glVertexAttribPointer(NormalHandler, 3, GL_FLOAT, GL_FALSE,
                          sizeof(BasicVertex), (void*)0x10);

    for (auto e : FaceGroup) {
      glUniform3f(ColorHandler, e.Material.kd.x, e.Material.kd.y,
                  e.Material.kd.z);
      glDrawElements(GL_TRIANGLES, e.Indices.size(), GL_UNSIGNED_SHORT, (void*)0);
    }

    glDisableVertexAttribArray(PositionHandler);
    glDisableVertexAttribArray(NormalHandler);
    glDisableVertexAttribArray(ColorHandler);

    glBindVertexArray(0);
  }

  ~GLBasicObject() {}

 protected:
  void updateNormals(std::vector<BasicVertex>& Vertices,
                     std::vector<unsigned int>& Indices) {
    for (size_t i = 0; i < Indices.size() / 3; ++i) {
      size_t i0 = Indices[3 * i];
      size_t i1 = Indices[3 * i + 1];
      size_t i2 = Indices[3 * i + 2];
      glm::vec3 p1 = Vertices[i0].pos;
      glm::vec3 p2 = Vertices[i1].pos;
      glm::vec3 p3 = Vertices[i2].pos;
      Vertices[i0].normal += glm::normalize(glm::cross(p2 - p1, p3 - p1));
      Vertices[i1].normal += glm::normalize(glm::cross(p3 - p2, p1 - p2));
      Vertices[i2].normal += glm::normalize(glm::cross(p1 - p3, p2 - p3));
    }
    for (size_t i = 0; i < Vertices.size(); ++i)
      Vertices[i].normal = glm::normalize(Vertices[i].normal);
  }

  void getHandlers() {
    PositionHandler =
        glGetAttribLocation(ProgramID, "vertexPosition_modelspace");
    NormalHandler = glGetAttribLocation(ProgramID, "vertexNormal_modelspace");

    MMatrixHandle = glGetUniformLocation(ProgramID, "M");
    VMatrixHandle = glGetUniformLocation(ProgramID, "V");
    MVPMatrixHandle = glGetUniformLocation(ProgramID, "MVP");
    ColorHandler = glGetUniformLocation(ProgramID, "Color");

    LightPositionHandler =
        glGetUniformLocation(ProgramID, "LightPosition_worldspace");
    LightsHandler = glGetUniformLocation(ProgramID, "Lights");
  }

  void updateBindings() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(BasicVertex),
                 &Vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int),
                 &Indices[0], GL_STATIC_DRAW);
    glBindVertexArray(0);
  }

  std::vector<BasicVertex> Vertices;
  std::vector<unsigned int> Indices;
  std::vector<GLMaterial> Materials;
  std::vector<GLFaceGroup> FaceGroup;
};

}  // namespace rg

#endif  // RGGLBASICOBJECT_H
