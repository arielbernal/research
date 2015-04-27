#include "glwidget.h"
#include <iostream>

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

void GLWidget::initializeGL() {
  const GLenum glewState = glewInit();
  if (glewState != GLEW_OK)
    std::cout << "Glew failed to load" << std::endl;
  std::cout << "Glew Initialized" << std::endl;
  glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  emit initialized();
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  glVertex2f(0, 0);
  glVertex2f(1, 0);
  glVertex2f(1, 1);
  glEnd();
}

void GLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}
