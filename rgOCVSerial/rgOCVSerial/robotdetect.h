#ifndef ROBOTDETECT_H
#define ROBOTDETECT_H

#include <QOpenGLWidget>
#include <QDebug>
#include <list>
#include <opencv2/opencv.hpp>
#include <glm/glm.hpp>

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
    cv::Mat YellowMask;
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
//         cv::inRange(HSV, cv::Scalar(HL, SL, VL), cv::Scalar(HH, SH, VH),
//         YellowMask);
    cv::inRange(
        HSV, cv::Scalar(25, 120, 210), cv::Scalar(50, 255, 255), YellowMask);
    cv::inRange(
        HSV, cv::Scalar(150, 120, 180), cv::Scalar(180, 255, 255), RedMask);

    cv::dilate(RedMask, RedMask, cv::Mat());
    cv::dilate(RedMask, RedMask, cv::Mat());
    cv::dilate(YellowMask, YellowMask, cv::Mat());
    cv::dilate(YellowMask, YellowMask, cv::Mat());

    cv::blur(YellowMask, YellowMask, cv::Size(10, 10));
    cv::threshold(YellowMask, YellowMask, 200, 255, cv::THRESH_BINARY);
    cv::blur(RedMask, RedMask, cv::Size(10, 10));
    cv::threshold(RedMask, RedMask, 200, 255, cv::THRESH_BINARY);
    cv::add(RedMask, YellowMask, ThresholdMask);

    glp::setTexture(texCamId, frame.cols, frame.rows, GL_BGR, frame.ptr());
    glp::setTexture(texPId,
                    ThresholdMask.cols,
                    ThresholdMask.rows,
                    GL_LUMINANCE,
                    ThresholdMask.ptr());

    glm::vec3 colorYellow(1, 1, 0);
    cv::Moments m1 = cv::moments(YellowMask);
    cv::Point p1(m1.m10 / m1.m00, m1.m01 / m1.m00);
    glDisable(GL_TEXTURE_2D);
//    if (p1.x > 0 && p1.y > 0)
//      glp::cross(
//          p1.x / 960.0f * 640, 480 - p1.y / 720.0f * 480, 50, colorYellow);

    glm::vec3 colorRed(1, 0, 0);
    cv::Moments m2 = cv::moments(RedMask);
    cv::Point p2(m2.m10 / m2.m00, m2.m01 / m2.m00);
//    if (p2.x > 0 && p2.y > 0)
//      glp::cross(p2.x / 960.0f * 640, 480 - p2.y / 720.0f * 480, 50, colorRed);

    cv::Point pm = (p1 + p2) / 2;
    if (pm.x > 0 && pm.y > 0) {
    //  glp::cross(pm.x / 960.0f * 640,
//                 480 - pm.y / 720.0f * 480,
//                 50,
//                 glm::vec3(1, 1, 1));
      glPushMatrix();
      glTranslatef(pm.x / 960.0f * 640,
                  480 - pm.y / 720.0f * 480,0);
      glp::circle(20,0);
      glPopMatrix();
    }

    // Draw a textured quad
    float CW, CH;
    getBestFit(frame.cols, frame.rows, Width, Height / 2, CW, CH);
    // std::cout << "CW = " << CW << " CH = " << CH << std::endl;
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
