#include "genericglwidget.h"

GenericGLWidget::GenericGLWidget(QWidget* parent) : QOpenGLWidget(parent) {
}

GenericGLWidget::~GenericGLWidget() {
}

void GenericGLWidget::initializeGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
}

void GenericGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GenericGLWidget::resizeGL(int width, int height) {
  Width = width;
  Height = height;
}

void GenericGLWidget::mousePressEvent(QMouseEvent* event) {
  // cam->mousePressed(event->x(), event->y());
}
