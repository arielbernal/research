#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#include <QDialog>
#include <ocvTools/imageglwidget.h>
#include <opencv2/opencv.hpp>

namespace Ui {
class ImageDialog;
}

class ImageDialog : public QDialog {
  Q_OBJECT

public:
  explicit ImageDialog(const std::string &Name, cv::Mat &Image,
                       QWidget *parent = 0);
  ~ImageDialog();
protected:
    void closeEvent(QCloseEvent *event);
private:
  Ui::ImageDialog *ui;
  ImageGLWidget *imageWidget;
  std::string Name;
};

#endif // IMAGEDIALOG_H
