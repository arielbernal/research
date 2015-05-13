#include "mainwindow.h"
#include <QApplication>

#include <imagedialog.h>
#include <opencv2/opencv.hpp>

int main(int argc, char* argv[]) {
  //  QApplication a(argc, argv);
  //  //    MainWindow w;
  //  //    w.setGeometry(2400, 100, 800, 800);
  //  //    w.show();
  //  ImageDialog* imageDialog = new ImageDialog();
  //  imageDialog->setAttribute(Qt::WA_DeleteOnClose);
  //  imageDialog->setModal(false);
  //  imageDialog->show();
  //  imageDialog->raise();
  //  return a.exec();

  cv::VideoCapture cap(0);
  if (!cap.isOpened()) {
    std::cout << "Camera error" << std::endl;
    exit(-1);
  } else {
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 960);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
    size_t CamWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    size_t CamHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    std::cout << "Camera initialized width = " << CamWidth
              << " height = " << CamHeight << std::endl;
  }

  cv::Mat HSV;
  cv::Mat RedMask;
  cv::Mat YellowMask;
  cv::Mat ThresholdMask;
  for (;;) {
    cv::Mat frame;
    cap >> frame;
    cv::cvtColor(frame, HSV, cv::COLOR_BGR2HSV);
    cv::inRange(
        HSV, cv::Scalar(25, 120, 210), cv::Scalar(50, 255, 255), YellowMask);
    cv::inRange(
        HSV, cv::Scalar(150, 120, 180), cv::Scalar(180, 255, 255), RedMask);

//    cv::erode(RedMask, RedMask, cv::Mat());
//    cv::erode(YellowMask, RedMask, cv::Mat());
    cv::dilate(RedMask, RedMask, cv::Mat());
    cv::dilate(YellowMask, YellowMask, cv::Mat());
//    cv::erode(RedMask, RedMask, cv::Mat());
//    cv::erode(YellowMask, RedMask, cv::Mat());

    cv::blur(YellowMask, YellowMask, cv::Size(10, 10));
    cv::threshold(YellowMask, YellowMask, 150, 255, cv::THRESH_BINARY);
    cv::blur(RedMask, RedMask, cv::Size(10, 10));
    cv::threshold(RedMask, RedMask, 150, 255, cv::THRESH_BINARY);
    cv::add(RedMask, YellowMask, ThresholdMask);

    cv::Moments m1 = cv::moments(YellowMask);
    cv::Point p1(m1.m10 / m1.m00, m1.m01 / m1.m00);
    cv::Moments m2 = cv::moments(RedMask);
    cv::Point p2(m2.m10 / m2.m00, m2.m01 / m2.m00);
    cv::Point pm = (p1 + p2);
    pm.x /= 2;
    pm.y /= 2;
    if (pm.x > 0 && pm.y > 0) {
      int Cx = 20;
      cv::Point p0x(pm.x - Cx, pm.y);
      cv::Point p1x(pm.x + Cx, pm.y);
      cv::line(frame, p0x, p1x, cv::Scalar(0, 255, 0), 1);
      cv::Point p0y(pm.x, pm.y - Cx);
      cv::Point p1y(pm.x, pm.y + Cx);
      cv::line(frame, p0y, p1y, cv::Scalar(0, 255, 0), 1);
    }

    cv::imshow("frame", frame);
    cv::imshow("ThresholdMask", ThresholdMask);

    if (cv::waitKey(30) >= 0)
      break;
  }

  std::cout << "End of program" << std::endl;
}
