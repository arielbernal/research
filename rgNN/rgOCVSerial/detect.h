#ifndef DETECT
#define DETECT
#include <QMessageBox>
#include <QObject>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <../common/ocvTools/imageshow.h>
#include <../common/oglTools/fps.h>
#include <fstream>

class RobotDetect : public QObject {
  Q_OBJECT
 public:
  RobotDetect() : captureFrames(false), timer(new QTimer(this)) {}
  ~RobotDetect() {
    std::cout << "Camera Released" << std::endl;
    if (cap.isOpened())
      cap.release();
    if (capPhone.isOpened())
      capPhone.release();
  }

  bool turnCameraOn() {
    cap.open(0);
    if (!cap.isOpened()) {
      return false;
    } else {
      cap.set(cv::CAP_PROP_FRAME_WIDTH, 960);
      cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
      CamWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
      CamHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
      std::cout << "Camera initialized width = " << CamWidth
                << " height = " << CamHeight << std::endl;
    }

    capPhone.open("http://10.0.0.103:8080/videofeed?dummy=param.mjpg");
    if (!capPhone.isOpened()) {
      return false;
    } else {
      capPhone.set(cv::CAP_PROP_FRAME_WIDTH, 320);
      capPhone.set(cv::CAP_PROP_FRAME_HEIGHT, 240);
      CamWidthPhone = capPhone.get(cv::CAP_PROP_FRAME_WIDTH);
      CamHeightPhone = capPhone.get(cv::CAP_PROP_FRAME_HEIGHT);
      std::cout << "Camera initialized width = " << CamWidthPhone
                << " height = " << CamHeightPhone << std::endl;
    }
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
    return true;
  }

  void startCapture() {
    if (cap.isOpened()) {
      ofs.open("E:/DataNN/video.raw");
      if (ofs.is_open()) {
        captureFrames = true;
      }
    }
  }

  void stopCapture() {
    captureFrames = false;
    ofs.close();
  }

  bool turnCameraOff() {
    cap.release();
    timer->stop();
    return true;
  }

 private slots:

  void update() {
    capPhone >> FramePhone;
    cv::cvtColor(FramePhone, greyMat, cv::COLOR_BGR2GRAY);
    glp::ShowImage("FramePhone", FramePhone, 640, 480);
    //    if (captureFrames) {
    //      saveFrame(greyMat);
    //    }

    cap >> Frame;

    cv::cvtColor(Frame, HSV, cv::COLOR_BGR2HSV);
    cv::inRange(
        HSV, cv::Scalar(25, 120, 210), cv::Scalar(40, 255, 255), YellowMask);
    cv::inRange(
        HSV, cv::Scalar(0, 100, 100), cv::Scalar(15, 255, 255), RedMask);
    cv::inRange(
        HSV, cv::Scalar(170, 100, 100), cv::Scalar(180, 255, 255), RedMask1);
    cv::add(RedMask, RedMask1, RedMask);

    cv::dilate(RedMask, RedMask, cv::Mat());
    cv::dilate(YellowMask, YellowMask, cv::Mat());

    cv::blur(YellowMask, YellowMask, cv::Size(15, 15));
    cv::threshold(YellowMask, YellowMask, 100, 255, cv::THRESH_BINARY);
    cv::blur(RedMask, RedMask, cv::Size(15, 15));
    cv::threshold(RedMask, RedMask, 100, 255, cv::THRESH_BINARY);
    cv::add(RedMask, YellowMask, ThresholdMask);

    glp::ShowImage("Threshold", ThresholdMask);
    glp::ShowImage("Frame", Frame);
    glp::EnableImageFPS("Frame", true);
  }

 protected:
  void saveFrame(const cv::Mat& mat) {
    const uchar* p = mat.ptr();
    for (int i = 0; i < CamWidth * CamHeight; ++i) {
      ofs << p[i];
    }
  }

 private:
  size_t CamWidth;
  size_t CamHeight;
  size_t CamWidthPhone;
  size_t CamHeightPhone;

  cv::VideoCapture cap;
  cv::VideoCapture capPhone;
  cv::Mat FramePhone;
  cv::Mat Frame, greyMat;

  cv::Mat HSV;
  cv::Mat RedMask;
  cv::Mat RedMask1;
  cv::Mat YellowMask;
  cv::Mat ThresholdMask;

  QTimer* timer;
  bool captureFrames;
  std::ofstream ofs;
};

#endif  // DETECT
