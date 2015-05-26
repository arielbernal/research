#include "mainwindow.h"
#include <QApplication>

#include <ocvTools/imagedialog.h>
#include <opencv2/opencv.hpp>
//#include <oglTools/fps.h>

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

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
        MainWindow w;
        w.setGeometry(2400, 100, 800, 800);
        w.show();
    return a.exec();

//  cv::Mat HSV;
//  cv::Mat RedMask;
//  cv::Mat RedMask1;
//  cv::Mat YellowMask;
//  cv::Mat ThresholdMask;

//  std::list<cv::Point> centers;

//    cv::VideoCapture cap(0);
//    if (!cap.isOpened()) {
//      return false;
//    } else {
////      cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
////      cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
//      size_t CamWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
//      size_t CamHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
//      std::cout << "Camera initialized width = " << CamWidth
//                << " height = " << CamHeight << std::endl;
//    }
//  glp::FPS fps;
//  for (;;) {


//    cv::Mat frame;
//    cap >> frame;
//    float fpsVal = fps.update();
//    std::cout << "FPS = " << fpsVal << std::endl;

////    cv::cvtColor(frame, HSV, cv::COLOR_BGR2HSV);
////    cv::inRange(
////        HSV, cv::Scalar(25, 120, 210), cv::Scalar(40, 255, 255), YellowMask);
////    cv::inRange(
////        HSV, cv::Scalar(0, 120, 180), cv::Scalar(15, 255, 255), RedMask);
////    cv::inRange(
////        HSV, cv::Scalar(170, 120, 180), cv::Scalar(180, 255, 255), RedMask1);
////    cv::add(RedMask, RedMask1, RedMask);

////    cv::dilate(RedMask, RedMask, cv::Mat());
////    cv::dilate(YellowMask, YellowMask, cv::Mat());

////    cv::blur(YellowMask, YellowMask, cv::Size(15, 15));
////    cv::threshold(YellowMask, YellowMask, 100, 255, cv::THRESH_BINARY);
////    cv::blur(RedMask, RedMask, cv::Size(15, 15));
////    cv::threshold(RedMask, RedMask, 100, 255, cv::THRESH_BINARY);
////    cv::add(RedMask, YellowMask, ThresholdMask);

////    cv::Moments m1 = cv::moments(YellowMask);
////    cv::Point p1(m1.m10 / m1.m00, m1.m01 / m1.m00);
////    cv::Moments m2 = cv::moments(RedMask);
////    cv::Point p2(m2.m10 / m2.m00, m2.m01 / m2.m00);
////    cv::Point pm = (p1 + p2) / 2.0f;
////    if (pm.x > 0 && pm.y > 0) {
////      centers.push_back(pm);
////      if (centers.size() > 10)
////        centers.pop_front();
////      cv::Point pavg(0, 0);
////      for (auto& e : centers)
////        pavg += e;
////      pavg = pavg / float(centers.size());
////      ocv::cross(frame, pavg, 20, cv::Scalar::all(0), 2);
////      float dx = p2.x - p1.x;
////      float dy = p2.y - p1.y;
////      float angle = atan2(dy, dx);
////      cv::Point pf(pavg.x - 50 * sin(angle), pavg.y + 50 * cos(angle));

////      cv::line(frame, pavg, pf, cv::Scalar(0,0,255), 2);

////      char str[100];
////      sprintf_s(str, "Angle = %f", angle / 3.14159265358f * 180);
////      cv::putText(frame,
////                  str,
////                  cv::Point(10, 25),
////                  CV_FONT_HERSHEY_SIMPLEX,
////                  1,
////                  cv::Scalar::all(255));
////    }


//    cv::imshow("frame", frame);
////    cv::imshow("ThresholdMask", ThresholdMask);



//    if (cv::waitKey(30) >= 0)
//      break;
//  }

////  std::cout << "End of program" << std::endl;
}
