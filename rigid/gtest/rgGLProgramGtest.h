#ifndef RGGLPROGRAMGTEST_H
#define RGGLPROGRAMGTEST_H

#include <fstream>
#include <iostream>

#include <gl/rgGLHeaders.h>
#include <gl/rgGLProgram.h>

using namespace rg;

static bool initialized = false;

class Test_GLProgramManager : public ::testing::Test {
 protected:
  virtual void SetUp() {
    if (!initialized) {
      int a = 0;
      glutInit(&a, NULL);
      glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
      glutInitWindowPosition(100, 100);
      glutInitWindowSize(100, 100);
      glutCreateWindow("gtest");
      GLuint err = glewInit();
      if (err != GLEW_OK) std::cout << "Glew not supported\n";
      if (!GLEW_VERSION_2_1) std::cout << "Glew 2.1 not supported\n";
      initialized = true;
    }
  }
};

TEST_F(Test_GLProgramManager, GLProgram_addProgram) {
  GLProgramManager::addProgram("Basic2d", "./shaders/basic.vs",
                               "./shaders/basic.fs");
  int id = -1;
  id = GLProgramManager::getProgram("Basic2d");
  EXPECT_TRUE(id >= 0);
}

std::string loadShader(const std::string &FileName) {
  std::string ShaderCode;
  std::ifstream ShaderStream(FileName.c_str(), std::ios::in);
  if (ShaderStream.is_open()) {
    std::string Line = "";
    while (getline(ShaderStream, Line)) ShaderCode += "\n" + Line;
    ShaderStream.close();
  } else {
    std::cout << "Shader file not found\n";
    return "";
  }
  return ShaderCode;
}

TEST_F(Test_GLProgramManager, GLProgram_addProgramFromSource) {
  std::string VertexShaderCode = loadShader("./shaders/basic.vs");
  std::string FragmentShaderCode = loadShader("./shaders/basic.fs");

  GLProgramManager::addProgramFromSource("Basic2d1", VertexShaderCode,
                                         FragmentShaderCode);
  int id = -1;
  id = GLProgramManager::getProgram("Basic2d1");
  EXPECT_TRUE(id >= 0);
}

#endif  // RGGLPROGRAMGTEST_H