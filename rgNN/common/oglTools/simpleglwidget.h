#ifndef SIMPLEGLWIDGET_H
#define SIMPLEGLWIDGET_H

#include <QOpenGLWidget>
#include <stdint.h>
#include <../common/oglTools/glprimitivies.h>
#include <QTime>
#include <functional>
#include <iostream>

class SimpleGLWidget : public QOpenGLWidget {
  Q_OBJECT
public:
  explicit SimpleGLWidget(QWidget *parent = 0);

  ~SimpleGLWidget();
  void setName(const std::string &name) { Name = name; }
  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);
  void resizeEvent(QResizeEvent *event);

  void setCallbackRenderer(std::function<void()> Func) {
    CallbackRenderer = Func;
    isCallbackEnabled = true;
  }

  void disableCallbackRenderer() { isCallbackEnabled = false; }

protected:
  void mousePressEvent(QMouseEvent *event);

private:
  std::string Name;
  int Width;
  int Height;

  bool FPSEnable;
  uchar FPSPos;

  bool isCallbackEnabled;
  std::function<void()> CallbackRenderer;
};

#endif // SIMPLEGLWIDGET_H
