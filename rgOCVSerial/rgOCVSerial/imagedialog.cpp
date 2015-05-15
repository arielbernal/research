#include "imagedialog.h"
#include "ui_imagedialog.h"
#include <imageglwidget.h>
#include <imageshow.h>

#include <iostream>

ImageDialog::ImageDialog(const std::string& Name, cv::Mat& Image, QWidget* parent)
    : QDialog(parent), ui(new Ui::ImageDialog), Name(Name) {
  ui->setupUi(this);
  setAttribute(Qt::WA_DeleteOnClose);
  setModal(false);

  imageWidget = new ImageGLWidget(Image);
  imageWidget->setFixedSize(Image.cols, Image.rows);
  layout()->addWidget(imageWidget);
  adjustSize();
  std::cout << "Created ImageDialog " << Name <<  std::endl;
}

ImageDialog::~ImageDialog() {
  glp::ImageShow::Remove(Name);
  std::cout << "Deleted ImageDialog " << Name << std::endl;
  delete ui;
}
