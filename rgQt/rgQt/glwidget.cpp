#define GLEW_STATIC
#include <GL/glew.h>
#include "glwidget.h"
#include <iostream>

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

void GLWidget::initializeGL() {
  const GLenum glewState = glewInit();
  if (glewState != GLEW_OK)
    std::cout << "Glew failed to load" << std::endl;

  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  emit initialized();
}
void GLWidget::paintGL() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
void GLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}
