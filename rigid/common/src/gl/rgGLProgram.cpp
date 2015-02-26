#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <gl/rgGLProgram.h>

namespace rg {

GLProgramManager::~GLProgramManager() {
  for (auto e : Programs) glDeleteProgram(e.second);
}

std::string GLProgramManager::loadShader(const std::string &FileName) {
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

std::string GLProgramManager::getShaderTypeString(GLenum ShaderType) {
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

GLuint GLProgramManager::createShader(GLenum ShaderType,
                                      const std::string &Source) {
  GLuint ShaderID = glCreateShader(ShaderType);
  const char *SourceStr = Source.c_str();
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
              << " Error: " << (char *)&ShaderErrorMessage[0] << "\n";
    return GL_FALSE;
  }
  return ShaderID;
}

GLuint GLProgramManager::createProgram(const std::vector<GLuint> &ShaderList) {
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
    std::cout << "Link Program Error : " << (char *)&ProgramErrorMessage[0]
              << "\n";
    glDeleteProgram(ProgramID);
    return GL_FALSE;
  }
  return ProgramID;
}

bool GLProgramManager::addProgramFromSourceNonStatic(
    const std::string &ProgramName, const std::string &VertexShaderCode,
    const std::string &FragmentShaderCode) {
  if (Programs.find(ProgramName) != Programs.end()) return false;

  // Create the shaders
  std::vector<GLuint> ShaderList;
  ShaderList.push_back(createShader(GL_VERTEX_SHADER, VertexShaderCode));
  ShaderList.push_back(createShader(GL_FRAGMENT_SHADER, FragmentShaderCode));

  // Link the program
  LOG("Create Program\n");
  GLuint ProgramID = createProgram(ShaderList);

  for (auto e : ShaderList) glDeleteShader(e);

  if (ProgramID != GL_FALSE)
    Programs[ProgramName] = ProgramID;
  else
    return false;

  return true;
}

bool GLProgramManager::addProgramNonStatic(
    const std::string &ProgramName, const std::string &VertexFileName,
    const std::string &FragmentFileName) {
  LOG("Load VertexShader\n");
  std::string VertexShaderCode = loadShader(VertexFileName);

  LOG("Load FragmentShader\n");
  std::string FragmentShaderCode = loadShader(FragmentFileName);

  return addProgramFromSource(ProgramName, VertexShaderCode,
                              FragmentShaderCode);
}

}  // namespace rg