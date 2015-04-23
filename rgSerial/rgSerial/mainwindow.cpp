#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);
  settings = new SettingsDialog;
  serial = new QSerialPort;

  ui->actionConnect->setVisible(true);
  ui->actionDisconnect->setVisible(false);
  ui->actionExit->setEnabled(true);
  ui->actionConfiguration->setEnabled(true);
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

  connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(writeSomedata()));
}

MainWindow::~MainWindow() { delete ui; }

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

void MainWindow::writeData(const QByteArray& data) { serial->write(data); }

void MainWindow::readData() {
  QByteArray data = serial->readAll();
  ui->textConsole->insertPlainText(QString(data));
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

void MainWindow::writeSomedata() { serial->write("1"); }
