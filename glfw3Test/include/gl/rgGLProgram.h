#ifndef RGGLPROGRAM_H
#define RGGLPROGRAM_H

#include <iostream>
#include <map>
#include <vector>

#include <gl/rgGLHeaders.h>
#include <io/rgLog.h>

namespace rg {

class GLProgramManager {
 public:
  static bool addProgram(const std::string &ProgramName,
                         const std::string &VertexFileName,
                         const std::string &FragmentFileName) {
    return getInstance().addProgramNonStatic(ProgramName, VertexFileName,
                                             FragmentFileName);
  }

  static bool addProgramFromSource(const std::string &ProgramName,
                                   const std::string &VertexShaderCode,
                                   const std::string &FragmentShaderCode) {
    return getInstance().addProgramFromSourceNonStatic(
        ProgramName, VertexShaderCode, FragmentShaderCode);
  }

  static GLuint getProgram(const std::string &ProgramName) {
    return getInstance().Programs[ProgramName];
  }

 protected:
  static GLProgramManager &getInstance() {
    static GLProgramManager instance;
    return instance;
  }

  bool addProgramFromSourceNonStatic(const std::string &ProgramName,
                                     const std::string &VertexShaderCode,
                                     const std::string &FragmentShaderCode);

  bool addProgramNonStatic(const std::string &ProgramName,
                           const std::string &VertexFileName,
                           const std::string &FragmentFileName);

  std::string getShaderTypeString(GLenum ShaderType);
  std::string loadShader(const std::string &FileName);
  GLuint createShader(GLenum ShaderType, const std::string &Source);
  GLuint createProgram(const std::vector<GLuint> &ShaderList);

 private:
  GLProgramManager() {};
  GLProgramManager(const GLProgramManager &A);
  ~GLProgramManager();
  void operator=(const GLProgramManager &A);
  std::map<std::string, GLuint> Programs;
};

}  // namespace rg

#endif  // RGGLPROGRAM_H