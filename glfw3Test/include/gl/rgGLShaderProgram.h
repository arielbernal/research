#ifndef RGGLSHADERPROGRAM_H
#define RGGLSHADERPROGRAM_H

#include <gl/rgGLHeaders.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>

namespace rg {

class GLShaderProgram {
 public:
  GLShaderProgram(const std::string& ProgramName)
      : ProgramID(GL_FALSE), ProgramName(ProgramName) {}

  GLShaderProgram(const std::string& ProgramName,
                  const std::string& VertexFileName,
                  const std::string& FragmentFileName)
      : ProgramID(GL_FALSE),
        ProgramName(ProgramName),
        VertexFileName(VertexFileName),
        FragmentFileName(FragmentFileName) {
    addProgram(VertexFileName, FragmentFileName);
  }

  bool addProgram(const std::string& VertexFileName,
                  const std::string& FragmentFileName) {
    std::string VertexShaderCode = loadShader(VertexFileName);
    std::string FragmentShaderCode = loadShader(FragmentFileName);
    return addProgramFromSource(VertexShaderCode, FragmentShaderCode);
  }

  bool addProgramFromSource(const std::string& VertexShaderCode,
                            const std::string& FragmentShaderCode) {
    // Create the shaders
    std::vector<GLuint> ShaderList;
    ShaderList.push_back(createShader(GL_VERTEX_SHADER, VertexShaderCode));
    ShaderList.push_back(createShader(GL_FRAGMENT_SHADER, FragmentShaderCode));

    // Link the program
    ProgramID = createProgram(ShaderList);
    for (auto e : ShaderList) glDeleteShader(e);

    return (ProgramID != GL_FALSE);
  }

  GLuint getProgramID() { return ProgramID; }

  std::string getName() { return ProgramName; }

  void addAttribute(const std::string& AttrName) {
    Attributes[AttrName] = glGetAttribLocation(ProgramID, AttrName.c_str());
  }

  void addUniform(const std::string& UniformName) {
    Uniforms[UniformName] = glGetUniformLocation(ProgramID, UniformName.c_str());
  }

 protected:
  std::string loadShader(const std::string& FileName) {
    std::string ShaderCode;
    std::ifstream ShaderStream(FileName.c_str(), std::ios::in);
    if (ShaderStream.is_open()) {
      std::string Line = "";
      while (std::getline(ShaderStream, Line)) ShaderCode += "\n" + Line;
      ShaderStream.close();
    } else {
      std::cout << "Shader file not found\n";
      return "";
    }
    return ShaderCode;
  }

  std::string getShaderTypeString(GLenum ShaderType) {
    switch (ShaderType) {
      case GL_VERTEX_SHADER:
        return "Vertex Shader";
      case GL_GEOMETRY_SHADER:
        return "Geometry Shader";
      case GL_FRAGMENT_SHADER:
        return "Fragment Shader";
    }
    return "Unknown Shader";
  }

  GLuint createShader(GLenum ShaderType, const std::string& Source) {
    GLuint ShaderID = glCreateShader(ShaderType);
    const char* SourceStr = Source.c_str();
    glShaderSource(ShaderID, 1, &SourceStr, NULL);
    glCompileShader(ShaderID);
    GLint Status;
    glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Status);
    if (Status == GL_FALSE) {
      GLint InfoLogLength;
      glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
      std::vector<char> ShaderErrorMessage(std::max(InfoLogLength, int(1)));
      glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
      std::cout << "Create shader : " << getShaderTypeString(ShaderType).c_str()
                << " Error: " << (char*)&ShaderErrorMessage[0] << "\n";
      return GL_FALSE;
    }
    return ShaderID;
  }

  GLuint createProgram(const std::vector<GLuint>& ShaderList) {
    GLuint ProgramID = glCreateProgram();
    for (auto e : ShaderList) glAttachShader(ProgramID, e);

    glLinkProgram(ProgramID);
    GLint Status;
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Status);
    if (Status == GL_FALSE) {
      GLint InfoLogLength;
      glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
      std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, int(1)));
      glGetProgramInfoLog(ProgramID, InfoLogLength, NULL,
                          &ProgramErrorMessage[0]);
      std::cout << "Link Program Error : " << (char*)&ProgramErrorMessage[0]
                << "\n";
      glDeleteProgram(ProgramID);
      return GL_FALSE;
    }
    return ProgramID;
  }

 private:
  GLuint ProgramID;
  std::string ProgramName;
  std::string VertexFileName;
  std::string FragmentFileName;

  std::map<std::string, GLuint> Attributes;
  std::map<std::string, GLuint> Uniforms;
};

}  // namespace rg

#endif  // RGGLSHADERPROGRAM_H