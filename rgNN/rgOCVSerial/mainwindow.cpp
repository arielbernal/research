#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QTime>

#include <iostream>
#include <opencv2/opencv.hpp>
#include <../common/ocvTools/imageshow.h>
#include <QKeyEvent>
#include <QTimer>

#if WIN32
#include <windows.h>
#else
int GetAsyncKeyState(int k) {
  return 0;
}
#define VK_NUMPAD7 7
#define VK_NUMPAD4 4
#define VK_NUMPAD9 9
#define VK_NUMPAD6 6
#endif

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  settings = new SettingsDialog;
  serial = new QSerialPort;

  ui->actionConnect->setVisible(true);
  ui->actionDisconnect->setVisible(false);
  ui->actionCameraOn->setVisible(true);
  ui->actionCameraOff->setVisible(false);
  ui->actionExit->setEnabled(true);
  ui->actionConfiguration->setEnabled(true);
  ui->actionCameraOn->setEnabled(true);
  ui->statusBar->showMessage(tr("Disconnected"));

  connect(ui->actionConfiguration, SIGNAL(triggered()), settings, SLOT(show()));
  connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
  connect(
      ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
  connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

  connect(serial,
          SIGNAL(error(QSerialPort::SerialPortError)),
          this,
          SLOT(handleError(QSerialPort::SerialPortError)));
  connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));

  connect(ui->actionCameraOn, SIGNAL(triggered()), this, SLOT(cameraOn()));
  connect(ui->actionCameraOff, SIGNAL(triggered()), this, SLOT(cameraOff()));
  connect(ui->btnStartCapture, SIGNAL(clicked()), this, SLOT(startCapture()));
  connect(ui->btnStopCapture, SIGNAL(clicked()), this, SLOT(stopCapture()));

  detect = new RobotDetect();
  receiveData = false;
  ui->motorLeftF->setValue(0);
  ui->motorLeftB->setValue(0);
  ui->motorRightF->setValue(0);
  ui->motorRightB->setValue(0);

  vMotors[0] = 0;
  vMotors[1] = 0;
  v = 0;
  w = 0;

//  QTimer* mTimer = new QTimer();
//  connect(mTimer, SIGNAL(timeout()), this, SLOT(checkKeyPressed()));
//  mTimer->start(50);
}

MainWindow::~MainWindow() {
  delete detect;
  delete ui;
}


void MainWindow::startCapture() {
   detect->startCapture();
}

void MainWindow::stopCapture() {
  detect->stopCapture();
}

void MainWindow::checkKeyPressed() {
  int vstop = 15;
  int vmove = 10;
  if (GetAsyncKeyState(VK_NUMPAD7)) {
    vMotors[0] += vmove;
  } else if ((GetAsyncKeyState(VK_NUMPAD4))) {
    vMotors[0] -= vmove;
  } else {
    if (vMotors[0] > 0) {
      vMotors[0] -= vstop;
      if (vMotors[0] < 0)
        vMotors[0] = 0;
    }
    if (vMotors[0] < 0) {
      vMotors[0] += vstop;
      if (vMotors[0] > 0)
        vMotors[0] = 0;
    }
  }
  if (vMotors[0] > 100)
    vMotors[0] = 100;
  else if (vMotors[0] < -100)
    vMotors[0] = -100;

  if (GetAsyncKeyState(VK_NUMPAD9)) {
    vMotors[1] += vmove;
  } else if ((GetAsyncKeyState(VK_NUMPAD6))) {
    vMotors[1] -= vmove;
  } else {
    if (vMotors[1] > 0) {
      vMotors[1] -= vstop;
      if (vMotors[1] < 0)
        vMotors[1] = 0;
    }
    if (vMotors[1] < 0) {
      vMotors[1] += vstop;
      if (vMotors[1] > 0)
        vMotors[1] = 0;
    }
  }

  if (vMotors[1] > 100)
    vMotors[1] = 100;
  else if (vMotors[1] < -100)
    vMotors[1] = -100;

  if (vMotors[0] >= 0) {
    ui->motorLeftF->setValue(vMotors[0]);
    ui->motorLeftB->setValue(0);
  } else {
    ui->motorLeftB->setValue(-vMotors[0]);
    ui->motorLeftF->setValue(0);
  }

  if (vMotors[1] >= 0) {
    ui->motorRightF->setValue(vMotors[1]);
    ui->motorRightB->setValue(0);
  } else {
    ui->motorRightB->setValue(-vMotors[1]);
    ui->motorRightF->setValue(0);
  }
  writeMotors();
}

void MainWindow::closeEvent(QCloseEvent* event) {
  glp::CloseAllImages();
}

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
  detect->setSerialCom(serial);
}

void MainWindow::writeData(const QByteArray& data) {
  serial->write(data);
}

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

void MainWindow::writeMotors() {
  if (serial->isOpen()) {
    char v[2] = {char(-vMotors[0]), char(-vMotors[1])};
    serial->write(v, 2);
    bytesTotalRead = 0;
    bytesRead = 0;
    receiveData = true;
  }
}

void MainWindow::cameraOn() {
  if (!detect->turnCameraOn()) {
    QMessageBox::critical(this, tr("Critical Error"), tr("Camera Error"));
    return;
  }

  ui->actionCameraOn->setVisible(false);

  ui->actionCameraOff->setVisible(true);
}

void MainWindow::cameraOff() {
  detect->turnCameraOff();
  ui->actionCameraOff->setVisible(false);
  ui->actionCameraOn->setVisible(true);
}
