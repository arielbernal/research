#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QTime>

#include <iostream>
#include <opencv2/opencv.hpp>
#include <ocvTools/imageshow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  settings = new SettingsDialog;
  serial = new QSerialPort;

  ui->actionConnect->setVisible(true);
  ui->actionDisconnect->setVisible(false);
  ui->actionCamera->setVisible(true);
  ui->actionExit->setEnabled(true);
  ui->actionConfiguration->setEnabled(true);
  ui->actionCamera->setEnabled(true);
  ui->statusBar->showMessage(tr("Disconnected"));

  connect(ui->actionConfiguration, SIGNAL(triggered()), settings, SLOT(show()));
  connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
  connect(ui->actionDisconnect, SIGNAL(triggered()), this,
          SLOT(closeSerialPort()));
  connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

  connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
          SLOT(handleError(QSerialPort::SerialPortError)));
  connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));

  connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(writeSomedata()));
  connect(ui->pushButton_2, SIGNAL(pressed()), this, SLOT(pushButton2()));
  connect(ui->btnRead, SIGNAL(pressed()), this, SLOT(btnRead()));

  robot = new Robot(6, 5, 180);

  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(openNewImage()));

  receiveData = false;
}

void MainWindow::openNewImage() {
  cv::Mat frame(720, 960, CV_8UC3);
  glp::ImageShow::Show("Frame", frame);
  glp::ImageShow::Show("Frame1", frame);
  glp::ImageShow::Show("Frame2", frame);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::closeEvent(QCloseEvent *event) { glp::ImageShow::CloseAll(); }

void MainWindow::openSerialPort() {
  SettingsDialog::Settings p = settings->settings();
  serial->setPortName(p.name);
  serial->setBaudRate(p.baudRate);
  serial->setDataBits(p.dataBits);
  serial->setParity(p.parity);
  serial->setStopBits(p.stopBits);
  serial->setFlowControl(p.flowControl);
  if (serial->open(QIODevice::ReadWrite)) {
    ui->actionConnect->setVisible(false);
    ui->actionDisconnect->setVisible(true);
    ui->actionConfiguration->setVisible(false);
    ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6, %7")
                                   .arg(p.name)
                                   .arg(p.stringBaudRate)
                                   .arg(p.stringDataBits)
                                   .arg(p.stringParity)
                                   .arg(p.stringStopBits)
                                   .arg(p.stringFlowControl)
                                   .arg(p.manufacturer));
  } else {
    QMessageBox::critical(this, tr("Error"), serial->errorString());
    ui->statusBar->showMessage(tr("Open error"));
  }
}

void MainWindow::writeData(const QByteArray &data) { serial->write(data); }

void MainWindow::delay(int ms) {
  QTime dieTime = QTime::currentTime().addMSecs(ms);
  while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::readData() {
  if (receiveData) {
    QByteArray q = serial->readAll();
    std::cout << "Actual read = " << bytesTotalRead << " Read = " << q.size()
              << " Total = " << bytesTotalRead + q.size() << std::endl;
    memcpy(&data[bytesTotalRead], q.data(), q.size());
    bytesTotalRead += q.size();
    if (bytesTotalRead >= 180 * 2) {
      receiveData = false;
      robot->appendData((uint16_t *)data);
    }
  } else {
    QByteArray q = serial->readAll();
  }
}

void MainWindow::handleError(QSerialPort::SerialPortError error) {
  if (error == QSerialPort::ResourceError) {
    QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
    closeSerialPort();
  }
}

void MainWindow::closeSerialPort() {
  if (serial->isOpen())
    serial->close();
  ui->actionConnect->setVisible(true);
  ui->actionDisconnect->setVisible(false);
  ui->actionConfiguration->setVisible(true);
  ui->statusBar->showMessage(tr("Disconnected"));
}

void MainWindow::writeSomedata() {
  serial->write("1");
  bytesTotalRead = 0;
  bytesRead = 0;
  receiveData = true;
}

void MainWindow::pushButton2() { robot->randomMove(); }

void MainWindow::btnRead() {
  uint16_t b[2000];
  b[0] = 2000;
  for (int i = 1; i < 180; ++i) {
    float v = b[i - 1] + (rand() / float(RAND_MAX) * 2 - 1) * 50;
    b[i] = v < 0 ? 100 : v > 4000 ? 4000 : v;
  }
  robot->appendData(b);
}
