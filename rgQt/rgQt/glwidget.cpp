#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent), Initialized(false) {}

void GLWidget::initializeGL() {
  glClearColor(1, 1, 0, 1);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  Initialized = true;
}
void GLWidget::paintGL() { glClear(GL_COLOR_BUFFER_BIT); }
void GLWidget::resizeGL(int w, int h) {}
