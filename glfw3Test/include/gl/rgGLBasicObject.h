#ifndef RGGLBASICOBJECT_H
#define RGGLBASICOBJECT_H

#include <gl/rgGLObject.h>

namespace rg {

struct BasicVertex {
  BasicVertex(float x, float y, float z, float r, float g, float b, float a)
      : pos(x, y, z), normal(0, 0, 0), color(r, g, b, a) {}
  BasicVertex(float x, float y, float z, const glm::vec4& color)
      : pos(x, y, z), normal(0, 0, 0), color(color) {}
  ATTRALIGN glm::vec3 pos;
  ATTRALIGN glm::vec3 normal;
  ATTRALIGN glm::vec4 color;
};

class GLBasicObject : public GLObject {
 public:
  GLBasicObject(const std::string& ObjectName) : GLObject(ObjectName) {}

  void render() {
    glUseProgram(ProgramID);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    
    glUniformMatrix4fv(MVPMatrixHandle, 1, GL_FALSE, &MVPMatrix[0][0]);
    glUniformMatrix4fv(VMatrixHandle, 1, GL_FALSE, &MMatrix[0][0]);
    glUniformMatrix4fv(MMatrixHandle, 1, GL_FALSE, &VMatrix[0][0]);
    glUniform3f(LightPositionHandler, 5, 5, 5);
    glEnableVertexAttribArray(PositionHandler);
    glVertexAttribPointer(PositionHandler, 3, GL_FLOAT, GL_FALSE,
                          sizeof(BasicVertex), (void*)0);
    glEnableVertexAttribArray(NormalHandler);
    glVertexAttribPointer(NormalHandler, 3, GL_FLOAT, GL_FALSE,
                          sizeof(BasicVertex), (void*)0x10);
    glEnableVertexAttribArray(ColorHandler);
    glVertexAttribPointer(ColorHandler, 4, GL_FLOAT, GL_FALSE,
                          sizeof(BasicVertex), (void*)0x20);

    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, (void*)0);

    glDisableVertexAttribArray(PositionHandler);
    glDisableVertexAttribArray(NormalHandler);
    glDisableVertexAttribArray(ColorHandler);

    glBindVertexArray(0);
  }

  ~GLBasicObject() {
  }

 protected:
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
      if (std::abs(int(NN[i])) > 0.0001f) {
        Vertices[i].normal =
            glm::normalize(Vertices[i].normal / glm::vec3(NN[i]));
      }
  }

  void getHandlers() {
    std::cout << "Retrieved Handlers\n";
    PositionHandler =
        glGetAttribLocation(ProgramID, "vertexPosition_modelspace");
    std::cout << "PositionHandler=" << PositionHandler << std::endl;

    NormalHandler = glGetAttribLocation(ProgramID, "vertexNormal_modelspace");
    std::cout << "NormalHandler=" << NormalHandler << std::endl;

    ColorHandler = glGetAttribLocation(ProgramID, "vertexColor");
    std::cout << "ColorHandler=" << ColorHandler << std::endl;

    MMatrixHandle = glGetUniformLocation(ProgramID, "M");
    std::cout << "MMatrixHandle=" << MMatrixHandle << std::endl;

    MVPMatrixHandle = glGetUniformLocation(ProgramID, "MVP");
    std::cout << "MVPMatrixHandle=" << MVPMatrixHandle << std::endl;

    VMatrixHandle = glGetUniformLocation(ProgramID, "V");
    std::cout << "VMatrixHandle=" << VMatrixHandle << std::endl;

    LightPositionHandler =
        glGetUniformLocation(ProgramID, "LightPosition_worldspace");
        std::cout << "LightPositionHandler=" << LightPositionHandler << std::endl;

  }

  void updateBindings() {
    std::cout << "updateBindings VBO, IBO\n";
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
};

}  // namespace rg

#endif  // RGGLBASICOBJECT_H