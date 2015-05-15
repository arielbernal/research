#include <ocvTools/imageglwidget.h>
#include <iostream>
#include "GL/glu.h"
#include <QTimer>

ImageGLWidget::ImageGLWidget(cv::Mat &Image, QWidget *parent)
    : QOpenGLWidget(parent), Image(Image) {
  std::cout << "GLWidget created " << Image.cols << ", " << Image.rows
            << std::endl;
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(33);
}

ImageGLWidget::~ImageGLWidget() { glDeleteTextures(1, &TextureId); }

void ImageGLWidget::initializeGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  TextureId = glp::newTextureId();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, width(), 0, height());
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void ImageGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1, 1, 1);
  glp::setTexture(TextureId, Image.cols, Image.rows, GL_BGR, Image.ptr());
  glp::renderTexture(TextureId, 0, 0, width(), height());
  //std::cout << "painting" << std::endl;
}

void ImageGLWidget::resizeGL(int width, int height) {}

void ImageGLWidget::mousePressEvent(QMouseEvent *event) {
  // cam->mousePressed(event->x(), event->y());
}

void ImageGLWidget::resizeEvent(QResizeEvent *event) {}
