#ifndef DETECT
#define DETECT
#include <QMessageBox>
#include <QObject>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <ocvTools/imageshow.h>
#include <oglTools/fps.h>

<<<<<<< HEAD
=======
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
//    Center = (CenterLeft + CenterRight) / 2 ;
//    glPushMatrix();
//    glTranslatef(Center.x, WHeight - Center.y, 0.0f);
//    glRotatef(getAngle(), 0, 0, 1);
//    glColor3f(1, 0, 0);
//    glBegin(GL_LINES);
//    glVertex2f(0, 0);
//    glVertex2f(50, 0);
//    glEnd();
//    glColor3f(0, 0, 0);
//    glp::disk(5);
//    glColor3f(1, 1, 1);

//    glPopMatrix();
  }
};

>>>>>>> 2a016ff8f3049abc75a66feadd4b5cab4e94226b
class RobotDetect : public QObject {
  Q_OBJECT
public:
  RobotDetect() { timer = new QTimer(this); }
  ~RobotDetect() {
    std::cout << "Camera Released" << std::endl;
    cap.release();
  }

  bool turnCameraOn() {
    //cap.open(0);
    cap.open("http://10.0.0.103:8080/videofeed?dummy=param.mjpg");
    if (!cap.isOpened()) {
      return false;
    } else {
//      cap.set(cv::CAP_PROP_FRAME_WIDTH, 960);
//      cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
      CamWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
      CamHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
      std::cout << "Camera initialized width = " << CamWidth
                << " height = " << CamHeight << std::endl;
    }
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
    cv::cvtColor(Frame, greyMat, CV_BGR2GRAY);

    glp::ShowImage("Frame", greyMat);
    glp::EnableImageFPS("Frame", true);
    320*240

  }

private:
  size_t CamWidth;
  size_t CamHeight;

  cv::VideoCapture cap;
  cv::Mat Frame, greyMat;
  QTimer *timer;
};

#endif // DETECT
