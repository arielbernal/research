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

#define MAX_LIGHTS 10

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
        MMatrix(glm::mat4(1.0f)),
        Lights(0) {
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
    EyePos = Cam.getPosition();
    updateMatrices();
  }

  void setLights(std::map<std::string, GLLight*>* VLights) { Lights = VLights; }

  void getHandlers() {
    VertexHandler = glGetAttribLocation(ProgramID, "Vertex");
    NormalHandler = glGetAttribLocation(ProgramID, "Normal");
    UvHandler = glGetAttribLocation(ProgramID, "Uv");

    MMatrixHandle = glGetUniformLocation(ProgramID, "M");
    VMatrixHandle = glGetUniformLocation(ProgramID, "V");
    MVPMatrixHandle = glGetUniformLocation(ProgramID, "MVP");
    EyePosHandler = glGetUniformLocation(ProgramID, "EyePos");

    Material_Kd_Handler = glGetUniformLocation(ProgramID, "Material.Kd");
    Material_Ka_Handler = glGetUniformLocation(ProgramID, "Material.Ka");
    Material_Ks_Handler = glGetUniformLocation(ProgramID, "Material.Ks");
    Material_Ns_Handler = glGetUniformLocation(ProgramID, "Material.Ns");

    NLightsHandler = glGetUniformLocation(ProgramID, "NLights");
    for (size_t i = 0; i < MAX_LIGHTS; ++i) {
      std::ostringstream osLight;
      osLight << "Lights[" << i << "].";
      Light_type_Handler[i] = glGetUniformLocation(ProgramID, (osLight.str() + "type").c_str());
      Light_La_Handler[i] = glGetUniformLocation(ProgramID, (osLight.str() + "La").c_str());
      Light_Ld_Handler[i] = glGetUniformLocation(ProgramID, (osLight.str() + "Ld").c_str());
      Light_Ls_Handler[i] = glGetUniformLocation(ProgramID, (osLight.str() + "Ls").c_str());
      Light_Pos_Handler[i] = glGetUniformLocation(ProgramID, (osLight.str() + "Pos").c_str());
      Light_Direction_Handler[i] =
        glGetUniformLocation(ProgramID, (osLight.str() + "Direction").c_str());
      Light_Ac_Handler[i] = glGetUniformLocation(ProgramID, (osLight.str() + "Ac").c_str());
      Light_Ab_Handler[i] = glGetUniformLocation(ProgramID, (osLight.str() + "Ab").c_str());
      Light_Aa_Handler[i] = glGetUniformLocation(ProgramID, (osLight.str() + "Aa").c_str());
    }
  }

  void render() {
    glUseProgram(ProgramID);
    glBindVertexArray(VAO);

    glUniformMatrix4fv(MVPMatrixHandle, 1, GL_FALSE, &MVPMatrix[0][0]);
    glUniformMatrix4fv(MMatrixHandle, 1, GL_FALSE, &MMatrix[0][0]);
    glUniformMatrix4fv(VMatrixHandle, 1, GL_FALSE, &VMatrix[0][0]);

    size_t i = 0;
    glUniform1i(NLightsHandler, Lights->size());
    for (auto e : (*Lights)) {
      glUniform1i(Light_type_Handler[i], e.second->type);
      glUniform3fv(Light_La_Handler[i], 1, glm::value_ptr(e.second->La));
      glUniform3fv(Light_Ld_Handler[i], 1, glm::value_ptr(e.second->Ld));
      glUniform3fv(Light_Ls_Handler[i], 1, glm::value_ptr(e.second->Ls));
      glUniform3fv(Light_Pos_Handler[i], 1, glm::value_ptr(e.second->Pos));
      glUniform3fv(Light_Direction_Handler[i], 1,
                   glm::value_ptr(e.second->Direction));
      glUniform1f(Light_Ac_Handler[i], e.second->Ac);
      glUniform1f(Light_Ab_Handler[i], e.second->Ab);
      glUniform1f(Light_Aa_Handler[i], e.second->Aa);
      i++;
    }
    glUniform3fv(EyePosHandler, 1, glm::value_ptr(EyePos));

    for (auto e : Groups) {
      glBindBuffer(GL_ARRAY_BUFFER, e->VBO);

      glEnableVertexAttribArray(VertexHandler);
      glVertexAttribPointer(VertexHandler, 3, GL_FLOAT, GL_FALSE,
                            sizeof(GLVertex), (void*)0);

      glEnableVertexAttribArray(NormalHandler);
      glVertexAttribPointer(NormalHandler, 3, GL_FLOAT, GL_FALSE,
                            sizeof(GLVertex), (void*)0x10);

      if (UvHandler >= 0) {
        glEnableVertexAttribArray(UvHandler);
        glVertexAttribPointer(UvHandler, 3, GL_FLOAT, GL_FALSE,
                              sizeof(GLVertex), (void*)0x20);
      }

      glUniform3fv(Material_Kd_Handler, 1, glm::value_ptr(e->Material.Kd));
      glUniform3fv(Material_Ka_Handler, 1, glm::value_ptr(e->Material.Ka));
      glUniform3fv(Material_Ks_Handler, 1, glm::value_ptr(e->Material.Ks));
      glUniform1f(Material_Ns_Handler, e->Material.Ns);

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

  GLint VertexHandler;
  GLint NormalHandler;
  GLint UvHandler;

  GLint MMatrixHandle;
  GLint VMatrixHandle;
  GLint MVPMatrixHandle;
  GLint LightPositionHandler;
  GLint EyePosHandler;

  GLint Material_Kd_Handler;
  GLint Material_Ka_Handler;
  GLint Material_Ks_Handler;
  GLint Material_Ns_Handler;

  GLint NLightsHandler;
  GLint Light_type_Handler[MAX_LIGHTS];
  GLint Light_La_Handler[MAX_LIGHTS];
  GLint Light_Ld_Handler[MAX_LIGHTS];
  GLint Light_Ls_Handler[MAX_LIGHTS];
  GLint Light_Pos_Handler[MAX_LIGHTS];
  GLint Light_Direction_Handler[MAX_LIGHTS];
  GLint Light_Ac_Handler[MAX_LIGHTS];
  GLint Light_Ab_Handler[MAX_LIGHTS];
  GLint Light_Aa_Handler[MAX_LIGHTS];

  glm::mat4 MMatrix;
  glm::mat4 VMatrix;
  glm::mat4 PMatrix;
  glm::mat4 MVPMatrix;

  glm::vec3 EyePos;

  std::vector<GroupFaces*> Groups;
  std::map<std::string, GLLight*>* Lights;
};

}  // namespace rg

#endif  // RGGLOBJECT_H