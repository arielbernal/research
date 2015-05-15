#ifndef IMAGEGLWIDGET_H
#define IMAGEGLWIDGET_H

#include <QOpenGLWidget>
#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <glprimitivies.h>

class ImageGLWidget : public QOpenGLWidget {
  Q_OBJECT
public:
  explicit ImageGLWidget(cv::Mat &Image, QWidget *parent = 0);
  ~ImageGLWidget();
  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);
  void resizeEvent(QResizeEvent *event);

protected:
  void mousePressEvent(QMouseEvent *event);

private:
  int Width;
  int Height;
  cv::Mat Image;
  uint32_t TextureId;
};

#endif // IMAGEGLWIDGET_H
