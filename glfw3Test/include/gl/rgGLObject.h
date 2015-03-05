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

class GLObject {
 public:
  GLObject(const std::string& ObjectName)
      : ObjectName(ObjectName),
        Enabled(true),
        ShowMesh(false),
        ShaderProgram(NULL),
        ShaderMeshProgram(NULL),
        MMatrix(glm::mat4(1.0f)) {
    generateArrayBuffers();
  }

  ~GLObject() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
  }

  std::string getName() { return ObjectName; }

  void enable() { Enabled = true; }
  void disable() { Enabled = false; }
  bool isEnabled() { return Enabled; }

  void showMesh() { ShowMesh = true; }
  void hideMesh() { ShowMesh = false; }
  bool isShowMesh() { return ShowMesh; }

  void triangle(unsigned int i0, unsigned int i1, unsigned int i2,
                   std::vector<unsigned int>& Indices) {
    Indices.push_back(i0);
    Indices.push_back(i1);
    Indices.push_back(i2);
  }

  void quad(unsigned int i0, unsigned int i1, unsigned int i2,
               unsigned int i3, std::vector<unsigned int>& Indices) {
    triangle(i0, i1, i2, Indices);
    triangle(i2, i3, i0, Indices);
  }

  void triangleFan(unsigned int ic, const std::vector<unsigned int>& fan, std::vector<unsigned int>& Indices) {
    size_t N = fan.size();
    for (size_t i = 0; i < N; ++i)
      triangle(fan[i], ic, fan[(i + 1) % N], Indices);
  }

  void translate(float dx, float dy, float dz) {
    MMatrix = glm::translate(MMatrix, glm::vec3(dx, dy, dz));
    updateMatrices();
  }

  void attachShader(GLShaderProgram* Shader) {
    ShaderProgram = Shader;
    ProgramID = Shader->getProgramID();
    getHandlers();
  }

  void attachMeshSahder(GLShaderProgram* Shader) { ShaderMeshProgram = Shader; }

  bool isShaderAttached() { return ShaderProgram != NULL; }
  bool isShaderMeshAttached() { return ShaderMeshProgram != NULL; }

  void updateCamera(const GLCamera& Cam) {
    VMatrix = Cam.getVMatrix();
    PMatrix = Cam.getPMatrix();
    updateMatrices();
  }

  virtual void getHandlers() = 0;
  virtual void render() = 0;

 protected:
  void generateArrayBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
  }

  void updateMatrices() {
    MVPMatrix = PMatrix * VMatrix * MMatrix;
  }

  std::string ObjectName;
  bool Enabled;
  bool ShowMesh;

  GLShaderProgram* ShaderProgram;
  GLShaderProgram* ShaderMeshProgram;

  GLuint ProgramID;
  GLuint ProgramMeshID;
  GLuint VAO;
  GLuint VBO;
  GLuint IBO;
  GLuint PositionHandler;
  GLuint NormalHandler;
  GLuint ColorHandler;
  GLuint MMatrixHandle;
  GLuint VMatrixHandle;
  GLuint MVPMatrixHandle;
  GLuint LightPositionHandler;
  GLuint LightsHandler;

  glm::mat4 MMatrix;
  glm::mat4 VMatrix;
  glm::mat4 PMatrix;
  glm::mat4 MVPMatrix;
};

}  // namespace rg

#endif  // RGGLOBJECT_H