#include <iostream>
#include <cmath>
#include "include/glheaders.h"
#include "nngen.h"
#include "glnngen.h"

namespace {
int m_window_width = 1000;
int m_window_height = 1000;
std::string m_window_title = "GENN";
GENNeuralNet NN(100, 100, 400, 400);
GLNGENNN GLNN(&NN);
}

void set2DMode(size_t Width, size_t Height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, Width, Height, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void set3DMode(size_t Width, size_t Height) {
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, float(Width) / Height, 0.01f, 1000);
  gluLookAt(0, 0, 40, 0, 0, 0, 0.0, 1.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  int viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  int width = viewport[2];
  int height = viewport[3];
  set3DMode(width, height);
  GLNN.render();
  set2DMode(width, height);
  printText(10, 20, format("Neurons       = %8zu", NN.getNNeurons()));
  printText(10, 40, format("   Exitatory  = %8zu", NN.getNExitatory()));
  printText(10, 60, format("   Inhibitory = %8zu", NN.getNInhibitory()));
  printText(10, 80, format("   Input      = %8zu", NN.getNInput()));
  printText(10,100, format("   Output     = %8zu", NN.getNOutput()));
  printText(10,120, format("Synapses      = %8zu", NN.getNSynapses()));

  glutSwapBuffers();
}

void init_display() {}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  display();
}

void mouse_wheel(int wheel, int direction, int x, int y) {}

void mouse_button(int button, int state, int x, int y) {
  GLNN.mouse_button(button, state, x, y);
}

void mouse_active_motion(int x, int y) { GLNN.mouse_active_motion(x, y); }

void mouse_passive_motion(int x, int y) { GLNN.mouse_passive_motion(x, y); }

void special_keys(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      break;
    case GLUT_KEY_DOWN:
      break;
    case GLUT_KEY_RIGHT:
      break;
    case GLUT_KEY_LEFT:
      break;
    default:
      break;
  }
}

void normal_keys(unsigned char key, int x, int y) {
  switch (key) {
    case 'r':
      break;
    case 's':
      break;
    case 'h':
      glutPostRedisplay();
      break;
    case 27:
      glutLeaveMainLoop();
      break;
    default:
      break;
  }
}

void init_glut_window(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
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


  std::vector<double> I(4);
  I[0] = 0.5;
  I[1] = 0.6;
  I[2] = 0.8;
  I[3] = 0.2;

  NN.feed(I);
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();
  NN.generateSynapses();

//  NN.dump();

  // glewInit();
  glutMainLoop();
}

int main(int argc, char **argv) {
  init_glut_window(argc, argv);
  return 0;
}



