#include <iostream>
#include <gl/rgGLHeaders.h>
#include <math/rgSvector.h>
#include <gl/rgGLProgram.h>

using namespace rg;

class GLAmbient {
 public:
  void setShader(const std::string& shaderProgramName) {
    ProgramID = GLProgramManager::getProgram(shaderProgramName);
  }
  void render() {}

 private:
  GLuint ProgramID;
  std::string ProgramName;
  glm::mat4 ProjectionMatrix;
  glm::mat4 ViewMatrix;
  glm::mat4 ModelMatrix;
  glm::mat4 MVPMatrix;
  glm::vec4 Color;

  GLuint MVPMatrixHandle;
  GLuint PositionHandler;
  GLuint ColorHandler;
};

class World {
 public:
  void create() {
    GLProgramManager::addProgram("Basic3d", "./shaders/basic3d.vs",
                                 "./shaders/basic3d.fs");
    ambient.setShader("Basic3d");
  }
  void render() {
    ambient.render();
  }
private:
  GLAmbient ambient;
  // cameras
  // ligths
  // particles
  // static objects
  // objects
};

namespace {
int m_window_width = 800;
int m_window_height = 800;
std::string m_window_title = "SpiderQuad";
World w;
}

void display() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  int viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  int width = viewport[2];
  int height = viewport[3];
  // call to world display
  w.render();
  glutSwapBuffers();
}

void init_display() {}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  display();
}

void mouse_wheel(int wheel, int direction, int x, int y) {}

void mouse_button(int button, int state, int x, int y) {}

void mouse_active_motion(int x, int y) {}

void mouse_passive_motion(int x, int y) {}

void special_keys(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      break;
    default:
      break;
  }
}

void normal_keys(unsigned char key, int x, int y) {
  switch (key) {
    case 27:
      glutLeaveMainLoop();
      break;
    default:
      break;
  }
}

void init_glut_window() {
  int a = 0;
  glutInit(&a, NULL);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(2380, 100);
  glutInitWindowSize(m_window_width, m_window_height);
  glutCreateWindow(m_window_title.c_str());
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutKeyboardFunc(normal_keys);
  glutSpecialFunc(special_keys);
  glutMouseFunc(mouse_button);
  glutMotionFunc(mouse_active_motion);
  glutPassiveMotionFunc(mouse_passive_motion);
  glutMouseWheelFunc(mouse_wheel);
  glutReshapeFunc(reshape);
  GLuint err = glewInit();
  if (err != GLEW_OK) std::cout << "Glew not supported\n";
  if (!GLEW_VERSION_2_1) std::cout << "Glew 2.1 not supported\n";
  w.create();
  glutMainLoop();
}

int main(int argc, char* argv[]) { init_glut_window(); }