#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <settingsdialog.h>
#include <detect.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();
  void delay(int ms);
 private slots:
  void openSerialPort();
  void closeSerialPort();
  void writeData(const QByteArray& data);
  void readData();
  void handleError(QSerialPort::SerialPortError error);
  void writeMotors();
  void cameraOn();
  void cameraOff();
  void checkKeyPressed();
  void startCapture();
  void stopCapture();

 protected:
  void closeEvent(QCloseEvent* event);

 private:
  Ui::MainWindow* ui;
  SettingsDialog* settings;
  QSerialPort* serial;

  RobotDetect* detect;

  bool receiveData;
  char data[2000];
  int bytesRead;
  int bytesTotalRead;

  float vMotors[2];
  float v,w;
};
#endif  // MAINWINDOW_H
