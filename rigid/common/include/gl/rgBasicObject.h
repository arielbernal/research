#ifndef RGBASICOBJECT_H
#define RGBASICOBJECT_H

#include <gl/rgGLHeaders.h>
#include <gl/rgCamera.h>
#include <iostream>

namespace rg {

#ifndef _WIN32
#define ATTRALIGN __attribute__((aligned(16)))
#else
#define ATTRALIGN
#endif

struct BasicVertex {
  BasicVertex(float x, float y, float z, float r, float g, float b, float a)
      : pos(x, y, z), normal(0, 0, 0), color(r, g, b, a) {}
  BasicVertex(float x, float y, float z, const glm::vec4& color)
      : pos(x, y, z), normal(0, 0, 0), color(color) {}
  ATTRALIGN glm::vec3 pos;
  ATTRALIGN glm::vec3 normal;
  ATTRALIGN glm::vec4 color;
};

class BasicObject {
 public:
  BasicObject() { MMatrix = glm::mat4(1.0f); }

  void setShader(const std::string& shaderProgramName) {
    ShaderProgramName = shaderProgramName;
    ProgramID = GLProgramManager::getProgram(shaderProgramName);
  }

  void translate(float x, float y, float z) {
    MMatrix = glm::translate(MMatrix, glm::vec3(x, y, z));
    updateMatrices();
  }

  void addTriangle(unsigned int i0, unsigned int i1, unsigned int i2,
                   std::vector<unsigned int>& Indices) {
    Indices.push_back(i0);
    Indices.push_back(i1);
    Indices.push_back(i2);
  }

  void addQuad(unsigned int i0, unsigned int i1, unsigned int i2,
               unsigned int i3, std::vector<unsigned int>& Indices) {
    addTriangle(i0, i1, i2, Indices);
    addTriangle(i2, i3, i0, Indices);
  }

  void printVec3(const glm::vec3& v) {
    std::cout << " [" << v.x << ", " << v.y << ", " << v.z << "] ";
  }
  void updateNormals(std::vector<BasicVertex>& Vertices,
                     std::vector<unsigned int>& Indices) {
    std::vector<size_t> NN(Vertices.size());

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
      NN[i0]++;
      NN[i1]++;
      NN[i2]++;
    }
    for (size_t i = 0; i < Vertices.size(); ++i)
      if (std::abs(NN[i]) > 0.0001f) {
        Vertices[i].normal =
            glm::normalize(Vertices[i].normal / glm::vec3(NN[i]));
      }
  }

  void buildCuboid(float dx, float dy, float dz,
                   std::vector<BasicVertex>& Vertices,
                   std::vector<unsigned int>& Indices, const glm::vec4& color) {
    float dx2 = dx / 2;
    float dy2 = dy / 2;
    float dz2 = dz / 2;
    Vertices.push_back(BasicVertex(-dx2, -dy2, -dz2, color));  // 0
    Vertices.push_back(BasicVertex(dx2, -dy2, -dz2, color));   // 1
    Vertices.push_back(BasicVertex(dx2, dy2, -dz2, color));    // 2
    Vertices.push_back(BasicVertex(-dx2, dy2, -dz2, color));   // 3
    Vertices.push_back(BasicVertex(-dx2, -dy2, dz2, color));   // 4
    Vertices.push_back(BasicVertex(dx2, -dy2, dz2, color));    // 5
    Vertices.push_back(BasicVertex(dx2, dy2, dz2, color));     // 6
    Vertices.push_back(BasicVertex(-dx2, dy2, dz2, color));    // 7
    addQuad(0, 3, 2, 1, Indices);                              // bottom
    addQuad(4, 5, 6, 7, Indices);                              // top
    addQuad(1, 2, 6, 5, Indices);                              // front
    addQuad(0, 4, 7, 3, Indices);                              // back
    addQuad(1, 5, 4, 0, Indices);                              // left
    addQuad(3, 7, 6, 2, Indices);                              // right
    updateNormals(Vertices, Indices);
  }

  void createModel() {
    Vertices.clear();
    float rl = 1;
    float rh = 0.05;
    float th = 0.1;
    float tl = 0.1;
    buildCuboid(2, 2, 2, Vertices, Indices, glm::vec4(1, 0, 0, 0));

    ColorHandler = glGetAttribLocation(ProgramID, "vertexColor");
    std::cout << NormalHandler << " " << ColorHandler << " Color\n";

    PositionHandler =
        glGetAttribLocation(ProgramID, "vertexPosition_modelspace");
    NormalHandler = glGetAttribLocation(ProgramID, "vertexNormal_modelspace");

    MVPMatrixHandle = glGetUniformLocation(ProgramID, "MVP");
    MVMatrixHandle = glGetUniformLocation(ProgramID, "MV");
    VMatrixHandle = glGetUniformLocation(ProgramID, "V");
    MMatrixHandle = glGetUniformLocation(ProgramID, "M");
    LightPositionHandler =
        glGetUniformLocation(ProgramID, "LightPosition_worldspace");

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(BasicVertex),
                 &Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int),
                 &Indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
  }

  void render() {
    glUseProgram(ProgramID);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glUniformMatrix4fv(MVPMatrixHandle, 1, GL_FALSE, &MVPMatrix[0][0]);
    glUniformMatrix4fv(MVMatrixHandle, 1, GL_FALSE, &MVMatrix[0][0]);
    glUniformMatrix4fv(VMatrixHandle, 1, GL_FALSE, &MMatrix[0][0]);
    glUniformMatrix4fv(MMatrixHandle, 1, GL_FALSE, &VMatrix[0][0]);
    glUniform3f(LightPositionHandler, 10, 10, 10);

    glEnableVertexAttribArray(PositionHandler);
    glVertexAttribPointer(PositionHandler, 3, GL_FLOAT, GL_FALSE,
                          sizeof(BasicVertex), (void*)0);
    glEnableVertexAttribArray(NormalHandler);
    glVertexAttribPointer(NormalHandler, 3, GL_FLOAT, GL_FALSE,
                          sizeof(BasicVertex), (void*)16);
    glEnableVertexAttribArray(ColorHandler);
    glVertexAttribPointer(ColorHandler, 4, GL_FLOAT, GL_FALSE,
                          sizeof(BasicVertex), (void*)32);

    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, (void*)0);

    glDisableVertexAttribArray(PositionHandler);
    glDisableVertexAttribArray(NormalHandler);
    glDisableVertexAttribArray(ColorHandler);

    glBindVertexArray(0);
  }

  void updateCamera(const Camera& Cam) {
    VMatrix = Cam.getVMatrix();
    PMatrix = Cam.getPMatrix();
    updateMatrices();
  }

 protected:
  void updateMatrices() {
    MVMatrix = VMatrix * MMatrix;
    MVPMatrix = PMatrix * MVMatrix;
  }

 private:
  GLuint ProgramID;
  GLuint VAO;
  GLuint VBO;
  GLuint IBO;

  std::string ShaderProgramName;
  glm::mat4 MMatrix;
  glm::mat4 VMatrix;
  glm::mat4 PMatrix;
  glm::mat4 MVMatrix;
  glm::mat4 MVPMatrix;

  std::vector<BasicVertex> Vertices;
  std::vector<unsigned int> Indices;

  GLuint MVPMatrixHandle;
  GLuint MVMatrixHandle;
  GLuint MMatrixHandle;
  GLuint VMatrixHandle;
  GLuint LightPositionHandler;

  GLuint PositionHandler;
  GLuint NormalHandler;
  GLuint ColorHandler;
};

}  // namespace rg

#endif  // RGBASICOBJECT_H
