#ifndef GENERICGLWIDGET_H
#define GENERICGLWIDGET_H

#include <QOpenGLWidget>

class GenericGLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  explicit GenericGLWidget(QWidget* parent = 0);
  ~GenericGLWidget();
  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

 protected:
  void mousePressEvent(QMouseEvent* event);

 private:
  int Width;
  int Height;
};

#endif  // GENERICGLWIDGET_H
