#include "imagedialog.h"
#include "ui_imagedialog.h"

#include <iostream>

ImageDialog::ImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageDialog)
{
    ui->setupUi(this);
    std::cout << "Created ImageDialog" << std::endl;



}

ImageDialog::~ImageDialog()
{
    std::cout << "Deleted ImageDialog" << std::endl;
    delete ui;
}
