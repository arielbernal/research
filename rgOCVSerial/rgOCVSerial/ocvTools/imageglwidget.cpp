#include <ocvTools/imageglwidget.h>
#include <iostream>
#include "GL/glu.h"
#include <QTimer>

ImageGLWidget::ImageGLWidget(const std::string &Name, cv::Mat &Image,
                             QWidget *parent)
    : QOpenGLWidget(parent), Name(Name), Image(Image) {
  std::cout << "GLWidget created " << Image.cols << ", " << Image.rows
            << std::endl;
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(33);
  channels = 1 + (Image.type() >> CV_CN_SHIFT);
  depth = Image.type() & CV_MAT_DEPTH_MASK;
  DataFormat = GL_BGR;
  if (channels == 1)
    DataFormat = GL_LUMINANCE;
  FPSEnable = false;
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
  if (FPSEnable) {
    float fpsVal = fps.update();
    char str[20];
#if WIN32
    sprintf_s(str, "FPS = %5.2f", fpsVal);
    cv::putText(Image, str, cv::Point(width()/2, 25), CV_FONT_HERSHEY_SIMPLEX, 1,
                cv::Scalar::all(255));
#else
    snprintf(str, 20, "FPS = %5.2f", fpsVal);
    cv::putText(Image, str, cv::Point(width()/2, 25), cv::FONT_HERSHEY_SIMPLEX, 1,
                cv::Scalar::all(255));
#endif
  }

  if (CallbackRenderer) {
    CallbackRenderer();
  }

  glp::setTexture(TextureId, Image.cols, Image.rows, DataFormat, Image.ptr());
  glp::renderTexture(TextureId, 0, 0, width(), height());

}

void ImageGLWidget::resizeGL(int width, int height) {}

void ImageGLWidget::mousePressEvent(QMouseEvent *event) {
  // cam->mousePressed(event->x(), event->y());
}

void ImageGLWidget::resizeEvent(QResizeEvent *event) {}
