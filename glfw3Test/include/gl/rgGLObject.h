#ifndef RGGLOBJECT_H
#define RGGLOBJECT_H

#include <gl/rgGLHeaders.h>
#include <gl/rgGLCamera.h>
#include <gl/rgGLShaderProgram.h>

#include <iostream>
#include <vector>

namespace rg {

#ifndef _WIN32
#define ATTRALIGN __attribute__((aligned(16)))
#else
#define ATTRALIGN __declspec(align(16))
#endif

struct GLMaterial {
  std::string Name;
  glm::vec3 Ka;        // Ambient color
  glm::vec3 Kd;        // Diffuse color
  glm::vec3 Ks;        // Specular color
  float Ns;            // Specular exponent
  glm::vec3 Tf;        // Transmision filter
  int illum;           // Illumination model
  float d;             // Dissolve factor
  float Ni;            // Index of refraction
  std::string map_Ka;  // Ambient texture
  std::string map_Kd;  // Diffuse texture
  std::string map_Ks;  // Specular texture

  GLMaterial(const std::string& Name) : Name(Name) {}
  const bool hasTextureFiles() const {
    return map_Ka.length() > 0 || map_Kd.length() > 0 || map_Ks.length() > 0;
  }
};

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
      Vertices[i0].normal += glm::normalize(glm::cross(p2 - p1, p3 - p1));
      Vertices[i1].normal += glm::normalize(glm::cross(p3 - p2, p1 - p2));
      Vertices[i2].normal += glm::normalize(glm::cross(p1 - p3, p2 - p3));
    }
    for (size_t i = 0; i < Vertices.size(); ++i)
      Vertices[i].normal = glm::normalize(Vertices[i].normal);
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
        ShaderProgram(NULL),
        ShaderMeshProgram(NULL),
        MMatrix(glm::mat4(1.0f)) {
    glGenVertexArrays(1, &VAO);
    beta = 0;
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
    updateMatrices();
  }

  void attachShader(GLShaderProgram* Shader) {
    ShaderProgram = Shader;
    ProgramID = Shader->getProgramID();
    getHandlers();
    for (auto e : Groups) e->updateBindings(VAO);
  }

  void attachMeshSahder(GLShaderProgram* Shader) { ShaderMeshProgram = Shader; }

  bool isShaderAttached() { return ShaderProgram != NULL; }
  bool isShaderMeshAttached() { return ShaderMeshProgram != NULL; }

  void updateCamera(const GLCamera& Cam) {
    VMatrix = Cam.getVMatrix();
    PMatrix = Cam.getPMatrix();
    updateMatrices();
  }

  void getHandlers() {
    VertexHandler = glGetAttribLocation(ProgramID, "Vertex");
    NormalHandler = glGetAttribLocation(ProgramID, "Normal");

    MMatrixHandle = glGetUniformLocation(ProgramID, "M");
    MVPMatrixHandle = glGetUniformLocation(ProgramID, "MVP");
    ColorHandler = glGetUniformLocation(ProgramID, "Color");

    LightPositionHandler =
        glGetUniformLocation(ProgramID, "LightPosition_worldspace");
  }

  float beta;
  void render() {
    glUseProgram(ProgramID);
    glBindVertexArray(VAO);

    glUniformMatrix4fv(MVPMatrixHandle, 1, GL_FALSE, &MVPMatrix[0][0]);
    glUniformMatrix4fv(MMatrixHandle, 1, GL_FALSE, &MMatrix[0][0]);

    glUniform3f(LightPositionHandler, cos(beta) * 10, sin(beta) * 10, 10);
                //10.0 * cos(beta) * sin(beta));

    beta += 0.01f;
    // glUniform3f(LightPositionHandler, 0, 4, 2);

    for (auto e : Groups) {
      glBindBuffer(GL_ARRAY_BUFFER, e->VBO);

      glEnableVertexAttribArray(VertexHandler);
      glVertexAttribPointer(VertexHandler, 3, GL_FLOAT, GL_FALSE,
                            sizeof(GLVertex), (void*)0);

      glEnableVertexAttribArray(NormalHandler);
      glVertexAttribPointer(NormalHandler, 3, GL_FLOAT, GL_FALSE,
                            sizeof(GLVertex), (void*)0x10);

      if (int16_t(UvHandler - 1) > 0) {
        glEnableVertexAttribArray(UvHandler);
        glVertexAttribPointer(UvHandler, 3, GL_FLOAT, GL_FALSE,
                              sizeof(GLVertex), (void*)0x20);
      }

      glUniform3f(ColorHandler, e->Material.Kd.x, e->Material.Kd.y,
                  e->Material.Kd.z);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e->IBO);
      glDrawElements(GL_TRIANGLES, e->Indices.size(), GL_UNSIGNED_SHORT,
        (void*)0);

      glDisableVertexAttribArray(VertexHandler);
      glDisableVertexAttribArray(NormalHandler);
      glDisableVertexAttribArray(UvHandler);
    }

    glBindVertexArray(0);
  }

 protected:
  void updateMatrices() { MVPMatrix = PMatrix * VMatrix * MMatrix; }

  std::string ObjectName;
  bool Enabled;
  bool ShowMesh;

  GLShaderProgram* ShaderProgram;
  GLShaderProgram* ShaderMeshProgram;

  GLuint ProgramID;
  GLuint ProgramMeshID;
  GLuint VAO;

  GLuint VertexHandler;
  GLuint NormalHandler;
  GLuint UvHandler;

  GLuint MMatrixHandle;
  GLuint MVPMatrixHandle;
  GLuint LightPositionHandler;
  GLuint ColorHandler;

  glm::mat4 MMatrix;
  glm::mat4 VMatrix;
  glm::mat4 PMatrix;
  glm::mat4 MVPMatrix;

  std::vector<GroupFaces*> Groups;
};

}  // namespace rg

#endif  // RGGLOBJECT_H