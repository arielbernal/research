#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <QOpenGLWidget>
#include <opencv2/opencv.hpp>
#include <robot.h>
#include <robotdetect.h>

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  explicit GLWidget(QWidget* parent = 0);

  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);
  void setRobot(Robot* R) { robot = R; }

signals:
  void initialized();

 protected:
  bool getFrame();

 private:
  float* data;
  Robot* robot;
  CamDetect* cam;
  int Width;
  int Height;

};

#endif  // GLWIDGET_H