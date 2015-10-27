#include <iostream>
#include <cmath>
#include <queue>
#include "include/glheaders.h"
#include "nngen.h"
#include "glnngen.h"

namespace {
int m_window_width = 1000;
int m_window_height = 1000;
std::string m_window_title = "GENN";
GENNeuralNet NN(2, 1, 4, 2);
GLNGENNN GLNN(&NN);
std::queue<float> TrainInput;
std::queue<float> TrainOutput;
}

float fc(float t, float V0, float VP, float tau) {
  return V0 * (1 - exp(-t / tau)) + VP;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  int viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  int width = viewport[2];
  int height = viewport[3];
  GLNN.render(width, height);

  set2DMode(width, height);
  printText(10, 20, format("Neurons       = %8zu", NN.getNNeurons()));
  printText(10, 40, format("   Exitatory  = %8zu", NN.getNExitatory()));
  printText(10, 60, format("   Inhibitory = %8zu", NN.getNInhibitory()));
  printText(10, 80, format("   Input      = %8zu", NN.getNInput()));
  printText(10, 100, format("   Output     = %8zu", NN.getNOutput()));
  printText(10, 120, format("Synapses      = %8zu", NN.getNSynapses()));

  // glScalef(1, -1, 1);
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

void populateBurst(float x, float y, float c) {
  char cx = char(x);
  char cy = char(y);
  char cc = char(c);
  char mask = 0x04;
  TrainInput.push(0);
  TrainOutput.push(0);
  for (size_t i = 0; i < 3; ++i) {
    char sx = (cx & mask) != 0;
    char sy = (cy & mask) != 0;
    char sc = (cc & mask) != 0;
    TrainInput.push(sx);
    TrainInput.push(sy);
    TrainOutput.push(sc);
    // std::cout << "  " << int(sx) << " " << int(sy) << " " << int(sc)
    //           << std::endl;
    mask >>= 1;
  }
  TrainInput.push(0);
  TrainOutput.push(0);
}

void trainNN() {
  std::default_random_engine generator;
  static std::uniform_int_distribution<size_t> uniform(0, 7);
  for (size_t r = 0; r < 10000; ++r) {
    size_t err = 0;
    for (size_t i = 0; i < 1000; ++i) {
      float x = uniform(generator);
      float y = uniform(generator);
      float c = x > 4 && y > 4 ? 1 : 0;
      populateBurst(x, y, c);
    }
    while (!TrainInput.empty()) {
      NN.setInput(TrainInput);
      NN.update();
      if (NN.getOutputs()[0]->Ap != TrainOutput.front())
        err++;
      NN.feedback(TrainOutput);
    }
    std::cout << "r = " << r << " Errors = " << err << " Ratio = " << err / 1000.f <<  std::endl;
  }
}

void normal_keys(unsigned char key, int x, int y) {
  switch (key) {
  case 32: {
    NN.setInput(TrainInput);
    NN.update();
    glutPostRedisplay();
    break;
  }
  case 't':
    trainNN();
    glutPostRedisplay();
    break;
  case 's':
    populateBurst(7, 4, 1);
    glutPostRedisplay();
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

  for (size_t i = 0; i < 15; ++i)
    NN.generateSynapses();

  //  NN.dump();

  // glewInit();
  glutMainLoop();
}

int main(int argc, char **argv) {
  init_glut_window(argc, argv);
  return 0;
}
