#ifndef RGBASICOBJECT_H
#define RGBASICOBJECT_H

#include <gl/rgGLHeaders.h>
#include <gl/rgCamera.h>

namespace rg {

struct BasicVertex {
  BasicVertex(float x, float y, float z, float r, float g, float b, float a)
      : pos(x, y, z), color(r, g, b, a) {}
  glm::vec3 pos;
  glm::vec4 color;
};

class BasicObject {
 public:
  BasicObject() { ModelMatrix = glm::mat4(1.0f); }

  void setShader(const std::string& shaderProgramName) {
    ShaderProgramName = shaderProgramName;
    ProgramID = GLProgramManager::getProgram(shaderProgramName);
  }

  void translate(float x, float y, float z) {
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(x, y, z));
    updateMVPMatrix();
  }

  void createModel() {
    Vertices.clear();
    Vertices.push_back(BasicVertex(-1, -1, 0, 1, 0, 0, 1));
    Vertices.push_back(BasicVertex(1, -1, 0, 0, 1, 0, 1));
    Vertices.push_back(BasicVertex(0, 1, 0, 0, 0, 1, 1));
    Indices.push_back(0);
    Indices.push_back(1);
    Indices.push_back(2);

    PositionHandler = glGetAttribLocation(ProgramID, "position");
    ColorHandler = glGetAttribLocation(ProgramID, "color");
    MVPMatrixHandle = glGetUniformLocation(ProgramID, "MVP");

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
    std::cout << "VAO=" << VAO << " VBO= "<< VBO << " IBO=" << IBO << std::endl;
    std::cout << "P=" << PositionHandler << " C=" << ColorHandler << " VMP=" << MVPMatrixHandle << std::endl;
    
    glBindVertexArray(0);
  }

  void render() {
    glUseProgram(ProgramID);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glUniformMatrix4fv(MVPMatrixHandle, 1, GL_FALSE, &MVPMatrix[0][0]);

    glEnableVertexAttribArray(PositionHandler);
    glVertexAttribPointer(PositionHandler, 3, GL_FLOAT, GL_FALSE,
                          sizeof(BasicVertex), (void*)0);
    glEnableVertexAttribArray(ColorHandler);
    glVertexAttribPointer(ColorHandler, 4, GL_FLOAT, GL_FALSE,
                          sizeof(BasicVertex), (void*)12);

    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, (void*)0);

    glDisableVertexAttribArray(PositionHandler);
    glDisableVertexAttribArray(ColorHandler);

    glBindVertexArray(0);
  }

  void updateVPMatrix(const glm::mat4& VP) {
    VPMatrix = VP;
    updateMVPMatrix();
  }

 protected:
  void updateMVPMatrix() { MVPMatrix = VPMatrix * ModelMatrix; }

 private:
  GLuint ProgramID;
  GLuint VAO;
  GLuint VBO;
  GLuint IBO;

  std::string ShaderProgramName;
  glm::mat4 VPMatrix;
  glm::mat4 ModelMatrix;
  glm::mat4 MVPMatrix;

  std::vector<BasicVertex> Vertices;
  std::vector<unsigned int> Indices;

  GLuint MVPMatrixHandle;
  GLuint PositionHandler;
  GLuint ColorHandler;
};

}  // namespace rg

#endif // RGBASICOBJECT_H
