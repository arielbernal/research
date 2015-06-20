#include "simpleglwidget.h"
#include <QOpenGLWidget>
#include "GL/glu.h"
#include <iostream>

SimpleGLWidget::SimpleGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

SimpleGLWidget::~SimpleGLWidget() {}

void SimpleGLWidget::initializeGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, width(), 0, height());
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void SimpleGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glColor3f(1, 1, 1);
  if (isCallbackEnabled && CallbackRenderer) {
    CallbackRenderer();
  }
}

void SimpleGLWidget::resizeGL(int width, int height) {}

void SimpleGLWidget::mousePressEvent(QMouseEvent *event) {
  // cam->mousePressed(event->x(), event->y());
}

void SimpleGLWidget::resizeEvent(QResizeEvent *event) {}
