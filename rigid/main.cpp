#include <iostream>
#include <gl/rgGLHeaders.h>
#include <math/rgSvector.h>
#include <gl/rgGLProgram.h>
#include <gl/rgCamera.h>
#include <gl/rgWorldScene.h>

using namespace rg;

namespace {
int m_window_width = 800;
int m_window_height = 800;
std::string m_window_title = "SpiderQuad";
WorldScene w;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  w.render();
  glutSwapBuffers();
}

void reshape(int w, int h) { display(); }

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
    case 'a':
      w.updateCamera();
      break;
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
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(380, 100);
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

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

  // Cull triangles which normal is not towards the camera
  glEnable(GL_CULL_FACE);
  w.create();
  glutMainLoop();
}

int main(int argc, char* argv[]) { init_glut_window(); }