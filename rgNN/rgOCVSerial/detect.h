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
    cap.release();
  }

  bool turnCameraOn() {
#if WIN32
    cap.open("http://10.0.0.103:8080/videofeed?dummy=param.mjpg");
#else
    cap.open(0);
#endif
    if (!cap.isOpened()) {
      return false;
    } else {
      cap.set(cv::CAP_PROP_FRAME_WIDTH, 320);
      cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240);
      CamWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
      CamHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
      std::cout << "Camera initialized width = " << CamWidth
                << " height = " << CamHeight << std::endl;
    }
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);
    return true;
  }

  void startCapture() {
    if (cap.isOpened()) {
      ofs.open("../data/video_capture/video.raw");
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
    cap >> Frame;
    cv::cvtColor(Frame, greyMat, cv::COLOR_BGR2GRAY);
    if (captureFrames) {
      saveFrame(greyMat);
    }
    glp::ShowImage("Frame", greyMat);
    //  glp::EnableImageFPS("Frame", true);
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

  cv::VideoCapture cap;
  cv::Mat Frame, greyMat;
  QTimer* timer;
  bool captureFrames;
  std::ofstream ofs;
};

#endif  // DETECT
