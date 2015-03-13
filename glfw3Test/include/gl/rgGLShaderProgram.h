#ifndef RGGLSHADERPROGRAM_H
#define RGGLSHADERPROGRAM_H

#include <gl/rgGLHeaders.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <map>

namespace rg {

#define MAX_LIGHTS 6

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

  ~GLShaderProgram() { glDeleteProgram(ProgramID); }

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

  GLuint ProgramID;

 private:
  std::string ProgramName;
  std::string VertexFileName;
  std::string FragmentFileName;
};

struct GLObjectHandlers {
  GLint VertexHandler;
  GLint NormalHandler;
  GLint UvHandler;
  GLint MMatrixHandler;
  GLint Material_Kd_Handler;
  GLint Material_Ka_Handler;
  GLint Material_Ks_Handler;
  GLint Material_Ns_Handler;

  void bindHandlers(GLuint ProgramID) {
    VertexHandler = glGetAttribLocation(ProgramID, "Vertex");
    NormalHandler = glGetAttribLocation(ProgramID, "Normal");
    UvHandler = glGetAttribLocation(ProgramID, "Uv");
    MMatrixHandler = glGetUniformLocation(ProgramID, "M");
    Material_Kd_Handler = glGetUniformLocation(ProgramID, "Material.Kd");
    Material_Ka_Handler = glGetUniformLocation(ProgramID, "Material.Ka");
    Material_Ks_Handler = glGetUniformLocation(ProgramID, "Material.Ks");
    Material_Ns_Handler = glGetUniformLocation(ProgramID, "Material.Ns");
  }
  void printHandlers() {
    std::cout << "Object Handlers\n";
    std::cout << "  VertexHandler=" << VertexHandler
              << ", NormalHandler=" << NormalHandler
              << ", UvHandler=" << UvHandler
              << ", MMatrixHandler=" << MMatrixHandler << "\n";
    std::cout << "  Kd=" << Material_Kd_Handler
              << ", Ka=" << Material_Ka_Handler
              << ", Ks=" << Material_Ka_Handler
              << ", Ns=" << Material_Ns_Handler << "\n\n";

  }
};

struct GLCameraHandlers {
  GLint VMatrixHandler;
  GLint PMatrixHandler;

  void bindHandlers(GLuint ProgramID) {
    VMatrixHandler = glGetUniformLocation(ProgramID, "V");
    PMatrixHandler = glGetUniformLocation(ProgramID, "P");
  }
  void printHandlers() {
    std::cout << "Camera Handlers\n";
    std::cout << "  VMatrixHandler=" << VMatrixHandler
              << ", PMatrixHandler=" << PMatrixHandler << "\n\n";
  }
};

struct GLLightsHandlers {
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

  void bindHandlers(GLuint ProgramID) {
    NLightsHandler = glGetUniformLocation(ProgramID, "NLights");
    for (size_t i = 0; i < MAX_LIGHTS; ++i) {
      std::ostringstream osLight;
      osLight << "Lights[" << i << "].";
      Light_type_Handler[i] =
          glGetUniformLocation(ProgramID, (osLight.str() + "type").c_str());
      Light_La_Handler[i] =
          glGetUniformLocation(ProgramID, (osLight.str() + "La").c_str());
      Light_Ld_Handler[i] =
          glGetUniformLocation(ProgramID, (osLight.str() + "Ld").c_str());
      Light_Ls_Handler[i] =
          glGetUniformLocation(ProgramID, (osLight.str() + "Ls").c_str());
      Light_Pos_Handler[i] =
          glGetUniformLocation(ProgramID, (osLight.str() + "Pos").c_str());
      Light_Direction_Handler[i] = glGetUniformLocation(
          ProgramID, (osLight.str() + "Direction").c_str());
      Light_Ac_Handler[i] =
          glGetUniformLocation(ProgramID, (osLight.str() + "Ac").c_str());
      Light_Ab_Handler[i] =
          glGetUniformLocation(ProgramID, (osLight.str() + "Ab").c_str());
      Light_Aa_Handler[i] =
          glGetUniformLocation(ProgramID, (osLight.str() + "Aa").c_str());
    }
  }
  void printHandlers() {
    std::cout << "Light Handlers\n";
    std::cout << "  NLightsHandler=" << NLightsHandler << std::endl;
    for (size_t i = 0; i < MAX_LIGHTS; ++i) {
      std::cout << "  Light " << i << std::endl;
      std::cout << "    type=" << Light_type_Handler[i] << "\n";
      std::cout << "    La=" << Light_La_Handler[i]
                << ", Ld=" << Light_Ld_Handler[i]
                << ", Ls=" << Light_Ls_Handler[i] << "\n";
      std::cout << "    Pos=" << Light_Pos_Handler[i]
                << ", Direction=" << Light_Direction_Handler[i]
                << ", Aa=" << Light_Aa_Handler[i]
                << ", Ab=" << Light_Ab_Handler[i]
                << ", Ac=" << Light_Ac_Handler[i] << "\n";
    }
  }
};

class GLShaderLight : public GLShaderProgram {
 public:
  GLShaderLight(const std::string& ProgramName,
                const std::string& VertexFileName,
                const std::string& FragmentFileName)
      : GLShaderProgram(ProgramName, VertexFileName, FragmentFileName) {

    OH.bindHandlers(ProgramID);
    CH.bindHandlers(ProgramID);
    LH.bindHandlers(ProgramID);

    OH.printHandlers();
    CH.printHandlers();
    LH.printHandlers();
  }

  GLObjectHandlers getObjectHandlers() { return OH; }
  GLCameraHandlers getCameraHandlers() { return CH; }
  GLLightsHandlers getLightsHandlers() { return LH; }

 private:
  // Object Handlers
  GLObjectHandlers OH;
  // Camera Handlers
  GLCameraHandlers CH;
  // Light Handlers
  GLLightsHandlers LH;
};

}  // namespace rg

#endif  // RGGLSHADERPROGRAM_H