#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <QOpenGLWidget>
#include <opencv2/opencv.hpp>
#include <robot.h>

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  explicit GLWidget(QWidget* parent = 0);
  ~GLWidget();

  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);
  void setRobot(Robot* R) { robot = R; }

signals:
  void initialized();

 protected:
  void cameraInit();
  bool getFrame();

 private:
  float* data;
  Robot* robot;
  int Width, Height;
  cv::VideoCapture* cap;
  size_t CamWidth;
  size_t CamHeight;
  GLuint textureTrash;
};

#endif  // GLWIDGET_H
