#ifndef GLWIDGET_H
#define GLWIDGET_H
#define GLEW_STATIC
#include <GL/glew.h>
#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
public:
  explicit GLWidget(QWidget* parent = 0);
  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);
signals:
  void initialized();

};

#endif // GLWIDGET_H
