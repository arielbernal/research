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
      cap->set(CV_CAP_PROP_FRAME_WIDTH, 960);
      cap->set(CV_CAP_PROP_FRAME_HEIGHT, 720);
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
  glGenTextures(1, &texCamId);
  glBindTexture(GL_TEXTURE_2D, texCamId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glGenTextures(1, &texPId);
  glBindTexture(GL_TEXTURE_2D, texPId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);



  emit initialized();
}

bool GLWidget::getFrame() {
  cv::Mat frame;
  cap->read(frame);
  cv::Mat redOnly(frame);
  //cv::inRange(frame, cv::Scalar(0,80,180), cv::Scalar(50,120,255), redOnly);
  cv::inRange(frame, cv::Scalar(140,180,80), cv::Scalar(180,240,130), redOnly);


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
  glBindTexture(GL_TEXTURE_2D, texCamId);

  glTexImage2D(
      GL_TEXTURE_2D,  // Type of texture
      0,              // Pyramid level (for mip-mapping) - 0 is the top level
      GL_RGB,         // Internal colour format to convert to
      redOnly.cols,     // Image width  i.e. 640 for Kinect in standard mode
      redOnly.rows,     // Image height i.e. 480 for Kinect in standard mode
      0,              // Border width in pixels (can either be 1 or 0)
      GL_LUMINANCE,         // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
      GL_UNSIGNED_BYTE,  // Image data type
      redOnly.ptr());      // The actual image data itself



  // Draw a textured quad
  float cw = 1, cv = 1;
  float CH = Height / 2;
  if (Width >= CH)
    cv = CH / float(Width);
  else
    cw = Width / float(CH);

  glBindTexture(GL_TEXTURE_2D, texCamId);
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
  glBindTexture(GL_TEXTURE_2D, texPId);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 1);
  glVertex2f(0, cv);
  glTexCoord2f(1, 1);
  glVertex2f(cw, cv);
  glTexCoord2f(1, 0);
  glVertex2f(cw, 2*cv);
  glTexCoord2f(0, 0);
  glVertex2f(0, 2*cv);
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
