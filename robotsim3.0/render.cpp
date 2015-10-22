#include <iostream>
#include <cmath>
#include "include/glheaders.h"
#include "nngen.h"
#include "glnngen.h"

namespace {
int m_window_width = 1000;
int m_window_height = 1000;
std::string m_window_title = "GENN";
GENNeuralNet NN(8, 8, 40, 40);
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

float fc(float t, float V0, float VP, float tau) {
  return V0 * (1 - exp(-t/tau)) + VP;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  int viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  int width = viewport[2];
  int height = viewport[3];
  set3DMode(width, height);
  //GLNN.render();
  set2DMode(width, height);
  printText(10, 20, format("Neurons       = %8zu", NN.getNNeurons()));
  printText(10, 40, format("   Exitatory  = %8zu", NN.getNExitatory()));
  printText(10, 60, format("   Inhibitory = %8zu", NN.getNInhibitory()));
  printText(10, 80, format("   Input      = %8zu", NN.getNInput()));
  printText(10, 100, format("   Output     = %8zu", NN.getNOutput()));
  printText(10, 120, format("Synapses      = %8zu", NN.getNSynapses()));
  
  //glScalef(1, -1, 1);
  float kc = 10;
  float kcx = 20;
  float V0 = 40;
  float VV = 0;
  float VP = 10;
  float v = VP;
  float tau = 5;
  float h = 0.01;
  
  glBegin(GL_POINTS);
  for (size_t i = 0; i < 100; ++i) {
    float x0 = i * kcx;
    float y0 = fc(i, V0, VP, tau) * kc;
    glVertex2f(x0, height - y0);
    //glVertex2f(x1, height - y1);
    v += h * V0 /tau * exp(-i * h / tau);
    float y1 = v * kc;
    std::cout << "  " << y0 << " " << y1 << std::endl;
    glColor3f(1, 1, 0);
    glVertex2f(x0, height - y1);
  }
  glEnd();
  exit(-1);

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
  case 32: {
    std::vector<double> I(8);
    for (size_t i = 0; i < 8; ++i)
      I[0] = ((i % 8) + 1) / 9.0 * 0.1;
    NN.feed(I);
    break;
  }
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

  std::vector<double> I(8);
  for (size_t i = 0; i < 8; ++i)
    I[0] = ((i % 8) + 1) / 9.0 * 0.01;

  for (size_t i = 0; i < 200; ++i) {
    NN.generateSynapses();
  }

  NN.feed(I);

  //  NN.dump();

  // glewInit();
  glutMainLoop();
}

int main(int argc, char **argv) {
  init_glut_window(argc, argv);
  return 0;
}
