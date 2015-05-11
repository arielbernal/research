#include "glwidget.h"
#include <iostream>
#include <QTimer>
#include <glprimitivies.h>
#include <QMouseEvent>

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {
  robot = nullptr;
  cam = new CamDetect(maximumWidth(), maximumHeight());
}

void GLWidget::initializeGL() {
  const GLenum glewState = glewInit();
  if (glewState != GLEW_OK)
    std::cout << "Glew failed to load" << std::endl;
  else
    std::cout << "Glew Initialized" << std::endl;
  // glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);

  cam->init();

  QTimer* timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(33);

  emit initialized();
}


void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (robot) {
    robot->render();
  }
  cam->render();
}

void GLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
  Width = width;
  Height = height;
  cam->setSize(Width, Height);
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
  cam->mousePressed(event->x(), event->y());
}
