#include <iostream>
#include <glheaders.h>
#include <cmath>

#include "particles.h"
#include "world.h"
#include "glparticles.h"


namespace {
int m_window_width = 1000;
int m_window_height = 1000;
std::string m_window_title = "SpiderQuad";
ParticleSystem ps;
World world;
GLParticleSystem glps(&world, &ps);
bool runSim = false;
}

void set2DMode(size_t Width, size_t Height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, Width, 0, Height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void set3DMode(size_t Width, size_t Height) {
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, float(Width) / Height, 0.01f, 1000);
  gluLookAt(80, 0, 80, 0, 0, 0, 0.0, 1.0, 0.0);
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
  glps.draw();
  if (runSim)
    ps.step(0.02f);
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
  glps.mouse_button(button, state, x, y);
}

void mouse_active_motion(int x, int y) { glps.mouse_active_motion(x, y); }

void mouse_passive_motion(int x, int y) { glps.mouse_passive_motion(x, y); }

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
      runSim = !runSim;
      break;
    case 's':
      ps.step(0.01f);
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

void setWorld() {

  CubeObject *g = new CubeObject(40, 40, 5.0f);  // ground
  g->setColor(float4(0.3f, 0.5f, 0.4f, 1.0f));
  g->translate(-20, -20, -5.0f);
  g->setFriction(2.8f);
  world.push_back(g);

  CubeObject *c = new CubeObject();
  c->setColor(float4(0.3f, 0.2f, 0.7f, 1.0f));
  c->scale(5);
  c->translate(0, 0, 1);
  c->setFriction(0.8f);
//  world.push_back(c);

  TriangularPrismObject *p = new TriangularPrismObject();
  p->scale(5);
  p->translate(8, 0, 0);
  p->setColor(float4(0.3f, 0.6f, 0.6f, 1.0f));
  p->setFriction(0.8f);
  world.push_back(p);

  TetrahedronObject *t = new TetrahedronObject();
  t->scale(8);
  t->translate(8, 8, 0);
  t->setColor(float4(0.6f, 0.2f, 0.3f, 1.0f));
  t->setFriction(0.8f);
  world.push_back(t);
  ps.setWorld(&world);
  ps.createTest();
}

void init_glut_window(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(2800, 100);
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
  // glewInit();
  setWorld();
  glutMainLoop();
}
int main(int argc, char **argv) {
  init_glut_window(argc, argv);
  return 0;
}
