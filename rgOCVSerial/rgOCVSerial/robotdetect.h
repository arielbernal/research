#ifndef ROBOTDETECT_H
#define ROBOTDETECT_H

#include <QOpenGLWidget>
#include <QDebug>
#include <list>
#include <opencv2/opencv.hpp>

class CamDetect {
 public:
  CamDetect(size_t W, size_t H) : Width(W), Height(H) {}
  float HL, SL, VL, HH, SH, VH;
  int mouseX, mouseY;
  bool mPressed;

  void setSize(size_t W, size_t H) {
    Width = W;
    Height = H;
    HL = 0;
    SL = 0;
    VL = 0;
    HH = 0;
    SH = 0;
    VH = 0;
    mouseX = 0;
    mouseY = 0;
    mPressed = false;
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
    qDebug() << "Camera Released";
    cap->release();
  }

  void mousePressed(int x, int y) {
    y = y - 480;
    // std::cout << "x = " << x << " y = "<< y << std::endl;
    if (x >= 0 && x <= 640 && y >= 0 && y < 480) {
      y = 480 - y;
      mouseX = x;
      mouseY = y;
      mPressed = true;
    }
  }

  void getAVGColor(cv::Mat& a, int x, int y, float& v1, float& v2, float& v3) {
    x = float(x) / 640 * 960;
    y = 720 - float(y) / 480 * 720;
    int xmax = a.cols;
    int ymax = a.rows;
    int x0 = x < 10 ? 0 : x - 10;
    int y0 = y < 10 ? 0 : y - 10;
    int x1 = x + 10 > xmax ? xmax : x + 10;
    int y1 = y + 10 > ymax ? ymax : y + 10;
    std::cout << "x = " << x << " y = " << y << " ->" << x0 << " " << x1 << " "
              << y0 << " " << y1 << std::endl;

    std::cout << (int)a.ptr()[3 * (y * xmax + x)] << " - ";
    std::cout << (int)a.ptr()[3 * (y * xmax + x) + 1] << " - ";
    std::cout << (int)a.ptr()[3 * (y * xmax + x) + 2] << std::endl;
    v1 = (int)a.ptr()[3 * (y * xmax + x)];
    v2 = (int)a.ptr()[3 * (y * xmax + x) + 1];
    v3 = (int)a.ptr()[3 * (y * xmax + x) + 2];
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
    cv::Mat RedMask;
    cv::Mat GreenMask;
    cv::Mat ThresholdMask;
    cv::cvtColor(frame, HSV, cv::COLOR_BGR2HSV);
    if (mPressed) {
      float h, s, v;
      getAVGColor(HSV, mouseX, mouseY, h, s, v);
      HL = h - 20 < 0 ? 0 : h - 20;
      HH = h + 20 > 180 ? 180 : h + 20;
      SL = s - 50 < 0 ? 0 : s - 50;
      SH = 255;
      VL = v - 50 < 0 ? 0 : v - 50;
      VH = 255;
      mPressed = false;
    }
    // cv::inRange(HSV, cv::Scalar(HL, SL, VL), cv::Scalar(HH, SH, VH),
    // GreenMask);
    cv::inRange(
        HSV, cv::Scalar(20, 150, 100), cv::Scalar(40, 255, 255), GreenMask);
    cv::inRange(
        HSV, cv::Scalar(150, 100, 144), cv::Scalar(180, 255, 255), RedMask);

    cv::blur(GreenMask, GreenMask, cv::Size(10, 10));
    cv::threshold(GreenMask, GreenMask, 200, 255, cv::THRESH_BINARY);
    cv::blur(RedMask, RedMask, cv::Size(10, 10));
    cv::threshold(RedMask, RedMask, 200, 255, cv::THRESH_BINARY);
    cv::add(GreenMask, RedMask, ThresholdMask);

    glp::setTexture(texCamId, frame.cols, frame.rows, GL_BGR, frame.ptr());
    glp::setTexture(texPId,
                    ThresholdMask.cols,
                    ThresholdMask.rows,
                    GL_LUMINANCE,
                    ThresholdMask.ptr());

    // Draw a textured quad
    float CW, CH;
    getBestFit(frame.cols, frame.rows, Width, Height / 2, CW, CH);
    // std::cout << "CW = " << CW << " CH = " << CH << std::endl;

    {
      cv::Moments m = cv::moments(GreenMask);
      cv::Point p(m.m10 / m.m00, m.m01 / m.m00);
      glDisable(GL_TEXTURE_2D);
      if (p.x > 0 && p.y > 0)
        glp::cross(p.x / 960.0f * 640, 480 - p.y / 720.0f * 480, 50);
    }
    {
      cv::Moments m = cv::moments(RedMask);
      cv::Point p(m.m10 / m.m00, m.m01 / m.m00);
      glDisable(GL_TEXTURE_2D);
      if (p.x > 0 && p.y > 0)
        glp::cross(p.x / 960.0f * 640, 480 - p.y / 720.0f * 480, 50);
    }

    glColor3f(1, 1, 1);
    glp::renderTexture(texCamId, 0, 0, CW, CH);
    glp::renderTexture(texPId, 0, Height / 2, CW, CH);
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
