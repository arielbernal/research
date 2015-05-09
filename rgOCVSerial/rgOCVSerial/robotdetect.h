#ifndef ROBOTDETECT_H
#define ROBOTDETECT_H

#include <QOpenGLWidget>
#include <QDebug>
#include <opencv2/opencv.hpp>

class CamDetect {
 public:
  CamDetect(size_t W, size_t H) : Width(W), Height(H) {}

  void setSize(size_t W, size_t H) {
    Width = W;
    Height = H;
  }

  void init() {
    cap = new cv::VideoCapture(0);
    if (!cap->isOpened()) {
      std::cout << "Camera error" << std::endl;
      exit(-1);
    } else {
      cap->set(cv::CAP_PROP_FRAME_WIDTH, 960);
      cap->set(cv::CAP_PROP_FRAME_HEIGHT, 720);
      CamWidth = cap->get(cv::CAP_PROP_FRAME_WIDTH);
      CamHeight = cap->get(cv::CAP_PROP_FRAME_HEIGHT);
      std::cout << "Camera initialized width = " << CamWidth
                << " height = " << CamHeight << std::endl;
    }

    texCamId = glp::newTextureId();
    texPId = glp::newTextureId();
  }
  ~CamDetect() {
    cap->release();
    qDebug() << "Camera Released";
  }

  void render() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, Width, 0, Height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    cv::Mat frame;
    cap->read(frame);
    cv::Mat HSV;
    cv::Mat redOnly;
    cv::cvtColor(frame, HSV, cv::COLOR_BGR2HSV);
    cv::inRange(HSV, cv::Scalar(10, 90, 0), cv::Scalar(40, 200, 30), redOnly);
    // cv::blur(frame,redOnly, cv::Size(9,9));

    glColor3f(1, 1, 1);
    glp::setTexture(texCamId, frame.cols, frame.rows, GL_BGR, frame.ptr());
    glp::setTexture(
        texPId, redOnly.cols, redOnly.rows, GL_LUMINANCE, redOnly.ptr());

    // Draw a textured quad
    float CW, CH;
    getBestFit(frame.cols, frame.rows, Width, Height / 2, CW, CH);
    glp::renderTexture(texCamId, 0, 0, CW, CH);
    glp::renderTexture(texPId, 0, Height / 2, CW, CH);
    glDisable(GL_TEXTURE_2D);
  }

 protected:
  void getBestFit(float old_w,
                  float old_h,
                  float refw,
                  float refh,
                  float& new_w,
                  float& new_h) {
    if (refh / refw > old_h / old_w) {
      new_w = refw;
      new_h = new_w * old_h / old_w;
    } else {
      new_h = refh;
      new_w = new_h * old_w / old_h;
    }
  }

 private:
  cv::VideoCapture* cap;
  size_t Width;
  size_t Height;
  size_t CamWidth;
  size_t CamHeight;
  GLuint texCamId;
  GLuint texPId;
};

#endif  // ROBOTDETECT_H
