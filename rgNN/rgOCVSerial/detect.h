#ifndef DETECT
#define DETECT
#include <QMessageBox>
#include <QObject>
#include <QTimer>
#include <QSerialPort>
#include <opencv2/opencv.hpp>
#include <../common/ocvTools/imageshow.h>
#include <../common/oglTools/fps.h>
#include <fstream>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358
#endif

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

    // capPhone.open("http://10.0.0.103:8080/videofeed?dummy=param.mjpg");
    if (!capPhone.isOpened()) {
      //  return false;
    } else {
      capPhone.set(cv::CAP_PROP_FRAME_WIDTH, 320);
      capPhone.set(cv::CAP_PROP_FRAME_HEIGHT, 240);
      CamWidthPhone = capPhone.get(cv::CAP_PROP_FRAME_WIDTH);
      CamHeightPhone = capPhone.get(cv::CAP_PROP_FRAME_HEIGHT);
      std::cout << "Camera initialized width = " << CamWidthPhone
                << " height = " << CamHeightPhone << std::endl;
    }

    P1 = cv::Mat(30, 30, CV_8UC1);
    P2 = cv::Mat(30, 30, CV_8UC1);
    for (int y = 0; y < 30; ++y) {
      for (int x = 0; x < 30; ++x) {
        float r = sqrt((x - 15) * (x - 15) + (y - 15) * (y - 15));
        if (15 < r) {
          P1.at<uchar>(y, x) = 128;
          P2.at<uchar>(y, x) = 128;
        }
        if (11 < r && r <= 15) {
          P1.at<uchar>(y, x) = 0;
          P2.at<uchar>(y, x) = 0;
        }
        if (r <= 11)
          P1.at<uchar>(y, x) = 255;
        if (7 < r && r <= 11)
          P2.at<uchar>(y, x) = 255;
        if (r <= 7)
          P2.at<uchar>(y, x) = 0;
      }
    }

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
    return true;
  }

  void setSerialCom(QSerialPort* serialCom) { serial = serialCom; }

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

  void onMouse(int event, int x, int y, int status, void* ptr) {
    if (event == cv::EVENT_LBUTTONDOWN) {
      PMouse = cv::Point(x, y);
      float gamma = atan2(-PMouse.y + PRobot.y, PMouse.x - PRobot.x);
      if (gamma < 0)
        gamma = 2 * M_PI + gamma;

      if (beta < gamma) {
        vMotors[0] = -50;
        vMotors[1] = 50;
      } else {
        vMotors[0] = 50;
        vMotors[1] = -50;
      }
      writeMotors();
      return;
    }
    if (event == cv::EVENT_RBUTTONDOWN) {
      PMouse = cv::Point(x, y);
      vMotors[0] = 0;
      vMotors[1] = 0;
      writeMotors();
      return;
    }
  }

  void writeMotors() {
    if (serial->isOpen()) {
      char v[2] = {char(-vMotors[0]), char(-vMotors[1])};
      serial->write(v, 2);
    }
  }

 private slots:

  float euclideanDist(const cv::Point& p, const cv::Point& q) {
    cv::Point diff = p - q;
    return sqrt(diff.x * diff.x + diff.y * diff.y);
  }

  void update() {
    cv::Mat Frame;
    cap >> Frame;

    cv::Mat greyMat;
    cv::cvtColor(Frame, greyMat, cv::COLOR_BGR2GRAY);
    cv::Mat R1(
        greyMat.rows - P1.rows + 1, greyMat.cols - P1.cols + 1, CV_32FC1);
    cv::matchTemplate(greyMat, P1, R1, CV_TM_CCOEFF_NORMED);
    cv::dilate(R1, R1, cv::Mat());
    cv::Mat T1;
    cv::threshold(R1, T1, 0.7, 1, CV_THRESH_BINARY);

    cv::Mat R2(
        greyMat.rows - P1.rows + 1, greyMat.cols - P1.cols + 1, CV_32FC1);
    cv::matchTemplate(greyMat, P2, R2, CV_TM_CCOEFF_NORMED);
    cv::dilate(R2, R2, cv::Mat());

    cv::Mat T2;
    cv::threshold(R2, T2, 0.6, 1, CV_THRESH_BINARY);

    cv::Moments m1 = cv::moments(T1);
    cv::Point p1(m1.m10 / m1.m00 + 15, m1.m01 / m1.m00 + 15);

    cv::Moments m2 = cv::moments(T2);
    cv::Point p2(m2.m10 / m2.m00 + 15, m2.m01 / m2.m00 + 15);

    cv::Point pm = (p2 + p1) / 2;
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float angle = atan2(dy, dx);
    PRobot = cv::Point(pm.x + 50 * sin(angle), pm.y - 50 * cos(angle));

    cv::Point pf1(pm.x + 100 * sin(angle), pm.y - 100 * cos(angle));
    cv::circle(Frame, PRobot, 30, cv::Scalar(0, 255, 255));
    cv::arrowedLine(Frame, PRobot, pf1, cv::Scalar(0, 0, 255));

    beta = M_PI / 2 - angle;
    if (beta < 0)
      beta = 2 * M_PI + beta;

    float gamma = atan2(-PMouse.y + PRobot.y, PMouse.x - PRobot.x);
    if (gamma < 0)
      gamma = 2 * M_PI + gamma;

    float eps = 6 / 180.0f * M_PI;

    if (abs(beta - 50 / 180.0f * M_PI - gamma) < eps) {
      vMotors[0] = 0;
      vMotors[1] = 0;
      writeMotors();
    }

    std::cout << beta * 180 / M_PI << " " << gamma * 180 / M_PI << std::endl;

    cv::circle(Frame, PMouse, 5, cv::Scalar(0, 255, 255));

    cv::Mat Threshold;
    cv::add(T1, T2, Threshold);
    cv::Mat Res;
    cv::add(R1, R2, Res);

    cv::imshow("frame", Frame);
    cv::setMouseCallback("frame", onMouseStatic, this);
    //        cv::imshow("greyMat", greyMat);
    cv::imshow("Match", R2);
    cv::imshow("Threshold", Threshold);
  }

 protected:
  static void onMouseStatic(int event, int x, int y, int status, void* ptr) {
    ((RobotDetect*)ptr)->onMouse(event, x, y, status, 0);
  }

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

  QTimer* timer;
  bool captureFrames;
  std::ofstream ofs;
  cv::Mat P1;
  cv::Mat P2;

  cv::Point PMouse;
  cv::Point PRobot;

  float vMotors[2];

  QSerialPort* serial;

  float beta;
};

#endif  // DETECT
