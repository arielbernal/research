#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->toolBox->setItemEnabled(1, false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_5_clicked() {}

void MainWindow::on_pushButton_2_clicked() {}
