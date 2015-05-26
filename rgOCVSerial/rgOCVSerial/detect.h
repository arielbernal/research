#ifndef DETECT
#define DETECT
#include <QMessageBox>
#include <QObject>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <ocvTools/imageshow.h>
#include <oglTools/fps.h>

class RobotCV {
public:
  RobotCV() : WWidth(0), WHeight(0) {}

  cv::Point Center;
  cv::Point CenterLeft;
  cv::Point CenterRight;
  size_t WWidth;
  size_t WHeight;

  void init(size_t W, size_t H) {
    WWidth = W;
    WHeight = H;
  }

  float getAngle() {
    float dx = CenterRight.x - CenterLeft.x;
    float dy = CenterRight.y - CenterLeft.y;
    float ap = atan2(dx, dy) + 3.14159265;
    return ap / 3.14159265358f * 180;
  }


  void render() {
    Center = (CenterLeft + CenterRight) / 2.0f;
    glPushMatrix();
    glTranslatef(Center.x, WHeight - Center.y, 0.0f);
    glRotatef(getAngle(), 0, 0, 1);
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(50, 0);
    glEnd();
    glColor3f(0, 0, 0);
    glp::disk(5);
    glColor3f(1, 1, 1);

    glPopMatrix();
  }
};

class RobotDetect : public QObject {
  Q_OBJECT
public:
  RobotDetect() { timer = new QTimer(this); }
  ~RobotDetect() {
    std::cout << "Camera Released" << std::endl;
    cap.release();
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
    Robot.init(CamWidth, CamHeight);

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1);
    return true;
  }

  bool turnCameraOff() {
    cap.release();
    timer->stop();
    return true;
  }
private slots:
  void update() { detect(); }

protected:
  void detect() {

    cap >> Frame;
    cv::cvtColor(Frame, HSV, cv::COLOR_BGR2HSV);
    cv::inRange(HSV, cv::Scalar(25, 120, 210), cv::Scalar(40, 255, 255),
                YellowMask);
    cv::inRange(HSV, cv::Scalar(0, 120, 180), cv::Scalar(15, 255, 255),
                RedMask);
    cv::inRange(HSV, cv::Scalar(170, 120, 180), cv::Scalar(180, 255, 255),
                RedMask1);
    cv::add(RedMask, RedMask1, RedMask);

    cv::dilate(RedMask, RedMask, cv::Mat());
    cv::dilate(YellowMask, YellowMask, cv::Mat());

    cv::blur(YellowMask, YellowMask, cv::Size(15, 15));
    cv::threshold(YellowMask, YellowMask, 100, 255, cv::THRESH_BINARY);
    cv::blur(RedMask, RedMask, cv::Size(15, 15));
    cv::threshold(RedMask, RedMask, 100, 255, cv::THRESH_BINARY);
    cv::add(RedMask, YellowMask, ThresholdMask);

    cv::Moments m1 = cv::moments(YellowMask);
    cv::Point p1(m1.m10 / m1.m00, m1.m01 / m1.m00);
    cv::Moments m2 = cv::moments(RedMask);
    cv::Point p2(m2.m10 / m2.m00, m2.m01 / m2.m00);
    if (p1.x > 0 && p1.y > 0 && p2.x > 0 && p2.y > 0) {
      CenterRight.push_back(p1);
      CenterLeft.push_back(p2);
      if (CenterLeft.size() > 10) {
        CenterRight.pop_front();
        CenterLeft.pop_front();
      }
      cv::Point PLeft(0, 0);
      for (auto &e : CenterLeft)
        PLeft += e;
      PLeft = PLeft / float(CenterLeft.size());
      cv::Point PRight(0, 0);
      for (auto &e : CenterRight)
        PRight += e;
      PRight = PRight / float(CenterRight.size());
      Robot.CenterLeft = PLeft;
      Robot.CenterRight = PRight;
    }
    glp::ShowImage("Threshold", ThresholdMask);
    auto fp = std::bind(&RobotDetect::FrameRenderer, this);
    glp::ShowImage("Frame", Frame, fp);
    glp::EnableImageFPS("Frame", true);
  }

  void FrameRenderer() { Robot.render(); }

private:
  size_t CamWidth;
  size_t CamHeight;

  cv::VideoCapture cap;
  cv::Mat Frame;
  QTimer *timer;
  std::list<cv::Point> CenterLeft;
  std::list<cv::Point> CenterRight;
  cv::Mat HSV;
  cv::Mat RedMask;
  cv::Mat RedMask1;
  cv::Mat YellowMask;
  cv::Mat ThresholdMask;
  RobotCV Robot;
};

#endif // DETECT
