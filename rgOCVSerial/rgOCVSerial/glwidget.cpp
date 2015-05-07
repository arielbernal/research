#include "glwidget.h"
#include <iostream>
#include <QTimer>
#include <opencv2/opencv.hpp>

#ifndef CV_CAP_PROP_FRAME_WIDTH
#define CV_CAP_PROP_FRAME_WIDTH 3
#endif

#ifndef CV_CAP_PROP_FRAME_HEIGHT
#define CV_CAP_PROP_FRAME_HEIGHT 4
#endif

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {
  robot = nullptr;
  cap = new cv::VideoCapture(0);
  if (!cap->isOpened()) {
    std::cout << "Camera error" << std::endl;
    exit(- 1);
  } else {
    CamWidth = cap->get(CV_CAP_PROP_FRAME_WIDTH);
    CamHeight = cap->get(CV_CAP_PROP_FRAME_HEIGHT);
    std::cout << "Camera initialized width = " << CamWidth
              << " height = " << CamHeight << std::endl;
  }

  QTimer* timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(33);
}

GLWidget::~GLWidget() {
  std::cout << "Release capture" << std::endl;
  cap->release();
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

  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &textureTrash);
  glBindTexture(GL_TEXTURE_2D, textureTrash);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // Set texture clamping method
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  emit initialized();
}

bool GLWidget::getFrame() {
  cv::Mat frame;
  cap->read(frame);
  glColor3f(1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  glTexImage2D(
      GL_TEXTURE_2D,  // Type of texture
      0,              // Pyramid level (for mip-mapping) - 0 is the top level
      GL_RGB,         // Internal colour format to convert to
      frame.cols,     // Image width  i.e. 640 for Kinect in standard mode
      frame.rows,     // Image height i.e. 480 for Kinect in standard mode
      0,              // Border width in pixels (can either be 1 or 0)
      GL_BGR,         // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
      GL_UNSIGNED_BYTE,  // Image data type
      frame.ptr());      // The actual image data itself
  glBindTexture(GL_TEXTURE_2D, textureTrash);
  // Draw a textured quad
  float cw = 1, cv = 1;
  if (CamWidth >= CamHeight)
    cv = CamHeight / float(CamWidth);
  else
    cw = CamWidth / float(CamHeight);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 1);
  glVertex2f(0, 0);
  glTexCoord2f(1, 1);
  glVertex2f(cw, 0);
  glTexCoord2f(1, 0);
  glVertex2f(cw, cv);
  glTexCoord2f(0, 0);
  glVertex2f(0, cv);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  return true;
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (robot) {
    robot->render();
  }
  float cw = 1, cv = 1;
  if (Width >= Height)
    cv = Height / float(Width);
  else
    cw = Width / float(Height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, cw, 0, cv);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (cap->isOpened()) {
    getFrame();
  }

}

void GLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
  Width = width;
  Height = height;
}
