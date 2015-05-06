#include "glwidget.h"
#include <iostream>

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {
  robot = nullptr;
  cap = new cv::VideoCapture(0);
  if (!cap->isOpened()) {
    std::cout << "Camera error" << std::endl;
  }
}

GLWidget::~GLWidget() {
    std::cout << "Release capture" << std::endl;
  cap->release();
}

void GLWidget::initializeGL() {
  const GLenum glewState = glewInit();
  if (glewState != GLEW_OK)
    std::cout << "Glew failed to load" << std::endl;
  std::cout << "Glew Initialized" << std::endl;
  // glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  cameraInit();
  emit initialized();
}

void GLWidget::cameraInit() {
  CamWidth = cap->get(CV_CAP_PROP_FRAME_WIDTH);
  CamHeight = cap->get(CV_CAP_PROP_FRAME_HEIGHT);
  cv::Mat frame;
  cap->read(frame);

  cv::flip(frame, frame, 0);
  glGenTextures(1, &textureTrash);
  glBindTexture(GL_TEXTURE_2D, textureTrash);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Set texture clamping method
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  glTexImage2D(
      GL_TEXTURE_2D,  // Type of texture
      0,              // Pyramid level (for mip-mapping) - 0 is the top level
      GL_RGB,         // Internal colour format to convert to
      frame.cols,     // Image width  i.e. 640 for Kinect in standard mode
      frame.rows,     // Image height i.e. 480 for Kinect in standard mode
      0,              // Border width in pixels (can either be 1 or 0)
      GL_RGB,         // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
      GL_UNSIGNED_BYTE,  // Image data type
      frame.ptr());      // The actual image data itself
}

bool GLWidget::getFrame() {
  cv::Mat frame;
  cap->read(frame);
  std::cout << "GetFrame cols = "  << frame.cols << " Rows = " << frame.rows << std::endl;
  glColor3f(1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  glTexImage2D(
      GL_TEXTURE_2D,  // Type of texture
      0,              // Pyramid level (for mip-mapping) - 0 is the top level
      GL_RGB,         // Internal colour format to convert to
      frame.cols,     // Image width  i.e. 640 for Kinect in standard mode
      frame.rows,     // Image height i.e. 480 for Kinect in standard mode
      0,              // Border width in pixels (can either be 1 or 0)
      GL_RGB,         // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
      GL_UNSIGNED_BYTE,  // Image data type
      frame.ptr());      // The actual image data itself
  glBindTexture(GL_TEXTURE_2D, textureTrash);

  // Draw a textured quad
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 100, 0, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex3f(0, 0, 0);
  glTexCoord2f(0, 1);
  glVertex3f(0, 100, 0);
  glTexCoord2f(1, 1);
  glVertex3f(100, 100, 0);
  glTexCoord2f(1, 0);
  glVertex3f(100, 0, 0);
  glEnd();

  return true;
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (robot) {
    robot->render();
  }
  if (cap->isOpened()) {
    getFrame();
  }
}

void GLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
  Width = width;
  Height = height;
}
