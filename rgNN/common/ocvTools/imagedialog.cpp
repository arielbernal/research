#include "imagedialog.h"
#include "ui_imagedialog.h"
#include <../common/ocvTools/imageglwidget.h>
#include <../common/ocvTools/imageshow.h>

#include <iostream>

ImageDialog::ImageDialog(const std::string &Name, cv::Mat &Image,
                         QWidget *parent)
    : QDialog(parent), ui(new Ui::ImageDialog), Name(Name) {
  ui->setupUi(this);
  setAttribute(Qt::WA_DeleteOnClose);
  setModal(false);
  setWindowTitle(Name.c_str());

  imageWidget = new ImageGLWidget(Name, Image);
  imageWidget->setFixedSize(Image.cols, Image.rows);
  layout()->addWidget(imageWidget);
  adjustSize();
  setFixedSize(width(), height());
  std::cout << "Created ImageDialog " << Name << std::endl;
}

ImageDialog::~ImageDialog() {
  glp::RemoveImage(Name);
  std::cout << "Deleted ImageDialog " << Name << std::endl;
  delete ui;
}

void ImageDialog::closeEvent(QCloseEvent *event) {

}
