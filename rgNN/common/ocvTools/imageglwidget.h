#ifndef IMAGEGLWIDGET_H
#define IMAGEGLWIDGET_H

#include <QOpenGLWidget>
#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <../common/oglTools/glprimitivies.h>
#include <QTime>
#include <../common/oglTools/fps.h>
#include <functional>

class ImageGLWidget : public QOpenGLWidget {
  Q_OBJECT
public:
  explicit ImageGLWidget(const std::string &Name, cv::Mat &Image,
                         QWidget *parent = 0);
  ~ImageGLWidget();
  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);
  void resizeEvent(QResizeEvent *event);
  void enableFPS(bool enabled = true) { FPSEnable = enabled; }
  void setFPSPosition(uchar pos) { FPSPos = pos; }

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
  cv::Mat Image;
  uint32_t TextureId;
  uint8_t channels;
  uint8_t depth;
  GLenum DataFormat;
  glp::FPS fps;

  bool FPSEnable;
  uchar FPSPos;

  bool isCallbackEnabled;
  std::function<void()> CallbackRenderer;
};

#endif // IMAGEGLWIDGET_H
