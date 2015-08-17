#include "mainwindow.h"
#include <QApplication>
#include <QSerialPort>
#include <../common/ocvTools/imagedialog.h>
#include <opencv2/opencv.hpp>
#include <QObject>
#include <serialcom.h>

namespace ocv {
using namespace cv;

void cross(const cv::Mat& image,
           const Point& pm,
           int size,
           const Scalar& color,
           int thickness = 1) {
  Point p0x(pm.x - size, pm.y);
  Point p1x(pm.x + size, pm.y);
  line(image, p0x, p1x, color, thickness);
  Point p0y(pm.x, pm.y - size);
  Point p1y(pm.x, pm.y + size);
  line(image, p0y, p1y, color, thickness);
}
}

#include "ffnn3l.h"

int main(int argc, char* argv[]) {
  float alpha = M_PI / 2;
  float dx = 10;
  float dy = 10;

  FFNN3L ffnn(3, 50, 3);
  std::vector<double> input(3);
  std::vector<double> output(3);
  input[0] = alpha;
  input[1] = dx;
  input[2] = dy;
  std::cout << "Alpha = " << alpha << " dx = " << dx << " dy = " << dy
            << std::endl;

  ffnn.feedForward(input);
  ffnn.getOutput(output);
  std::cout << "V1 = " << output[0] << " V2 = " << output[1]
            << " t = " << output[2] << std::endl;
}

int main1(int argc, char* argv[]) {
  cv::VideoCapture cap;
  cap.open(0);
  size_t CamWidth = 960;
  size_t CamHeight = 720;
  if (!cap.isOpened()) {
    return false;
  } else {
    cap.set(cv::CAP_PROP_FRAME_WIDTH, CamWidth);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, CamHeight);
    std::cout << "Camera initialized width = " << CamWidth
              << " height = " << CamHeight << std::endl;
  }

  cv::Mat P1(30, 30, CV_8UC1);
  cv::Mat P2(30, 30, CV_8UC1);
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
  // SerialCom SCom;
  // SCom.openSerialPort();

  for (;;) {
    cv::Mat Frame;
    cap >> Frame;
    cv::Mat greyMat;
    cv::cvtColor(Frame, greyMat, cv::COLOR_BGR2GRAY);
    cv::Mat R1(
        greyMat.rows - P1.rows + 1, greyMat.cols - P1.cols + 1, CV_32FC1);
    cv::matchTemplate(greyMat, P1, R1, CV_TM_CCOEFF_NORMED);
    cv::Mat T1;
    cv::threshold(R1, T1, 0.6, 1, CV_THRESH_BINARY);

    cv::Mat R2(
        greyMat.rows - P1.rows + 1, greyMat.cols - P1.cols + 1, CV_32FC1);
    cv::matchTemplate(greyMat, P2, R2, CV_TM_CCOEFF_NORMED);

    cv::Mat T2;
    cv::threshold(R2, T2, 0.55, 1, CV_THRESH_BINARY);

    cv::Moments m1 = cv::moments(T1);
    cv::Point p1(m1.m10 / m1.m00 + 15, m1.m01 / m1.m00 + 15);
    cv::Moments m2 = cv::moments(T2);
    cv::Point p2(m2.m10 / m2.m00 + 15, m2.m01 / m2.m00 + 15);
    cv::Point pm = (p2 + p1) / 2;
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float angle = atan2(dy, dx);
    cv::Point pf(pm.x + 50 * sin(angle), pm.y - 50 * cos(angle));
    cv::Point pf1(pm.x + 100 * sin(angle), pm.y - 100 * cos(angle));
    cv::circle(Frame, pf, 30, cv::Scalar(0, 255, 255));
    cv::arrowedLine(Frame, pf, pf1, cv::Scalar(0, 0, 255));

    cv::Mat Threshold;
    cv::add(T1, T2, Threshold);
    cv::Mat Res;
    cv::add(R1, R2, Res);

    cv::imshow("frame", Frame);
    //        cv::imshow("greyMat", greyMat);
    //        cv::imshow("Match", Res);
    //        cv::imshow("Threshold", Threshold);
    int key = cv::waitKey(30);
    switch (key) {
      case 27:
        return 1;
        break;
      case 'a':
        break;
    }
  }
}

// int main(int argc, char* argv[]) {

//}

int main2(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.setGeometry(2400, 100, 800, 800);
  w.show();
  return a.exec();
}
////  cv::Mat HSV;
////  cv::Mat RedMask;
////  cv::Mat RedMask1;
////  cv::Mat YellowMask;
////  cv::Mat ThresholdMask;

////  std::list<cv::Point> centers;

////    cv::VideoCapture cap(0);
////    if (!cap.isOpened()) {
////      return false;
////    } else {
//////      cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
//////      cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
////      size_t CamWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
////      size_t CamHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
////      std::cout << "Camera initialized width = " << CamWidth
////                << " height = " << CamHeight << std::endl;
////    }
////  glp::FPS fps;
////  for (;;) {

////    cv::Mat frame;
////    cap >> frame;
////    float fpsVal = fps.update();
////    std::cout << "FPS = " << fpsVal << std::endl;

//////    cv::cvtColor(frame, HSV, cv::COLOR_BGR2HSV);
//////    cv::inRange(
//////        HSV, cv::Scalar(25, 120, 210), cv::Scalar(40, 255, 255),
/// YellowMask);
//////    cv::inRange(
//////        HSV, cv::Scalar(0, 120, 180), cv::Scalar(15, 255, 255), RedMask);
//////    cv::inRange(
//////        HSV, cv::Scalar(170, 120, 180), cv::Scalar(180, 255, 255),
/// RedMask1);
//////        HSV, cv::Scalar(25, 120, 210), cv::Scalar(40, 255, 255),
/// YellowMask);
//////    cv::inRange(
//////        HSV, cv::Scalar(0, 120, 180), cv::Scalar(15, 255, 255), RedMask);
//////    cv::inRange(
//////        HSV, cv::Scalar(170, 120, 180), cv::Scalar(180, 255, 255),
/// RedMask1);
//////    cv::add(RedMask, RedMask1, RedMask);

//////    cv::dilate(RedMask, RedMask, cv::Mat());
//////    cv::dilate(YellowMask, YellowMask, cv::Mat());

//////    cv::blur(YellowMask, YellowMask, cv::Size(15, 15));
//////    cv::threshold(YellowMask, YellowMask, 100, 255, cv::THRESH_BINARY);
//////    cv::blur(RedMask, RedMask, cv::Size(15, 15));
//////    cv::threshold(RedMask, RedMask, 100, 255, cv::THRESH_BINARY);
//////    cv::add(RedMask, YellowMask, ThresholdMask);

//////    cv::Moments m1 = cv::moments(YellowMask);
//////    cv::Point p1(m1.m10 / m1.m00, m1.m01 / m1.m00);
//////    cv::Moments m2 = cv::moments(RedMask);
//////    cv::Point p2(m2.m10 / m2.m00, m2.m01 / m2.m00);
//////    cv::Point pm = (p1 + p2) / 2.0f;
//////    if (pm.x > 0 && pm.y > 0) {
//////      centers.push_back(pm);
//////      if (centers.size() > 10)
//////        centers.pop_front();
//////      cv::Point pavg(0, 0);
//////      for (auto& e : centers)
//////        pavg += e;
//////      pavg = pavg / float(centers.size());
//////      ocv::cross(frame, pavg, 20, cv::Scalar::all(0), 2);
//////      float dx = p2.x - p1.x;
//////      float dy = p2.y - p1.y;
//////      float angle = atan2(dy, dx);
//////      cv::Point pf(pavg.x - 50 * sin(angle), pavg.y + 50 * cos(angle));

//////      cv::line(frame, pavg, pf, cv::Scalar(0,0,255), 2);

//////      char str[100];
//////      sprintf_s(str, "Angle = %f", angle / 3.14159265358f * 180);
//////      cv::putText(frame,
//////                  str,
//////                  cv::Point(10, 25),
//////                  CV_FONT_HERSHEY_SIMPLEX,
//////                  1,
//////                  cv::Scalar::all(255));
//////    }

////    cv::imshow("frame", frame);
//////    cv::imshow("ThresholdMask", ThresholdMask);

////    cv::imshow("frame", frame);
//////    cv::imshow("ThresholdMask", ThresholdMask);

////    if (cv::waitKey(30) >= 0)
////      break;
////  }

//////  std::cout << "End of program" << std::endl;
//}
