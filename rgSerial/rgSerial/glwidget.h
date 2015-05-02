#ifndef GLWIDGET_H
#define GLWIDGET_H

//#define GLEW_STATIC
#include <GL/glew.h>
#include <QOpenGLWidget>
#include <robot.h>

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

 private:
  float* data;
  Robot* robot;
  int Width, Height;
};

#endif  // GLWIDGET_H
